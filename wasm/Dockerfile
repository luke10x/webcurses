FROM emscripten/emsdk:3.1.25

WORKDIR /opt

RUN wget https://invisible-island.net/archives/ncurses/ncurses-6.4.tar.gz \
  && tar xvf ncurses-6.4.tar.gz

WORKDIR  /opt/ncurses-6.4

# do a standard build of ncurses and install it
RUN mkdir ./INSTALLED
RUN ./configure --enable-widec --prefix=/opt/ncurses-6.4/INSTALLED \
  && make \
  && make install

RUN mkdir /opt/lib
RUN cp -r ./INSTALLED/share/terminfo /opt/lib

# setup ncurses from deeper dir
RUN cp ncurses/make_hash ncurses/make_hash_x86
RUN cp ncurses/make_keys ncurses/make_keys_x86
RUN cp ncurses/report_offsets ncurses/report_offsets_x86
RUN make clean

RUN sed -i 's|./make_hash|./make_hash_x86|g' ncurses/tinfo/MKcaptab.sh 
RUN sed -i 's|./make_keys\$|./make_keys_x86\$|g'           ncurses/Makefile.in 
RUN sed -i 's|./report_offsets\$|./report_offsets_x86\$|g' ncurses/Makefile.in 
RUN sed -i 's|./make_hash|./make_hash_x86|g' ncurses/tinfo/MKuserdefs.sh 

RUN make clean
RUN emconfigure ./configure --enable-widec 
RUN emmake make



