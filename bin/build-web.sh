#!/bin/bash

build-demo() {
    NAME="${1}"

    emcc -std=c++17 -Os -o "demos/${NAME}/${NAME}.js" "demos/${NAME}/${NAME}.cpp" \
        -I/Users/scottdoxey/git/github/HandcrankEngine/include \
        -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 \
        -s MODULARIZE=1 -s EXPORT_NAME="${NAME}Module"
}

build-demo "demo"
build-demo "animation"
build-demo "drawRectRenderer"
build-demo "simpleEventLoop"
build-demo "spriteRenderer"
build-demo "tiledMapSupport"
