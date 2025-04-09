#include "AIThread.hpp"

AIThread &AIThread::getInstance()
{
    static AIThread instance;
    return instance;
}

void AIThread::init() {
    tx_thread_create(
        &thread,
        (CHAR*)"AIThread",
        AIThread::ThreadFunc,
        (ULONG)this,
        stack,
        STACK_SIZE,
        6, 6, TX_NO_TIME_SLICE, TX_AUTO_START
    );

    tx_event_flags_create(&events, (CHAR*)"AI_EVENT");
}

void AIThread::ThreadFunc(ULONG arg)
{
    AIThread *self = reinterpret_cast<AIThread*>(arg);
    self->Run();
}

void AIThread::Run()
{
    ULONG actual_flags = 0;
  
    while (true) {
        tx_event_flags_get(&events, EVENT_AI_TRIGGER, TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);
        while (true) {
            auto& model = static_cast<FrontendApplication*>(FrontendApplication::getInstance())->getModel();
            model.StartAiCapture();
            tx_event_flags_get(&events, EVENT_AI_CAPTURE, TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);
            model.StartAiPostProcess();
            od_pp_out_t *res = GetResult_AI();
            od_pp_outBuffer_t *rois = res->pOutBuff;
            uint32_t nb_rois = res->nb_detect;
            
            model.setAiInfo(nb_rois);
            for (int32_t i = 0; i < nb_rois; i++) {
                uint16_t RectWidth = (uint16_t) (rois[i].width * ((float32_t) 640));
                uint16_t RectHeight = (uint16_t) (rois[i].height * ((float32_t) 480));
                uint16_t Xpos = (uint16_t)((rois[i].x_center - rois[i].width / 2) * ((float32_t)640));
                uint16_t Ypos = (uint16_t)((rois[i].y_center - rois[i].height / 2) * ((float32_t)480));
                AI_Result input = {
                    .x = Xpos,
                    .y = Ypos,
                    .width = RectWidth,
                    .height = RectHeight
                };
                model.setAICoordinates(i, input);
            }
        }
    }
}
