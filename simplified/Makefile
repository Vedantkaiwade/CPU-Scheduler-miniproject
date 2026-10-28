CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCS     = Process.cpp Sorting.cpp Structures.cpp Scheduler.cpp main.cpp
TARGET   = cpu_scheduler.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	.\$(TARGET)

clean:
	-del /F /Q $(TARGET) 2>nul
