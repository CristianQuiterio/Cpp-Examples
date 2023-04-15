AutomatedMakefile = am
CC = g++

FILES = InventoryDriver.o InventoryManager.o Widget.o
EXECUTABLE = Inventory.exe

PROJECT_PATH = $(PROJECT_DIR)
INC_DIRS = -I$(PROJECT_PATH)/CSC2110/
LIB_DIRS = -L$(PROJECT_PATH)/CSC2110/
LIBS = -lCSC2110

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

all: Project	

Project: 			$(FILES)
				$(LINK) $(EXECUTABLE) $(FILES) $(LIBS)

InventoryDriver.o:		InventoryManager.h InventoryDriver.cpp
				$(COMPILE) InventoryDriver.cpp

Widget.o:			Widget.cpp
				$(COMPILE) Widget.cpp

InventoryManager.o:		QueueDeque.h StackDeque.h DequeArray.h InventoryManager.h InventoryManager.cpp
				$(COMPILE) InventoryManager.cpp