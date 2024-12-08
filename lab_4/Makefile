# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -Wextra -Iinclude

# Папки
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/TemperatureLogger

# Файлы
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Правила/задачи
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p logs
	$(CXX) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) logs/*.log

.PHONY: all clean
