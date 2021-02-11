CC = g++ -std=c++17
CFLAGS = -Wfatal-errors -O
LFLAGS = -I/usr/local/include -L/usr/local/lib

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

dima: dima.cpp
	@$(CC) dima.cpp $(CFLAGS) $(LFLAGS) -o dima

install: dima
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 dima $(DESTDIR)$(PREFIX)/bin/

.PHONY: all
	dima
