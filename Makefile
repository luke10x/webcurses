# vim: tabstop=4 shiftwidth=4 noexpandtab
build:
	gcc ./src/example.c \
	$$(pkg-config --cflags ncurses) \
	$$(pkg-config --libs ncurses) \
	-o ./example

clean:
	rm -f ./example

