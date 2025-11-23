CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = banking_system
SOURCES = main.cpp BankingSystem.cpp Account.cpp Transaction.cpp
HEADERS = BankingSystem.h Account.h Transaction.h
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run