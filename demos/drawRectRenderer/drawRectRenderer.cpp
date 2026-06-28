#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/RectRenderObject.hpp"

using namespace HandcrankEngine;

auto main(int argc, char *argv[]) -> int
{
    auto game = std::make_unique<Game>();

    game->SetScreenSize(1000, 600);

    auto rect = std::make_shared<RectRenderObject>();

    rect->SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

    rect->SetRect(game->GetWidth() / 2, game->GetHeight() / 2, 250, 250);
    rect->SetFillColor(255, 0, 0, 255);

    game->AddChildObject(rect);

    return game->Run();
}
