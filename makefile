#op macros
QUIT :=@

# path macros
BIN_PATH := bin
OBJ_PATH := obj
HSH_PATH := src
TST_PATH := test
BST_PATH := boost_wrapper
DBG_PATH := debug
ifeq ($(OS), Windows_NT)
#INC_PATH := D:\project\hash
INC_PATH := `pwd`
else
INC_PATH := ${PWD}/include
endif

# configuration parameter
BOOST_INC_PATH=/usr/include/python2.7
BOOSTINCFLAG=-I${BOOST_INC_PATH}
BOOSTLDFLAG=-lpython2.7 -lboost_python -lboost_thread -lboost_system -lpthread
BOOST ?= 1
BOOST_TARGET_NAME := keyvaluehash.so
BOOST_TARGET :=$(BIN_PATH)/$(BOOST_TARGET_NAME)
BOOST_TARGET_DBG :=$(DBG_PATH)/$(BOOST_TARGET_NAME)

#tool macros
CC:=g++
CCFLAG:=-std=c++17
DBGFLAG:= -g
CCOBJFLAG:= $(CCFLAG) -c
INCFLAG := -I$(INC_PATH)

ifeq ($(BOOST), 1) 
  INCFLAG := $(INCFLAG) $(BOOSTINCFLAG)
endif

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
BST_SRC := $(foreach x, $(BST_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SRC := $(filter-out $(wildcard  $(HSH_PATH)/main*), $(HSH_SRC) $(TST_SRC)) 
BOOST_SRC := $(filter-out $(wildcard  $(HSH_PATH)/main*), $(HSH_SRC) $(BST_SRC))
#SRC := $(HSH_SRC) $(TST_SRC) 
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_BOOST_DBG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(BST_SRC)))))
OBJ_BOOST := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(BST_SRC)))))

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

$(OBJ_PATH)/%.o: $(BST_PATH)/%.c*
	$(CC) -o $@ $< $(INCFLAG) $(CCOBJFLAG)

$(DBG_PATH)/%.o: $(HSH_PATH)/%.c*
	$(CC) $(INCFLAG) $(CCOBJFLAG) $(DBGFLAG) -o $@ $<

$(DBG_PATH)/%.o: $(TST_PATH)/%.c*
	$(CC) $(INCFLAG) $(CCOBJFLAG) $(DBGFLAG) -o $@ $<

$(DBG_PATH)/%.o: $(BST_PATH)/%.c*
	$(CC) $(INCFLAG) $(CCOBJFLAG) $(DBGFLAG) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(INCFLAG) $(CCFLAG) $(DBGFLAG) $? -o $@

$(BOOST_TARGET): $(OBJ_BOOST) $(OBJ)
	echo "hello2"
	$(CC)  -o $@ $? $(CCFLAG) $(BOOSTLDFLAG)

$(BOOST_TARGET_DBG):$(OBJ_BOOST_DBG) $(OBJ_DEBUG)
	$(CC) $(CCFLAG) $(BOOSTLDFLAG) $(DBGFLAG) -o $@ $?

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
	$(QUIET)$(RM) $(BIN_PATH)/$(TARGET_NAME)

.PHONY: distclean
distclean:
	$(QUITE)echo CLEAN $(CLEAN_LIST)
	$(QUITE)$(RM)  $(DISTCLEAN_LIST)

var:
	$(QUITE)echo $(SRC)
	$(QUITE)echo $(OBJ)
	$(QUITE)echo $(OBJ_PATH)/%.o 
	$(QUITE)echo $(BOOST_TARGET)
	$(QUITE)echo $(OBJ_BOOST)

# make for test and all platform test
.PHONY: boost boost_debug

boost: $(BOOST_TARGET)

boost_debug:$(BOOST_TARGET_DBG)




