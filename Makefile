CC=g++
LD=g++
CCFLAGS=-I. -c -std=c++0x
LDFLAGS=-lpng
CCDEBUGFLAGS=-g
LDDEBUGFLAGS=
CCRELEASEFLAGS=-O3 -DNDEBUG
LDRELEASEFLAGS=-O3
DEBUG_EXECUTABLE=cgrayd
RELEASE_EXECUTABLE=cgray
SRC_DIRS=core rt main
INT_DIR = build
DEBUG_INT_DIR = build/debug
RELEASE_INT_DIR = build/release
DEP_INT_DIR = build/dep


CPP_FILES := $(shell find $(SRC_DIRS) -name *.cpp)
DEBUG_OBJ_FILES := $(patsubst %.cpp,%.o,$(addprefix $(DEBUG_INT_DIR)/,$(CPP_FILES)))
RELEASE_OBJ_FILES := $(patsubst %.cpp,%.o,$(addprefix $(RELEASE_INT_DIR)/,$(CPP_FILES)))
DEP_FILES := $(patsubst %.cpp,%.d,$(addprefix $(DEP_INT_DIR)/,$(CPP_FILES)))

all: debug

debug: $(DEBUG_EXECUTABLE)

release: $(RELEASE_EXECUTABLE)

$(DEBUG_EXECUTABLE) : $(DEBUG_OBJ_FILES)
	$(LD) $^ $(LDDEBUGFLAGS) $(LDFLAGS) -o $@

$(RELEASE_EXECUTABLE) : $(RELEASE_OBJ_FILES)
	$(LD) $^ $(LDRELEASEFLAGS) $(LDFLAGS) -o $@

$(DEBUG_INT_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(CCDEBUGFLAGS) $< -o $@

$(RELEASE_INT_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(CCRELEASEFLAGS) $< -o $@

$(DEP_INT_DIR)/%.d : %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -MM $< -MT $(patsubst %.cpp,%.o,$(addprefix $(DEBUG_INT_DIR)/,$<)) -MT $(patsubst %.cpp,%.o,$(addprefix $(RELEASE_INT_DIR)/,$<)) -MT $(patsubst %.cpp,%.d,$(addprefix $(DEP_INT_DIR)/,$<)) >> $@

clean:
	@rm -r -f $(INT_DIR)
	@rm -f $(DEBUG_EXECUTABLE)
	@rm -f $(RELEASE_EXECUTABLE)

depend : $(DEP_FILES)

-include $(DEP_FILES)

.PHONY: all debug release clean
.SECONDARY:
