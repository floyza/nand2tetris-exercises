##
# Nand2Tetris Assembler
#
# @file
# @version 0.1

SRC_DIR=src
OBJ_DIR=obj

TARGET = asm-n2t
_OBJS = $(wildcard *.o)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp))
CXXFLAGS += -std=c++17 -Wall -Wextra -MMD
DEPENDS = $(OBJS:.o=.d)

ifndef RELEASE
CXXFLAGS += -ggdb -O0
else
ifdef DEBUG
CXXFLAGS += -ggdb
endif
CXXFLAGS += -O2 -DNDEBUG
endif


all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

-include $(OBJ_DIR)/*.d

.PHONY: clean

clean:
	${RM} $(TARGET) $(OBJS) $(DEPENDS)

# end
