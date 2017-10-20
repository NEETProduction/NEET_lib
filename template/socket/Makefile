cc = gcc
server = server
client = client

compile_flags = -O2 -std=c99 -Wall -Werror
def_flags = #-DOLD_FASHION 			#enable DOLD_FASHION to use old-fashioned code(IPv6 support is under construction))
so_flags = -shared -fPIC
link_flags = -std=c99

server_sources = server.c
server_headers = 
server_objects = $(server_sources:.c=.o)

client_sources = client.c
client_headers = 
client_objects = $(client_sources:.c=.o)

all : $(server)	$(client)

$(server):	$(server_objects)
		$(cc) $(server_objects) $(link_flags) -o $(server)

$(client):	$(client_objects)
		$(cc) $(client_objects) $(link_flags) -o $(client)

.c.o:
	$(cc) $(compile_flags) $(def_flags) -c $< -o $@

clean:
	rm -f $(server_objects) $(server) $(client_objects) $(client)
