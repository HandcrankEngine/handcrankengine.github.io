FROM ubuntu:latest

ARG EMSDK_VERSION=5.0.7
ARG SDL_VERSION=3.4.10
ARG SDL_IMAGE_VERSION=3.4.4
ARG SDL_TTF_VERSION=3.2.2
ARG SDL_MIXER_VERSION=3.2.4

ARG DEPS_PREFIX="/build/dependencies"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y \
    curl \
    build-essential \
    pkg-config \
    libpng-dev \
    libjpeg-dev \
    libtiff-dev \
    libwebp-dev \
    libfreetype-dev \
    valgrind

RUN apt-get install -y \
    cmake \
    make \
    ninja-build \
    gnome-desktop-testing \
    libasound2-dev \
    libpulse-dev \
    libaudio-dev \
    libjack-dev \
    libsndio-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxfixes-dev \
    libxi-dev \
    libxss-dev \
    libxtst-dev \
    libxkbcommon-dev \
    libdrm-dev \
    libgbm-dev \
    libgl1-mesa-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    libdbus-1-dev \
    libibus-1.0-dev \
    libudev-dev

RUN apt-get install -y \
    libfreetype6-dev \
    libharfbuzz-dev

# Install Emscripten
RUN mkdir -p /tmp/.emscripten && \
    cd /tmp/.emscripten && \
    curl -L https://github.com/emscripten-core/emsdk/archive/refs/tags/${EMSDK_VERSION}.tar.gz > emscripten.tar.gz && \
    mkdir emscripten-${EMSDK_VERSION} && \
    tar -xzvf emscripten.tar.gz --strip-components=1 -C emscripten-${EMSDK_VERSION} && \
    rm emscripten.tar.gz && \
    cd emscripten-${EMSDK_VERSION} && \
    ./emsdk install ${EMSDK_VERSION} && \
    ./emsdk activate ${EMSDK_VERSION}

ENV EMSDK=/tmp/.emscripten/emscripten-${EMSDK_VERSION}
ENV PATH="${EMSDK}:${EMSDK}/upstream/emscripten:${PATH}"

# Install SDL
RUN mkdir -p /tmp/.sdl && \
    cd /tmp/.sdl && \
    curl -L https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL3-${SDL_VERSION}.tar.gz > SDL.tar.gz && \
    mkdir SDL-${SDL_VERSION} && \
    tar -xzvf SDL.tar.gz --strip-components=1 -C SDL-${SDL_VERSION} && \
    rm SDL.tar.gz && \
    cd SDL-${SDL_VERSION} && \
    emcmake cmake -S . -B dist \
        -DCMAKE_INSTALL_PREFIX="${DEPS_PREFIX}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL_SHARED=OFF \
        -DSDL_STATIC=ON \
        -DSDL_TESTS=OFF \
        -DSDL_EXAMPLES=OFF && \
    cmake --build dist -j$(nproc) && \
    cmake --install dist

# Install SDL_image
RUN mkdir -p /tmp/.sdl && \
    cd /tmp/.sdl && \
    curl -L https://github.com/libsdl-org/SDL_image/releases/download/release-${SDL_IMAGE_VERSION}/SDL3_image-${SDL_IMAGE_VERSION}.tar.gz > SDL_image.tar.gz && \
    mkdir SDL_image-${SDL_IMAGE_VERSION} && \
    tar -xzvf SDL_image.tar.gz --strip-components=1 -C SDL_image-${SDL_IMAGE_VERSION} && \
    rm SDL_image.tar.gz && \
    cd SDL_image-${SDL_IMAGE_VERSION} && \
    emcmake cmake -S . -B dist \
        -DCMAKE_INSTALL_PREFIX="${DEPS_PREFIX}" \
        -DSDL3_DIR="${DEPS_PREFIX}/lib/cmake/SDL3" \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL3IMAGE_SHARED=OFF \
        -DSDL3IMAGE_BUILD_SHARED_LIBS=OFF \
        -DSDLIMAGE_SAMPLES=OFF && \
    cmake --build dist -j$(nproc) && \
    cmake --install dist

# Install SDL_ttf
RUN mkdir -p /tmp/.sdl && \
    cd /tmp/.sdl && \
    curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-${SDL_TTF_VERSION}/SDL3_ttf-${SDL_TTF_VERSION}.tar.gz > SDL_ttf.tar.gz && \
    mkdir SDL_ttf-${SDL_TTF_VERSION} && \
    tar -xzvf SDL_ttf.tar.gz --strip-components=1 -C SDL_ttf-${SDL_TTF_VERSION} && \
    rm SDL_ttf.tar.gz && \
    cd SDL_ttf-${SDL_TTF_VERSION} && \
    emcc --use-port=freetype --use-port=harfbuzz --version && \
    emcmake cmake -S . -B dist \
        -DCMAKE_INSTALL_PREFIX="${DEPS_PREFIX}" \
        -DSDL3_DIR="${DEPS_PREFIX}/lib/cmake/SDL3" \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL3TTF_SHARED=OFF \
        -DSDLTTF_SAMPLES=OFF \
        -DCMAKE_C_FLAGS="-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1" \
        -DCMAKE_CXX_FLAGS="-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1" \
        -DSDL3TTF_HARFBUZZ=ON && \
    cmake --build dist -j$(nproc) && \
    cmake --install dist

# Install SDL_mixer
RUN mkdir -p /tmp/.sdl && \
    cd /tmp/.sdl && \
    curl -L https://github.com/libsdl-org/SDL_mixer/releases/download/release-${SDL_MIXER_VERSION}/SDL3_mixer-${SDL_MIXER_VERSION}.tar.gz > SDL_mixer.tar.gz && \
    mkdir SDL_mixer-${SDL_MIXER_VERSION} && \
    tar -xzvf SDL_mixer.tar.gz --strip-components=1 -C SDL_mixer-${SDL_MIXER_VERSION} && \
    rm SDL_mixer.tar.gz && \
    cd SDL_mixer-${SDL_MIXER_VERSION} && \
    emcmake cmake -S . -B dist \
        -DCMAKE_INSTALL_PREFIX="${DEPS_PREFIX}" \
        -DSDL3_DIR="${DEPS_PREFIX}/lib/cmake/SDL3" \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL3MIXER_SHARED=OFF \
        -DSDLMIXER_SAMPLES=OFF && \
    cmake --build dist -j$(nproc) && \
    cmake --install dist

WORKDIR /app

COPY ./bin ./bin
COPY ./demos ./demos
COPY ./include ./include
COPY ./js ./js

RUN mkdir -p /tmp/dist

RUN ./bin/build-web.sh
