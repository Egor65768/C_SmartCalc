NAMEAPP = SmartCalc
CC = gcc 
FLAGS = -Wextra -Werror -Wall -std=c11
MATRIX = *.c 
OBJECTS = *.o 
TEST_LIB = ./tests/*.c
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINK_FLAGS = -lcheck 
UNAME_S := $(shell uname -s)
BUILD_DOCKER = build_docker.sh

ifeq ($(UNAME_S), Linux) 
	LINK_FLAGS += -lm -lsubunit
endif

all: clean test gcov_report install

test: clean
	$(CC) $(LEAKS) $(MATRIX) ${TEST_LIB} ${LINK_FLAGS} -o test
	./test

leaks: test
ifeq ($(UNAME_S), Linux) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
endif
ifeq ($(UNAME_S), Darwin) 
	leaks -quiet -atExit -- ./test
endif

clean: 
	rm -fr *.o *.a *.gch *.gcno *.gcda gcov_test s21_test.info ./report test

rebuild: clean test 

style:
	clang-format -style=google -n tests/* ./*.c ./*.h ./views/*.cpp ./views/*.h

format:
	clang-format -style=google -i tests/* ./*.c ./*.h ./views/*.cpp ./views/*.h

gcov_report: 
	$(CC) $(FLAGS) $(GCOV_FLAGS) ${TEST_LIB} ${MATRIX} ${LINK_FLAGS} -o test
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open report/index.html	


install:
	echo "Start installation"
	mkdir -p ../build
	cd views && qmake && make && make clean && rm Makefile && mv views ../../build/$(NAMEAPP).app
	echo "The installation has been completed successfully"

install_in_docker: clean
	@chmod +x $(BUILD_DOCKER)
	./$(BUILD_DOCKER)


uninstall:
	rm ../build/SmartCalc.app
	echo "The uninstallation has been completed successfully"

dist:
	mkdir -p ../dist
	cp -R ../build/$(NAMEAPP).app ../dist
	cp ../README_RUS.md ../dist && cp ../README.md ../dist
	cd ../dist && tar cvzf $(NAMEAPP)_v1.0.tgz *
	cd ../dist && rm -rf $(NAMEAPP).app README.md README_RUS.md
	echo "The build was successfully archived"

dvi:
	open ../README.md
