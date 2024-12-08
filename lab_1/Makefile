# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2

# Папки
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/HelloWorld

# Файлы
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Правила/задачи
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
