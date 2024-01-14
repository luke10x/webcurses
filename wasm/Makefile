# vim: tabstop=4 shiftwidth=4 noexpandtab
build:

	emcc /mnt/examples/example.c \
	-lncursesw_g \
	--preload-file /opt/terminfo@/home/web_user/.terminfo \
	-o /mnt/examples/build/example.js \
	-s ASYNCIFY

	emcc /mnt/examples/prompt.c \
	-lncursesw_g \
	--preload-file /opt/terminfo@/home/web_user/.terminfo \
	-o /mnt/examples/build/prompt.js \
	-s ASYNCIFY

clean:
	rm -fr /mnt/wasm/build/

