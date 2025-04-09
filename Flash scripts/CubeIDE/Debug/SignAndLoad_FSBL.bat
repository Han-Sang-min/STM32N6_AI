@echo off
setlocal

set "CUBEPROGRAMMER_TOOL_PATH=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin"
set "BIN_DIR=%~pd0..\..\..\STM32CubeIDE\FSBL\Debug\"
set "OUT_DIR=%~pd0..\..\..\STM32CubeIDE\FSBL\Debug\"

:: Navigate to the script's directory
pushd "%BIN_DIR%"

:: Sign the app 
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_SigningTool_CLI.exe" -s -bin "%BIN_DIR%STM32N6570-DK_FSBL.bin" -nk -of 0x80000000 -t fsbl -o "%OUT_DIR%STM32N6570-DK_FSBL-trusted.bin" -hv 2.3 -dump "%OUT_DIR%STM32N6570-DK_FSBL-trusted.bin"

:: Load the binary
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_Programmer_CLI.exe" -c port=SWD mode=HOTPLUG AP=1 -el "%CUBEPROGRAMMER_TOOL_PATH%\ExternalLoader\MX66UW1G45G_STM32N6570-DK.stldr" -d "%OUT_DIR%STM32N6570-DK_FSBL-trusted.bin" 0x70000000

:: Return to the original directory
popd

:: Pause the script to view any messages
pause