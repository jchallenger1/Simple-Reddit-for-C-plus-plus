CC = g++
OOBJS = main.o Curl.o RedditUser.o
FILES = ../test/main.cpp ../src/Curl.hpp ../src/Curl.cpp ../src/RedditUser.hpp ../src/RedditUser.cpp ../src/RedditError.hpp
VER = -std=c++17
CFLAGS = -Wall -lcurl -c
LFLAGS = -Wall -lcurl

main : $(OOBJS)
	$(CC) $(VER) $(LFLAGS) $(OOBJS) -o main

main.o : ../test/main.cpp ../src/Curl.hpp ../src/RedditUser.hpp
	$(CC) $(VER) $(CFLAGS) ../test/main.cpp -o main.o

Curl.o : ../src/Curl.cpp ../src/Curl.hpp ../src/RedditUser.hpp ../src/RedditError.hpp
	$(CC) $(VER) $(CFLAGS) ../src/Curl.cpp -o Curl.o

RedditUser.o : ../src/RedditUser.cpp ../src/RedditUser.hpp 
	$(CC) $(VER) $(CFLAGS) ../src/RedditUser.cpp -o RedditUser.o

clean :
	rm *.o main

tar:
	mkdir ._reddit++_; \
	cp $(FILES) ._reddit++_; \
	tar cfv reddit++.tar ._reddit++_; \
	rm -r ._reddit++_;
