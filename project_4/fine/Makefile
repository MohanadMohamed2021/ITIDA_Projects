CXX = g++
CXXFLAGS = -Wall

all: out

out: UltaSonic.o main.o Buzzer.o 
	$(CXX) $^ -o $@ -lwiringPi

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf *.o out
