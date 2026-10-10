@echo off

echo ============================================================
echo   LR1 - build via CMake (preset mingw-release)
echo ============================================================
echo.

cd /d "%~dp0"

if exist "LR1_PassManager\credentials.json.enc" goto :encrypt_done

echo [1/3] Generating encrypted credentials file...
cd /d "%~dp0LR1_PassManager"

where python >nul 2>&1
if errorlevel 1 goto :no_python

python encrypt_credentials.py 1234
if errorlevel 1 goto :encrypt_failed

cd /d "%~dp0"
goto :encrypt_done

:no_python
echo [ERROR] Python not found. Install Python 3 and add it to PATH.
exit /b 1

:encrypt_failed
echo [ERROR] Failed to generate credentials.json.enc
exit /b 1

:encrypt_done
echo [1/3] credentials.json.enc is ready.

echo [2/3] CMake configure...
cmake --preset mingw-release
if errorlevel 1 goto :configure_failed
goto :configure_done

:configure_failed
echo [ERROR] CMake configure failed.
exit /b 1

:configure_done
echo [3/3] CMake build...
cmake --build build --preset mingw-release
if errorlevel 1 goto :build_failed
goto :build_done

:build_failed
echo [ERROR] CMake build failed.
exit /b 1

:build_done
echo.
echo ============================================================
echo   DONE!
echo ============================================================
echo.
echo   Output folder:  build\bin
echo   PIN:            1234
echo.
echo   Run password manager:
echo     cd build\bin
echo     LR1_PassManager.exe
echo.
echo   Run via Protector (anti-debug wrapper):
echo     cd build\bin
echo     LR1_Protector.exe
echo.
echo ============================================================
pause
