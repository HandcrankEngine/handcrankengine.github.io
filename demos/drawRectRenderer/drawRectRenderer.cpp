#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

using namespace Handcrank;

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    auto rect = std::make_shared<RectRenderObject>();

    rect->SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

    rect->SetRect(game->GetWidth() / 2, game->GetHeight() / 2, 250, 250);
    rect->SetFillColor(255, 0, 0, 255);

    game->AddChildObject(rect);

    return game->Run();
}
