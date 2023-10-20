cxx=clang++
flags=-c -O2 -std=c++20

utils.o: utils.cpp utils.hpp
	${cxx} ${flags} utils.cpp

levenshtein.o: levenshtein.cpp levenshtein.hpp
	${cxx} ${flags} levenshtein.cpp

file_diff.0: file_diff.cpp file_diff.hpp
	${cxx} ${flags} file_diff.cpp

main.o: main.cpp
	${cxx} ${flags} main.cpp

install: utils.o levenshtein.o file_diff.o main.o
	${cxx} -o filediff main.o file_diff.o levenshtein.o utils.o
	rm utils.o levenshtein.o file_diff.o main.o

clean:
	rm filediff main.o file_diff.o levenshtein.o utils.o
