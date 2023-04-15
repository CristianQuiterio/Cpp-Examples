@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\MinGW\bin;%DRIVE_LETTER%\MinGW\msys\1.0\bin;c:\Windows;c:\Windows\system32

g++ -c Keyboard.cpp
g++ -c Random.cpp
g++ -c String.cpp
g++ -c ReadFile.cpp
g++ -c WriteFile.cpp
g++ -c PlayerGuessDriver.cpp
g++ -c ComputerGuessDriver.cpp

g++ -o PlayerGuess.exe PlayerGuessDriver.o ComputerGuessDriver.o ReadFile.o WriteFile.o String.o Keyboard.o Random.o
