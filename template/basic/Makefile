cc = gcc
target = target

compile_flags = -O2 -std=c99 -Wall -Werror
relocatable_flags = -shared -fPIC
link_flags = -std=c99

sources = main.c
headers = 
objects = $(sources:.c=.o)

relocatable_src = 
relocatable_objects = $(relocatable_src:.c=.o)
relocatable = relocatable.so

all : $(target)

$(target):	$(objects)
		$(cc) $(objects) $(link_flags) -o $(target)

$(relocatable):	$(relocatable_objects)
		$(cc) $(relocatable_objects) $(so_flags) -o $(relocatable)

.c.o:
	$(cc) $(compile_flags) -c $< -o $@

clean:
	rm -f $(objects) $(target)
