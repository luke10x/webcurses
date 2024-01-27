# vim: tabstop=4 shiftwidth=4 noexpandtab
examples/build:
	mkdir -p ./examples/build
	gcc ./examples/example.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-o ./examples/build/example

	gcc ./examples/prompt.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-o ./examples/build/prompt

	gcc ./examples/window.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-o ./examples/build/window

	gcc ./examples/keyboard.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-o ./examples/build/keyboard

	gcc ./examples/mouse.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-o ./examples/build/mouse

	gcc ./examples/panel.c \
		$$(pkg-config --cflags ncurses) \
		$$(pkg-config --libs ncurses) \
		-lpanel \
		-o ./examples/build/panel

clean:
	rm -rf ./examples/build

