cc = gcc
target = mystring.so
test = test

compile_flags = -O2 -std=c99 -Wall -Werror
so_flags = -shared -fPIC
link_flags = 

sources = mystring.c
objects = $(sources:.c=.o)
headers = mystring.h

test_source = test.c
test_object = $(test_source:.c=.o)

all : $(target)

$(target):	$(headers) $(objects)
		$(cc) $(objects) $(link_flags) $(so_flags) -o $(target)

$(test):	$(target) $(test_object)
		$(cc) $(test_object) ./$(target) -o $(test)

.c.o:
	$(cc) $(compile_flags) -fPIC -c $< -o $@

clean:
	rm -f $(objects) $(test_objects) $(target)
