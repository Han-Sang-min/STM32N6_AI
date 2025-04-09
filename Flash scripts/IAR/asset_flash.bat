@echo off
setlocal

set "CUBEPROGRAMMER_TOOL_PATH=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin"
set "BIN_DIR=%~dp0..\..\Secure_nsclib\"

:: Navigate to the binarys's directory
pushd "%BIN_DIR%"

:: Extract the asset area from the original BIN file
srec_cat "STM32N6570-DK_Appli.hex" -intel -crop 0x70200000 0x72FFFFFF -offset -0x70200000 -o "assets.bin" -binary

:: Sign the app 
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_SigningTool_CLI.exe" -s -bin "assets.bin" -nk -of 0x80000000 -t fsbl -o "assets_trusted.bin" -hv 2.3 -dump "assets_trusted.bin"

:: Load the binary
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_Programmer_CLI.exe" -c port=SWD mode=HOTPLUG AP=1 -el "%
CUBEPROGRAMMER_TOOL_PATH%\ExternalLoader\MX66UW1G45G_STM32N6570-DK.stldr" -d "%BIN_DIR%assets_trusted.bin" 0x70200000

:: Return to the original directory
popd

:: Pause the script to view any messages
pause
