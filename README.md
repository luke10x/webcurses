WebCurses
=========

A web-based platform designed to bring the classic charm
of text-based interfaces into the modern web era.

This platform consists of:

    - Emscripten container image equipped
      with NCurses-6.4 compiled for WASM;
    - Web component exposing WASM applications in web UI
      using XTerm.js widget.

User guide
----------

TBA

Development procedures
----------------------

Build and push the image to the container registry:

    docker-compose build wasm --push

Start testing environment:

    docker-compose up --build --force-recreate -d wasm

Shell into the testing environment:

    docker-compose exec wasm bash

In that shell, build examples:

    make clean build

Navigate to http://localhost:9988 and see the testing apps

        
