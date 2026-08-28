#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/demo/sdl_logo.png")" > "demos/demo/sdl_logo.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/spriteRenderer/alienGreen.png")" > "demos/spriteRenderer/alienGreen.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/svg/Ghostscript_Tiger.svg")" > "demos/svg/Ghostscript_Tiger.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/texturePackerPlugin/alien.png")" > "demos/texturePackerPlugin/alien.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/texturePackerPlugin/alien.json")" > "demos/texturePackerPlugin/alien_json.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/tiledPlugin/tilemap.png")" > "demos/tiledPlugin/tilemap.h"
    printf "#pragma once\n\n%s\n" "$(xxd -i "demos/tiledPlugin/tilemap.json")" > "demos/tiledPlugin/tilemap_json.h"

)
