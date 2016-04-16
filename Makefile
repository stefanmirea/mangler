CC = g++
CFLAGS = -Wall -std=gnu++0x -g -DDEBUG
EXE = mangler
INCLUDE_FLAGS = -Iinclude
SRC = src

all: $(EXE)

$(EXE): build
	$(CC) $(INCLUDE_FLAGS) $(SRC)/*.o -o $(EXE)

build: $(patsubst %.cpp, %.o, $(wildcard $(SRC)/*.cpp))

$(SRC)/%.o : $(SRC)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS) $< -o $@

clean:
	rm -f $(EXE) $(SRC)/*.o *~ &>/dev/null
