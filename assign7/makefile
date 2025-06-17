CXX := g++
CXXFLAGS := -std=c++17 -pthread -Iinclude -Wall -Wextra

SRCDIR := src
INCDIR := include

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := game

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 編譯 src 底下的 .cpp 產生對應的 .o 檔
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
