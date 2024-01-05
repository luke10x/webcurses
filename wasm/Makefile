# vim: tabstop=4 shiftwidth=4 noexpandtab
build:

	emcc /mnt/src/example.c \
	-lncursesw_g \
	--preload-file /opt/terminfo@/home/web_user/.terminfo \
	-o compiled.js \
	-s ASYNCIFY

clean:
	rm -fr ./build/

