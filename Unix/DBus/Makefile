CFLAGS_DBUS = $(shell pkg-config --cflags --libs dbus-1)
CFLAGS_DBUS_GLIB = $(shell pkg-config --cflags --libs dbus-glib-1)

CFLAGS = -g -Wall -Werror

all: server client

server: server.c
	gcc $< -o $@ $(CFLAGS) $(CFLAGS_DBUS) $(CFLAGS_DBUS_GLIB)

client: client.c
	gcc $< -o $@ $(CFLAGS) $(CFLAGS_DBUS) $(CFLAGS_DBUS_GLIB)

clean:
	rm -rf client server