CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lstdc++fs

SOURCES = main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = BankingSystem

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete! Run with: ./$(EXECUTABLE)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "Cleaned up build files"

run: $(EXECUTABLE)
	./$(EXECUTABLE)

help:
	@echo "Available targets:"
	@echo "  make all     - Build the Banking System"
	@echo "  make clean   - Remove build files"
	@echo "  make run     - Build and run the application"
	@echo "  make help    - Show this help message"
