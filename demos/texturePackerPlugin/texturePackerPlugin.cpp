#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/SpriteRenderObject.hpp"

#include "TexturePacker/TexturePacker.hpp"

#include "alien.h"
// #include "alien_json.h"

using namespace HandcrankEngine;

class Example : public SpriteRenderObject
{
  private:
    std::vector<SpriteFrame> spriteFrames;

  public:
    using SpriteRenderObject::SpriteRenderObject;

    void Start() override
    {
        LoadTexture(game->GetRenderer(), images_alien_png,
                    images_alien_png_len);

        // spriteFrames =
        //     LoadTexturePackerFramesFromFile("./images/alien.json", "walk-");

        // SetFrames(spriteFrames);
    }
};

auto main(int argc, char *argv[]) -> int
{
#ifdef __EMSCRIPTEN__
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR, CANVAS_SELECTOR);
#endif

    auto game = std::make_unique<Game>();

    game->SetRenderScale(1);

    game->SetScreenSize(1000, 600);

    return game->Run();
}
