@echo off
cd "%~dp0"
gcc -Os -s -mwindows -nostdlib WinMain.c -lKernel32 -lOle32 -lShell32 -o AppLifecycleOptOut.exe
upx --best --ultra-brute AppLifecycleOptOut.exe>nul 2>&1