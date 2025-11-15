#include "Ghostscript_Tiger.h"

#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/ImageRenderObject.hpp"

using namespace HandcrankEngine;

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    auto image = std::make_shared<ImageRenderObject>();

    image->LoadTexture(game->GetRenderer(), images_Ghostscript_Tiger_svg,
                       images_Ghostscript_Tiger_svg_len);

    image->SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

    image->SetPosition(game->GetWidth() / 2, game->GetHeight() / 2);

    game->AddChildObject(image);

    return game->Run();
}
