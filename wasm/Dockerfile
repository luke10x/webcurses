FROM emscripten/emsdk:3.1.25

WORKDIR /opt

RUN wget https://invisible-island.net/archives/ncurses/ncurses-6.4.tar.gz \
  && tar xvf ncurses-6.4.tar.gz

WORKDIR  /opt/ncurses-6.4

# build native ncurses first
RUN mkdir /opt/ncurses-native
RUN ./configure --enable-widec --prefix=/opt/ncurses-native \
  && make \
  && make install

# user programs will need this terminfo from native build
RUN cp -r /opt/ncurses-native/share/terminfo /opt/terminfo

# WASM build will need these binaries from native build,
# prevent WASM build overriding them using custom file names
RUN cp ncurses/make_hash ncurses/make_hash_native
RUN cp ncurses/make_keys ncurses/make_keys_native
RUN cp ncurses/report_offsets ncurses/report_offsets_native

# patch build files to make sure the build always use the native programs
RUN sed -i 's|./make_hash|./make_hash_native|g' ncurses/tinfo/MKcaptab.sh 
RUN sed -i 's|./make_keys\$|./make_keys_native\$|g'           ncurses/Makefile.in 
RUN sed -i 's|./report_offsets\$|./report_offsets_native\$|g' ncurses/Makefile.in 
RUN sed -i 's|./make_hash|./make_hash_native|g' ncurses/tinfo/MKuserdefs.sh 

# Now build ncurses for WASM
RUN make clean
RUN emconfigure ./configure --enable-widec 
RUN emmake make

# Some functions like 
RUN ln -s /opt/ncurses-6.4/include/curses.h \
  /opt/ncurses-6.4/include/curses-original.h

ENV C_INCLUDE_PATH="/mnt/include:/opt/ncurses-6.4/include"
RUN ln -s /opt/ncurses-6.4/lib/* /emsdk/upstream/emscripten/cache/sysroot/lib/wasm32-emscripten/

COPY ./include /mnt/include