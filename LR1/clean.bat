@echo off
echo Cleaning build artifacts...

cd /d "%~dp0"
if exist build rmdir /s /q build
if exist dist rmdir /s /q dist

echo Done.
