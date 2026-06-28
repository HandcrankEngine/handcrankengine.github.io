#include "alienGreen.h"

#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/SpriteRenderObject.hpp"

using namespace HandcrankEngine;

class GreenAlien : public SpriteRenderObject
{
  public:
    void Start() override
    {
        LoadTexture(game->GetRenderer(), images_alienGreen_png,
                    images_alienGreen_png_len);

        SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_SCALEMODE_PIXELART);

        SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

        SetPosition(game->GetWidth() / 2, game->GetHeight() / 2);

        SetFrameSpeed(0.25);

        AddFrame({69, 193, 68, 93});
        AddFrame({0, 0, 70, 96});

        Play();
    }
};

auto main(int argc, char *argv[]) -> int
{
#ifdef __EMSCRIPTEN__
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR, CANVAS_SELECTOR);
#endif

    auto game = std::make_unique<Game>();

    game->SetScreenSize(1000, 600);

    game->AddChildObject(std::move(std::make_unique<GreenAlien>()));

    return game->Run();
}
