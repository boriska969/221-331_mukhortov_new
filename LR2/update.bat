@echo off
echo Updating C:\LR2xfer with the latest driver build...

set SRC=%~dp0PassThroughCrypt\x64\Debug

if not exist "%SRC%\passThrough.sys" (
    echo [ERROR] %SRC%\passThrough.sys not found. Build the driver in Visual Studio first.
    pause
    exit /b 1
)

if not exist "C:\LR2xfer" mkdir "C:\LR2xfer"

copy /y "%SRC%\passThrough.sys" "C:\LR2xfer\passThrough.sys"
copy /y "%SRC%\passThrough.inf" "C:\LR2xfer\passThrough.inf"
copy /y "%SRC%\passThrough\passthrough.cat" "C:\LR2xfer\passthrough.cat"

set TESTAPP=%~dp0TestApp\out\build\x64-Debug\test_file_io.exe
if exist "%TESTAPP%" (
    copy /y "%TESTAPP%" "C:\LR2xfer\test_file_io.exe"
) else (
    echo [WARNING] test_file_io.exe not found at %TESTAPP% - not updated.
)

echo.
echo Done. The files are now up to date in C:\LR2xfer (visible as L: in the VM).
pause
