CC := g++ # This is the main compiler
SRCDIR := src
BUILDDIR := build
MAINBUILDDIR := main/build
MAINDIR := main
TARGET := bin/Play
TARGET1 := bin/Create

SRCEXT := cpp
CFLAGS := --std=c++11 -Wall
INC := -I include
LDLIBS := -lncurses

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(TARGET) $(TARGET1)
# $(MAINBUILDDIR)/Play.o: $(CC) $(CFLAGS) $(INC) -c -o $(MAINBUILDDIR)/Play.o main/Play.cpp

$(TARGET): $(OBJECTS)
	@echo " Compiling Play...";
	$(CC) $(CFLAGS) $(INC) -c -o $(MAINBUILDDIR)/Play.o main/Play.cpp
	@echo " Linking Play...";
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ $(MAINBUILDDIR)/Play.o -o $(TARGET) $(LDLIBS)

$(TARGET1): $(OBJECTS)
	@echo " Compiling Create...";
	$(CC) $(CFLAGS) $(INC) -c -o $(MAINBUILDDIR)/Create.o main/Create.cpp
	@echo " Linking Create...";
	@echo " $(CC) $^ -o $(TARGET1)"; $(CC) $^ $(MAINBUILDDIR)/Create.o -o $(TARGET1) $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR);
	@mkdir -p $(MAINBUILDDIR);
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Create.o: main/Create.cpp
# 	$(CC) $(CFLAGS) $(INC) -c -o $(MAINBUILDDIR)/Create.o main/Create.cpp

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)";
	$(RM) -r $(BUILDDIR) $(MAINBUILDDIR) $(TARGET) $(TARGET1)

.PHONY : all
.PHONY: clean
