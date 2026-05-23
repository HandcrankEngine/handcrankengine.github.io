#!/bin/bash

build-demo() {
    NAME="${1}"

    mkdir -p /tmp/dist/demos/${NAME}/

    emcc -std=c++17 -Os -o "/tmp/dist/demos/${NAME}/${NAME}.js" "demos/${NAME}/${NAME}.cpp" \
        -I./include -I./HandcrankEngine/include \
        -I"${DEPS_PREFIX}"/include/SDL2 -I"${DEPS_PREFIX}"/include -L"${DEPS_PREFIX}"/lib \
        -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
        -s USE_FREETYPE=1 -s USE_HARFBUZZ=1 \
        -s MAX_WEBGL_VERSION=2 \
        -s MODULARIZE=1 -s EXPORT_NAME="${NAME}Module" --pre-js ./bin/sdl-mod.js
}

build-demo "demo"
build-demo "animation"
build-demo "drawRectRenderer"
build-demo "simpleEventLoop"
build-demo "spriteRenderer"
build-demo "svg"
build-demo "tiledPlugin"
