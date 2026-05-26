CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRCS = main.cpp ATM.cpp BankAccount.cpp
TARGET = atm

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
