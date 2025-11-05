# Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
TARGET = dbms

SOURCES = src/main.cpp src/array.cpp src/doublyLinkedList.cpp \
          src/forwardList.cpp src/queue.cpp src/redBlackTree.cpp \
          src/stack.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean