src_path = src
include_path = src/include
build_path = build
object_path = obj	
objects = main.o Backend.o Storage.o Student.o Term.o Lesson.o Console.o jsoncpp.o
my_objects = main.o Backend.o Storage.o Student.o Term.o Lesson.o
compiler = g++ -g -lreadline 
SYSUWKB: $(objects) 
	$(compiler) -o SYSUWKB $(objects)
	rm *.o
	mv SYSUWKB $(build_path)/
	cp crawler/crawler.py $(build_path)/
main.o: $(include_path)/Backend.h
	$(compiler) -c $(src_path)/main.cpp
Backend.o: $(include_path)/Backend.h $(include_path)/Storage.h
	$(compiler) -c $(src_path)/Backend.cpp
Storage.o: $(include_path)/Backend.h $(include_path)/Storage.h
	$(compiler) -c $(src_path)/Storage.cpp
Student.o: $(include_path)/Backend.h $(include_path)/Student.h
	$(compiler) -c $(src_path)/Student.cpp
Term.o: $(include_path)/Backend.h $(include_path)/Term.h
	$(compiler) -c $(src_path)/Term.cpp
Lesson.o: $(include_path)/Backend.h $(include_path)/Lesson.h
	$(compiler) -c $(src_path)/Lesson.cpp
Console.o:
	$(compiler) -c $(src_path)/Console.cpp
jsoncpp.o:
	$(compiler) -c $(src_path)/jsoncpp.cpp
clean:
	rm $(build_path)/SYSUWKB
valgrind: $(objects)
	$(compiler) -O0 $(objects) -o SYSUWKB
demo: $(objects)
	$(compiler) -o SYSUWKB $(objects)
	rm *.o
	mv SYSUWKB $(build_path)/
	cp crawler/crawler.py $(build_path)/
	cp -r demo/. ./
