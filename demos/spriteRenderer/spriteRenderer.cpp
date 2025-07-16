#include "alienGreen.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/SpriteRenderObject.hpp"

using namespace Handcrank;

class GreenAlien : public SpriteRenderObject
{
  public:
    void Start() override
    {
        LoadTexture(game->GetRenderer(), images_alienGreen_png,
                    images_alienGreen_png_len);

        SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

        SetPosition(game->GetWidth() / 2, game->GetHeight() / 2);

        SetFrameSpeed(0.25);

        AddFrame({69, 193, 68, 93});
        AddFrame({0, 0, 70, 96});

        Play();
    }
};

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    game->AddChildObject(std::move(std::make_unique<GreenAlien>()));

    return game->Run();
}
