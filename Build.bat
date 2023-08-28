@echo off
cd "%~dp0"
gcc -municode -O3 -mwindows -s WinMain.c -lole32 -o AppLifecycleOptOut.exe 
upx --best --ultra-brute AppLifecycleOptOut.exe>nul 2>&1