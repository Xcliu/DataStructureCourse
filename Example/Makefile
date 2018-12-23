LIBS = -I../DataStructureHomework/common_library
LINKS =
libs = ../DataStructureHomework/common_library/mystd.cpp
CC = g++
CFLAGS = -Wall -O2 -std=c++11

#text_book_1.1: text_book_1.1.cpp
#	$(CC) $(CFLAGS) -o $@ $^
function_example:function_example.cpp
	$(CC) $(CFLAGS) -o $@  $^

compile: text_book_1.1.cpp
	$(CC) $(CFLAGS) -o $@  $^



functional: functional.cpp
	$(CC) $(CFLAGS) -o $@ $^


io: io.cpp
	$(CC) $(CFLAGS) -o $@ $^


control: control.cpp
	$(CC) $(CFLAGS) -o $@ $^


memory: memory.cpp
	$(CC) $(CFLAGS) -o $@ $^


class: class.cpp
	$(CC) $(CFLAGS) -o $@ $^


template_class: template_class.cpp
	$(CC) $(CFLAGS) -o $@ $^

function_example: function_example.cpp $(libs)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ $(LINKS)
