# Windows Bat
## 周期重启某个指定的程序

@echo off
:start
choice /t 10 /d y /n >nul
cd C:\Users\Administrator\Desktop\XXXX.exe
choice /t 10 /d y /n >nul
taskkill /F /IM XXXX.exe
goto start
