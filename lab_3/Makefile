# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -Wextra -Iinclude

# Папки
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/ProcessProgram

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
	rm -rf $(BUILDDIR) log.txt

.PHONY: all clean
