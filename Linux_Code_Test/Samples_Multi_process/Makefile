CXX := g++
CXXFLAGS := -c -Wall
DEBUGFLAGS := -g

PROJECT_TEST_PIPE1 := test_pipe1
PROJECT_TEST_PIPE2 := test_pipe2
PROJECT_TEST_PIPE3 := test_pipe3
PROJECT_TEST_PIPE4 := test_pipe4
PROJECT_TEST_PIPE5 := test_pipe5

test_pipe1: $(PROJECT_TEST_PIPE1)
test_pipe2: $(PROJECT_TEST_PIPE2)
test_pipe3: $(PROJECT_TEST_PIPE3)
test_pipe4: $(PROJECT_TEST_PIPE4)
test_pipe5: $(PROJECT_TEST_PIPE5)

PROJECT_TEST_SIGNAL1 := test_signal1
PROJECT_TEST_SIGNAL2 := test_signal2
PROJECT_TEST_SIGNAL3 := test_signal3
PROJECT_TEST_SIGNAL4 := test_signal4
PROJECT_TEST_SIGNAL5 := test_signal5

test_signal1: $(PROJECT_TEST_SIGNAL1)
test_signal2: $(PROJECT_TEST_SIGNAL2)
test_signal3: $(PROJECT_TEST_SIGNAL3)
test_signal4: $(PROJECT_TEST_SIGNAL4)
test_signal5: $(PROJECT_TEST_SIGNAL5)

PROJECT_TEST_FORK1 := test_fork1
PROJECT_TEST_FORK2 := test_fork2
PROJECT_TEST_FORK3 := test_fork3
PROJECT_TEST_FORK4 := test_fork4

test_fork1: $(PROJECT_TEST_FORK1)
test_fork2: $(PROJECT_TEST_FORK2)
test_fork3: $(PROJECT_TEST_FORK3)
test_fork4: $(PROJECT_TEST_FORK4)

$(PROJECT_TEST_FORK4):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_FORK4).cpp
	$(CXX) -o $(PROJECT_TEST_FORK4) $(PROJECT_TEST_FORK4).o
	#./$(PROJECT_TEST_FORK4)

$(PROJECT_TEST_FORK3):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_FORK3).cpp
	$(CXX) -o $(PROJECT_TEST_FORK3) $(PROJECT_TEST_FORK3).o
	#./$(PROJECT_TEST_FORK3)

$(PROJECT_TEST_FORK2):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_FORK2).cpp
	$(CXX) -o $(PROJECT_TEST_FORK2) $(PROJECT_TEST_FORK2).o
	#./$(PROJECT_TEST_FORK2)

$(PROJECT_TEST_FORK1):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_FORK1).cpp
	$(CXX) -o $(PROJECT_TEST_FORK1) $(PROJECT_TEST_FORK1).o
	#./$(PROJECT_TEST_FORK1)

$(PROJECT_TEST_SIGNAL5):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_SIGNAL5).cpp
	$(CXX) -o $(PROJECT_TEST_SIGNAL5) $(PROJECT_TEST_SIGNAL5).o
	#./$(PROJECT_TEST_SIGNAL5)

$(PROJECT_TEST_SIGNAL4):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_SIGNAL4).cpp
	$(CXX) -o $(PROJECT_TEST_SIGNAL4) $(PROJECT_TEST_SIGNAL4).o
	#./$(PROJECT_TEST_SIGNAL4)

$(PROJECT_TEST_SIGNAL2):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_SIGNAL2).cpp
	$(CXX) -o $(PROJECT_TEST_SIGNAL2) $(PROJECT_TEST_SIGNAL2).o
	#./$(PROJECT_TEST_SIGNAL2)

$(PROJECT_TEST_SIGNAL3):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_SIGNAL3).cpp
	$(CXX) -o $(PROJECT_TEST_SIGNAL3) $(PROJECT_TEST_SIGNAL3).o
	#./$(PROJECT_TEST_SIGNAL3)

$(PROJECT_TEST_SIGNAL1):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_SIGNAL1).cpp
	$(CXX) -o $(PROJECT_TEST_SIGNAL1) $(PROJECT_TEST_SIGNAL1).o
	#./$(PROJECT_TEST_SIGNAL1)

$(PROJECT_TEST_PIPE1):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_PIPE1).cpp
	$(CXX) -o $(PROJECT_TEST_PIPE1) $(PROJECT_TEST_PIPE1).o
	./$(PROJECT_TEST_PIPE1)

$(PROJECT_TEST_PIPE2):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_PIPE2).cpp
	$(CXX) -o $(PROJECT_TEST_PIPE2) $(PROJECT_TEST_PIPE2).o
	#./$(PRJECT_TEST_PIPE2)

$(PROJECT_TEST_PIPE3):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_PIPE3).cpp
	$(CXX) -o $(PROJECT_TEST_PIPE3) $(PROJECT_TEST_PIPE3).o
	#./$(PRJECT_TEST_PIPE2)

$(PROJECT_TEST_PIPE4):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_PIPE4).cpp
	$(CXX) -o $(PROJECT_TEST_PIPE4) $(PROJECT_TEST_PIPE4).o
	#./$(PRJECT_TEST_PIPE2)

$(PROJECT_TEST_PIPE5):
	$(CXX) $(CXXFLAGS) $(PROJECT_TEST_PIPE5).cpp
	$(CXX) -o $(PROJECT_TEST_PIPE5) $(PROJECT_TEST_PIPE5).o
	#./$(PRJECT_TEST_PIPE2)

.PHONY: clean

clean:
	rm -f *.o  
