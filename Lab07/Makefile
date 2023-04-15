AutomatedMakefile = am
CC = g++

FILES =  Problem22_1.o RombergIntegration.o 
EXECUTABLE = Problem.exe

PROJECT_PATH = $(PROJECT_DIR)
INC_DIRS = -I$(PROJECT_PATH)/CSC2110/
LIB_DIRS = -L$(PROJECT_PATH)/CSC2110/
LIBS = -lCSC2110

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

all: Project

Project: 			$(FILES)
				$(LINK) $(EXECUTABLE) $(FILES) $(LIBS)

RombergIntegration.o:		multiVarFunction.h Double.h QueueLinked.h RombergIntegration.h NextNode.h RecursiveIntegration.h RombergIntegration.cpp
				$(COMPILE) RombergIntegration.cpp

Problem22_1.o:			RombergIntegration.h RecursiveIntegration.h Problem22_1.h Problem22_1.cpp
				$(COMPILE) Problem22_1.cpp
