objects = main.o Backend.o Storage.o Student.o Term.o Lesson.o
compiler = g++ -g
MUKS: $(objects)
	$(compiler) -o MUKS $(objects)
main.o: Backend.h
	$(compiler) -c main.cpp
Backend.o: Backend.h Storage.h
	$(compiler) -c Backend.cpp
Storage.o: Backend.h Storage.h
	$(compiler) -c Storage.cpp
Student.o: Backend.h Student.h
	$(compiler) -c Student.cpp
Term.o: Backend.h Term.h
	$(compiler) -c Term.cpp
Lesson.o: Backend.h Lesson.h
	$(compiler) -c Lesson.cpp
clean:
	rm MUKS $(objects)
	
