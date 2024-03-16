TARGET := b7k

SRCDIR := ./src
BUILDDIR := ./build
SCRIPTDIR := ./scripts
SAMPLEDIR := ./samples

SRCS := $(shell find $(SRCDIR) -type f \( -name "*.c" -or -name "*.cpp" \))
OBJS := $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SRCS:$(SRCDIR)/%=%))))
$(warning $(OBJS))
DEPS := $(OBJS:.o=.d)

INCDIR := $(SRCDIR)/include
INCFLAGS := $(addprefix -I, $(INCDIR))

$(warning $(INCFLAGS))

CC := clang
CXX := clang++
LD := ld.lld

CFLAGS := -O2 -Wall -Wextra
CXXFLAGS := -O2 -Wall -Wextra -std=c++20
LDFLAGS := -O2 -Wall -Wextra

CPPFLAGS := $(INCFLAGS) -MMD -MP

ARG = brainfuck.bf

.PHONY: all clean run

all: executable

executable: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $^ -o $@
#	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*

run: executable
	$(BUILDDIR)/b7k $(SAMPLEDIR)/$(ARG)

-include $(DEPS)
