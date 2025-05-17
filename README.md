
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

**Overview**

In this project, AI processing is performed in a dedicated thread (`AIThread`).
After the camera captures an image, the AI thread analyzes it to obtain object-recognition results, passes those results to the `Model`, and prepares them so the `View` can display them.
- AIThread operates on an event basis (`EVENT_AI_TRIGGER`, `EVENT_AI_CAPTURE`).
- The AI logic calls an external C library (`ai_helper_C`).
- The resulting ROI information is sent to the `Model`, and the `View` visualizes it with markers.

### Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Presenter as Presenter::tick()
    participant AIThread as AIThread::Run()
    participant Model as Model
    participant AIHelper as ai_helper_C (C)
    participant View as View

    Note over AIThread: Waiting (EVENT_AI_TRIGGER)

    activate AIThread
    AIThread->>Model: StartAiCapture()
    Model->>AIHelper: Start_Capture()
    Note over AIThread: Waiting for EVENT_AI_CAPTURE

    AIThread->>Model: StartAiPostProcess()
    Model->>AIHelper: Process_AI()
    AIThread->>AIHelper: GetResult_AI()
    AIHelper-->>AIThread: Object information (ROI)

    AIThread->>Model: setAiInfo(...)
    Note right of Model: Set AI data-ready flag
    AIThread->>Model: setAICoordinates(...)

    deactivate AIThread

    Note over Presenter: Checked every tick cycle
    Presenter->>Model: isAIDataReady()
    alt AI data ready ✅
        Presenter->>View: clearAIMarker()
        Presenter->>Model: getAICoordinates()
        Presenter->>Model: getAiInfo()
        Presenter->>View: updateAIMarker()
    end

```

# MVP Pattern

| Component | Responsibility |
| --- | --- |
| **Model** | Core logic (AI processing, camera control, data handling, etc.) |
| **Presenter** | In periodic functions such as `tick()`, checks `Model` state and forwards it to the `View` |
| **View** | Updates the screen and handles the UI shown to the user |

```mermaid
sequenceDiagram
    autonumber
    participant tickFunc as Presenter::tick()
    participant model as Model
    participant view as View

    tickFunc->>model: isCameraRefreshNeeded()
    alt Camera refresh needed ✅
        tickFunc->>model: clearflagCameraRefresh()
        tickFunc->>model: isAIDataReady()
        alt AI data ready ✅
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

# Class Diagram

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
