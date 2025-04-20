all: main

main: main.cpp | out
	g++ main.cpp -o out/main -std=c++23 -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror

out:
	mkdir -p out

clean:
	rm -rf out
