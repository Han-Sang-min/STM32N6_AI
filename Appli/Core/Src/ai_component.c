#include "ai_component.h"

#include "ll_aton_runtime.h"
#include "drv_imx335_camera.h"
#include "app_postprocess.h"

#define MAX_NUMBER_OUTPUT 5

// #ifdef __cplusplus
// extern "C" {
// #endif

volatile int32_t cameraFrameReceived;
uint8_t *nn_in;
float32_t *nn_out[MAX_NUMBER_OUTPUT];
int32_t nn_out_len[MAX_NUMBER_OUTPUT];
uint32_t nn_in_len;
int number_output = 0;

od_pp_out_t pp_output;

yolov2_pp_static_param_t pp_params;

LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);

void Init_AI(void)
{
  const LL_Buffer_InfoTypeDef *nn_in_info = LL_ATON_Input_Buffers_Info_Default();
  const LL_Buffer_InfoTypeDef *nn_out_info = LL_ATON_Output_Buffers_Info_Default();

  nn_in = (uint8_t *) LL_Buffer_addr_start(&nn_in_info[0]);

  /* Count number of outputs */
  while (nn_out_info[number_output].name != NULL)     
  {
    number_output++;
  }
  assert(number_output <= MAX_NUMBER_OUTPUT);

  for (int i = 0; i < number_output; i++)
  {
    nn_out[i] = (float32_t *) LL_Buffer_addr_start(&nn_out_info[i]);
    nn_out_len[i] = LL_Buffer_len(&nn_out_info[i]);
  }

  nn_in_len = LL_Buffer_len(&nn_in_info[0]);

  /*** Post Processing Init ***************************************************/
  app_postprocess_init(&pp_params);
}

void Start_Capture(void)
{
  IMX335_StartCamera(DCMIPP_PIPE2, nn_in, CMW_MODE_SNAPSHOT);
}

void Process_AI(void)
{
  /* run ATON inference */
  LL_ATON_RT_Main(&NN_Instance_Default);

  int32_t ret = app_postprocess_run((void **) nn_out, number_output, &pp_output, &pp_params);
  assert(ret == 0);

  /* Discard nn_out region (used by pp_input and pp_outputs variables) to avoid Dcache evictions during nn inference */
  for (int i = 0; i < number_output; i++)
  {
    float32_t *tmp = nn_out[i];
    SCB_InvalidateDCache_by_Addr(tmp, nn_out_len[i]);
  }
}

od_pp_out_t *GetResult_AI(void)
{
  return &pp_output;
}

// #ifdef __cplusplus
// }
// #endif