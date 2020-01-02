TARGET ?= Test.exe
SRC_DIRS ?= ./src
CC = g++ --std=c++11 -Wall

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)

deepclean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
