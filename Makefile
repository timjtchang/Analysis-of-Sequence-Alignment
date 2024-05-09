
all: basic efficient

basic: basic.cpp
	g++ basic.cpp -o basic.out

efficient: efficient.cpp
	g++ efficient.cpp -o efficient.out

clean: 
	rm basic.out efficient.out