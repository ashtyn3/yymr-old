CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++14 -ggdb -fpermissive -Wwrite-strings

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib
LIBRARIES  := 
EXECUTABLE := main


all: $(BIN)/$(EXECUTABLE)

print-%:
	@echo '$*'='$($*)'

run: clean all
	clear
	@echo "Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "Building..."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	@echo "Clearing..."
	-rm $(BIN)/*

