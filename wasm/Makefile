# vim: tabstop=4 shiftwidth=4 noexpandtab
build:
	emcc /mnt/src/example.c \
	-L /opt/ncurses-6.4/lib \
	-I /opt/ncurses-6.4/include \
	-lncursesw_g \
	--preload-file /opt/lib/terminfo@/home/web_user/.terminfo \
	-o compiled.js \
	-s WASM=1 \
	-s FORCE_FILESYSTEM=1 \
	-s EXIT_RUNTIME=1 \
	-s ASYNCIFY

clean:
	rm -fr ./build/

