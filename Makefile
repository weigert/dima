CC = g++ -std=c++17
CFLAGS = -Wfatal-errors -O
LFLAGS = -I/usr/local/include -L/usr/local/lib

dima: dima.cpp
	@$(CC) dima.cpp $(CFLAGS) $(LFLAGS) -o dima
	@mv dima /usr/local/bin/dima

.PHONY: all
	dima
