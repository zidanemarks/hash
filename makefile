QUIT :=
#tool macros
CC:=g++
CCFLAG:=-std=c++17
DBGFLAG:= -g
CCOBJFLAG:= $(CCFLAG) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

ifeq ($(OS),Windows_NT)
 RM:=del
else
 RM:=rm -rf
endif

# compile macros
TARGET_NAME := main
ifeq ($(OS),Windows_NT)
 TARGET_NAME:=$(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
MAIN_SRC := src/test.c

#src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
              $(TARGET_DEBUG) \
              $(DISTCLEAN_LIST)

# default rule
default: all

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) $(CCFLAG) -o $@ $?

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAG) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAG) $(DBGFLAG) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CCFLAG) $(DBGFLAG) $? -o $@

# phony rules
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	$(QUIET)echo CLEAN $(CLEAN_LIST)
	$(QUIET)$(RM) $(OBJ_PATH)\*.o
	$(QUIET)$(RM) $(BIN_PATH)\*.exe
	$(QUIET)$(RM) $(DBG_PATH)\*.o
	$(QUIET)$(RM) $(DBG_PATH)\*.exe

.PHONY: distclean
distclean:
	$(QUITE)echo CLEAN $(CLEAN_LIST)
	$(QUITE)$(RM)  $(DISTCLEAN_LIST)