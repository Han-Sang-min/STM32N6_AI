
![image](https://github.com/user-attachments/assets/a205e8b9-c64d-41b8-8a27-fb58e5840302)
Example Image

#  Development Environment

- **Board**:  STM32N6570-DK (Discovery Kit)
- **IDE**:  IAR Embedded Workbench / TouchGFX Designer
- **RTOS**:  Azure RTOS ThreadX
- **Toolchain**:  IAR ARM Compiler (EWARM)
- **Graphics Framework**:  TouchGFX

# Execution Steps

1. Connect the `STM32N6570-DK` to the PC and set Boot1 to High.
2. Open `EWARM/Project.eww`.
3. Build both `STM32N6570-DK_Appli` & `STM32N6570-DK_FSBL` projects.
4. Navigate to the `Flash scripts/IAR` directory.
5. Execute `SignAndLoad_App.bat` & `SignAndLoad_FSBL.bat` scripts.
6. Set **Boot1** to Low and perform a Reset.

# Camera Module

**Overview**

- The **CameraThread** is responsible for handling camera frame processing.
- When the **EVENT_START_CAMERA_THREAD** event is triggered, the CameraThread is initiated.
- For every **EVENT_FRAME_INTERRUPT** event, a new camera frame is ready:
    - The Model notifies the Presenter to update the camera feed.
    - `swap_bitmap()` is called to handle double-buffering.
- The Presenter detects the model state changes in its `tick()` method and updates the View accordingly.

### Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Model as Model
    participant CameraThread as CameraThread::Run()
    participant Presenter as Presenter::tick()
    participant View as View

    Note over CameraThread: Waiting for EVENT_START_CAMERA_THREAD
    activate CameraThread
    CameraThread->>CameraThread: Loop: Frame interrupt occurs

    loop Frame interrupt occurs
        Note over CameraThread: Waiting for EVENT_FRAME_INTERUPT
        CameraThread->>Model: setCameraRefreshRequest()
        Note over Model: Refresh flag set
        CameraThread->>Model: swap_bitmap()
    end

    deactivate CameraThread

    Note over Presenter: Check at every tick() interval.
    Presenter->>Model: isCameraRefreshNeeded()
    alt If an update request is present ✅
        Presenter->>Model: getCurrBitmap()
        Presenter->>View: swapCamBuf()
        Presenter->>Model: ProcessCameraBackground()
        Presenter->>View: refreshCameraArea()
        Presenter->>Model: clearCameraRefresh()
    end

```

# AI

**개요**

이 프로젝트에서 **AI 처리**는 별도의 스레드(`AIThread`)에서 수행됩니다.

카메라에서 이미지를 캡처한 후, AI 스레드는 이를 분석하여 객체 인식 결과를 얻고, 결과를 `Model`에 전달하여 화면에 표시할 수 있도록 준비합니다.

- **AIThread**는 이벤트 기반으로 동작합니다 (`EVENT_AI_TRIGGER`, `EVENT_AI_CAPTURE`).
- AI 처리 로직은 외부 C 라이브러리 (`ai_helper_C`)를 호출합니다.
- 결과로 얻은 ROI 정보를 Model에 전달하고, View에서 이를 마커로 시각화합니다.

**시퀸스 다이어그램**

```mermaid
sequenceDiagram
    autonumber
    participant Presenter as Presenter::tick()
    participant AIThread as AIThread::Run()
    participant Model as Model
    participant AIHelper as ai_helper_C (C)
    participant View as View

    Note over AIThread: 대기 중 (EVENT_AI_TRIGGER)

    activate AIThread
    AIThread->>Model: StartAiCapture()
    Model->>AIHelper: Start_Capture()
    Note over AIThread: EVENT_AI_CAPTURE 대기

    AIThread->>Model: StartAiPostProcess()
    Model->>AIHelper: Process_AI()
    AIThread->>AIHelper: GetResult_AI()
    AIHelper-->>AIThread: 객체 정보들 (ROI)

    AIThread->>Model: setAiInfo(...)
    Note right of Model: AI 데이터 준비 플래그 설정
    AIThread->>Model: setAICoordinates(...)

    deactivate AIThread

    Note over Presenter: tick 주기마다 확인
    Presenter->>Model: isAIDataReady()
    alt AI 데이터 준비됨 ✅
        Presenter->>View: clearAIMarker()
        Presenter->>Model: getAICoordinates()
        Presenter->>Model: getAiInfo()
        Presenter->>View: updateAIMarker()
    end

```

# MVP Pattern

| 구성 요소 | 담당 역할 |
| --- | --- |
| **Model** | 로직 처리 (AI 처리, 카메라, 데이터 핸들링 등) |
| **Presenter** | `tick()` 같은 주기 함수에서 Model의 상태 확인 및 View에 전달 |
| **View** | 화면 갱신 및 유저에게 보여지는 UI 처리 |

```mermaid
sequenceDiagram
    autonumber
    participant tickFunc as Presenter::tick()
    participant model as Model
    participant view as View

    tickFunc->>model: isCameraRefreshNeeded()
    alt 카메라 갱신 필요✅
        tickFunc->>model: clearflagCameraRefresh()
        tickFunc->>model: isAIDataReady()
        alt AI 데이터 준비됨✅
            tickFunc->>view: clearAIMarker()
            tickFunc->>model: getAICoordinates(coor)
            tickFunc->>model: getAiInfo(&info)
            tickFunc->>view: updateAIMarker(info, *coor)
        end
        tickFunc->>model: getCurrBitmap(&id)
        tickFunc->>view: swapCamBuf(id)

        tickFunc->>model: ProcessCameraBackground()
        tickFunc->>view: refreshCameraArea()
    else
        tickFunc-->>tickFunc: None
    end

```

# 클래스 다이어그램

```mermaid
---
config:
  look: classic
  class:
    hideEmptyMembersBox: true
---

classDiagram
    class AIThread {
        +static getEventGroup()
        +getInstance()
        +init()
        +Run()
    }

    class CameraThread {
        +static getEventGroup()
        +getInstance()
        +init()
        +Run()
    }

    class IMX335CameraDriver {
        +Init()
        +Start(...)
        +DoubleBufferStart(...)
        +BackgroundProcess()
        +Resume()
        +Suspend()
    }

    class ai_helper_C{
        Init_AI()
        Start_Capture()
        Process_AI()
        GetResult_AI()
    }

    class Model {
        +setupModel()
        +StartAiCapture()
        +StartAiPostProcess()
        +swap_bitmap()
        +ProcessCameraBackground()
    }

    class CameraPresenter {
        +activate()
        +deactivate()
        +tick()
        +camera_refrash_event()
        +ai_data_ready_event()
    }

    class CameraView {
        +setupScreen()
        +updateAIMarker(info, coor)
        +clearAIMarker()
        +refreshCameraArea()
        +swapCamBuf(id)
        +setFpsValue(fps)
    }

    CameraPresenter --> Model
    CameraPresenter --> CameraView
    Model *-- IMX335CameraDriver
    Model --> ai_helper_C
		AIThread --> ai_helper_C
    AIThread --> Model
    CameraThread --> Model
```
