:: @echo off
setlocal

set "CUBEPROGRAMMER_TOOL_PATH=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin"
set "BIN_DIR=%~dp0..\..\Secure_nsclib\"
set "FSBL_DIR=%~pd0..\..\EWARM\FSBL\STM32N6570-DK_FSBL\Exe\"

:: Navigate to the binarys's directory
pushd "%BIN_DIR%"

:: Extract the code area from the original BIN file
srec_cat "STM32N6570-DK_Appli.hex" -intel -crop 0x70100400 0x701FFFFF -offset -0x70100400 -o "code.bin" -binary

:: Sign the app (Appli)
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_SigningTool_CLI.exe" -s -bin "code.bin" -nk -of 0x80000000 -t fsbl -o "%BIN_DIR%code_trusted.bin" -hv 2.3 -dump "%BIN_DIR%code_trusted.bin" 

:: Load the Appli binary
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_Programmer_CLI.exe" -c port=SWD mode=HOTPLUG AP=1 -el "%CUBEPROGRAMMER_TOOL_PATH%\ExternalLoader\MX66UW1G45G_STM32N6570-DK.stldr" -d "%BIN_DIR%code_trusted.bin" 0x70100000

:: Load the FSBL binary
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_Programmer_CLI.exe" -c port=SWD mode=HOTPLUG AP=1 -el "%CUBEPROGRAMMER_TOOL_PATH%\ExternalLoader\MX66UW1G45G_STM32N6570-DK.stldr" -d "%FSBL_DIR%STM32N6570-DK_FSBL.bin" 0x34000400

:: Move PC to Reset_handler
"%CUBEPROGRAMMER_TOOL_PATH%\STM32_Programmer_CLI.exe" -c port=SWD mode=HOTPLUG AP=1 -g 0x34000400 -corereg pc=0x3400a9c9 -corereg

:: Return to the original directory
popd

:: Pause the script to view any messages
pause
