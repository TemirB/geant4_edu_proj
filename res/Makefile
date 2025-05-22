# Название исполняемого файла и исходника
TARGET = process
SRC = process.cpp

# Настройки ROOT
ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

# Компилятор и флаги
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $< -o $@ $(ROOTLIBS)

clean:
	rm -f $(TARGET) *.o
