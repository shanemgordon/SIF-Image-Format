TARGET = F.exe
CPP = main.cpp conversionFunctions.cpp interfaceFunctions.cpp
HPP = SIF.hpp 
OBJECTS = $(CPP:.cpp=.o)
INC_PATH = /usr/local/include/
LIB_PATH = /usr/local/lib/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#form of a function : "target:dependencies". Function will wait for dependenceis to be assembled before beginning
#E.g program.exe : main.o circle.o
${TARGET} : ${OBJECTS} ${HPP} 

#Including additional libraries

# $^ targets all dependencies of the 'function'
# $@ targets the target of the function
# -o should go before the desired name of the output
# E.g g++ main.o -o program.exe
	g++ $^ -o $@ $(CFLAGS) -L${LIB_PATH} ${LIBS}
	del ${OBJECTS}
${OBJECTS}: ${CPP}
	g++ -c $^

%.o: %.cpp
#Because each object file is comprised of only one .cpp file, $<, single selector, should be used
	g++ -o $@ -c $< -I ${INC_PATH} 
clean:
	del $(TARGET) $(OBJECTS)