OBJ =tools.o main.o student.o teacher.o principal.o
all:$(OBJ)
	g++ -std=gnu++0x -o exe $(OBJ) && ./exe

tools.o:tools.h
	g++ -std=gnu++0x -o tools.o -c tools.cpp
principal.o:tools.h person.h
	g++ -std=gnu++0x -o principal.o -c principal.cpp
student.o:tools.h teacher.h person.h tools.o
	g++ -std=gnu++0x -o student.o -c student.cpp
teacher.o:tools.h principal.h person.h
	g++ -std=gnu++0x -o teacher.o -c teacher.cpp
main.o:main.cpp tools.h person.h 
	g++ -std=gnu++0x -c main.cpp -o main.o

clean:
	rm -f ./*.o ./exe
