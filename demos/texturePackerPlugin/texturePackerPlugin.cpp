#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/SpriteRenderObject.hpp"

#include "TexturePacker/TexturePacker.hpp"

#include "alien.h"
#include "alien_json.h"

using namespace HandcrankEngine;

class GreenAlien : public SpriteRenderObject
{
  private:
    std::vector<SDL_Rect> spriteFrames;

  public:
    using SpriteRenderObject::SpriteRenderObject;

    void Start() override
    {
        LoadTexture(game->GetRenderer(), demos_texturePackerPlugin_alien_png,
                    demos_texturePackerPlugin_alien_png_len);

        spriteFrames = LoadTexturePackerFramesFromMemory(
            demos_texturePackerPlugin_alien_json,
            demos_texturePackerPlugin_alien_json_len, "walk-");

        SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_SCALEMODE_PIXELART);

        SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

        SetPosition(game->GetWidth() / 2, game->GetHeight() / 2);

        SetScale(2);

        SetFrameSpeed(0.25);

        SetFrames(spriteFrames);

        Play();
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

    game->AddChildObject(std::move(std::make_unique<GreenAlien>()));

    return game->Run();
}
