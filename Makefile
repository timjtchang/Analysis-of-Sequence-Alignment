
all: basic efficient

basic: basic.cpp
	g++ basic.cpp -o basic

efficient: efficient.cpp
	g++ efficient.cpp -o efficient

clean: 
	rm basic efficient