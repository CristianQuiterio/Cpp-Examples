@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\MinGW\bin;%DRIVE_LETTER%\MinGW\msys\1.0\bin;%DRIVE_LETTER%\MinGW\gtkmm3\bin;%DRIVE_LETTER%\MinGW\gtk\bin;c:\Windows;c:\Windows\system32

g++ -c DequeDriver.cpp
g++ -c Widget.cpp
g++ -c InventoryManager.cpp
g++ -o DequeDriver.exe DequeDriver.o Widget.o InventoryManager.o