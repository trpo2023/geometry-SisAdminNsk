APP_NAME = geometry
LIB_NAME = libgeometry

source_dirs = src/libgeometry test_src/test_lib

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I,$(source_dirs)) -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = cpp
CC = g++

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)


.PHONY: all clean test
all: $(APP_PATH)

-include $(wildcard *.d) 

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	$(RM) $(test_exe)
	

Test_Name = test_project
Test_Path = obj/test_src
test_exe = bin/$(Test_Name)
Test_src = test_src
Test_lib = test_lib
test:$(test_exe)

$(test_exe):$(Test_Path)/$(Test_Name)/main.o $(Test_Path)/$(Test_lib)/test.o $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	
$(Test_Path)/$(Test_lib)/%.o: $(Test_Path)/$(Test_lib)/%.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(Test_Path)/$(Test_Name)/main.o: $(Test_src)/$(Test_Name)/main.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@