#op macros
QUIT :=@

# path macros
BIN_PATH := bin
OBJ_PATH := obj
HSH_PATH := src
TST_PATH := test
DBG_PATH := debug
ifeq ($(OS), Windows_NT)
#INC_PATH := D:\project\hash
INC_PATH := `pwd`
else
INC_PATH := ${PWD}+
endif

#tool macros
CC:=g++
CCFLAG:=-std=c++17
DBGFLAG:= -g
CCOBJFLAG:= $(CCFLAG) -c
INCFLAG := -I$(INC_PATH)

ifeq ($(OS),Windows_NT)
 #RM:=del
 RM:=rm -rf
else
 RM:=rm -rf
endif

# compile macros
TARGET_NAME := test
ifeq ($(OS),Windows_NT)
 TARGET_NAME:=$(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
MAIN_SRC := src/test.c

#src files & obj files
HSH_SRC := $(foreach x, $(HSH_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
TST_SRC := $(foreach x, $(TST_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SRC := $(filter-out $(wildcard  $(HSH_PATH)/main*), $(HSH_SRC) $(TST_SRC)) 
#SRC := $(HSH_SRC) $(TST_SRC) 
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

$(OBJ_PATH)/%.o: $(HSH_PATH)/%.c*
	$(CC) $(INCFLAG) $(CCOBJFLAG) -o $@ $<

$(OBJ_PATH)/%.o: $(TST_PATH)/%.c*
	$(CC) $(INCFLAG) $(CCOBJFLAG) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAG) $(DBGFLAG) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(INCFLAG) $(CCFLAG) $(DBGFLAG) $? -o $@

# phony rules
.PHONY: all
#all: clean $(TARGET)
all: clean $(TARGET)


.PHONY: debug
debug: clean $(TARGET_DEBUG)

.PHONY: clean
clean:
	$(QUIET)echo CLEAN $(CLEAN_LIST)
	$(QUIET)$(RM) $(OBJ_PATH)/*.o
	$(QUIET)$(RM) $(BIN_PATH)/*.exe
	$(QUIET)$(RM) $(DBG_PATH)/*.o
	$(QUIET)$(RM) $(DBG_PATH)/*.exe

.PHONY: distclean
distclean:
	$(QUITE)echo CLEAN $(CLEAN_LIST)
	$(QUITE)$(RM)  $(DISTCLEAN_LIST)

var:
	echo $(SRC)
	echo $(OBJ)
	echo $(OBJ_PATH)/%.o 
