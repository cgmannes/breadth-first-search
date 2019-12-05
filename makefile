CXX = g++
CXXFLAGS = -c
NAME = "driver"

all: driver

driver: driver.o
	@echo "creating executable driver"
	$(CXX) driver.o -o $(NAME)

driver.o: driver.cpp
	@echo "creating a3_ece.o"
	$(CXX) $(CXXFLAGS) driver.cpp

run: all
	@echo "Running..."
	./$(NAME)

clean:
	@echo "cleaning..."
	rm *.o driver



