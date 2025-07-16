#include "Handcrank/Animator.hpp"
#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

using namespace Handcrank;

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    auto cube = std::make_shared<RectRenderObject>(
        game->GetWidth() / 2, game->GetHeight() / 2, 250, 250);

    cube->SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

    cube->SetFillColor(MAX_R, 0, 0, 0);

    game->AddChildObject(cube);

    auto animator = std::make_shared<Animator>(Animator::Mode::SEQUENCE, true);

    float internalAlpha = 0;

    // Fade in
    animator->AddAnimation(std::make_shared<Animation>(
        [&](const double deltaTime, const double elapsedTime)
        {
            auto color = cube->GetFillColor();

            internalAlpha += 500 * deltaTime;

            auto alpha = std::clamp(internalAlpha, 0.0F, (float)MAX_ALPHA);

            cube->SetFillColor(color.r, color.g, color.b, alpha);

            return alpha == (float)MAX_R ? 0 : 1;
        }));

    // Pause
    animator->AddAnimation(std::make_shared<Animation>(
        [&](const double deltaTime, const double elapsedTime)
        { return elapsedTime > 0.1 ? 0 : 1; }));

    // Fade out
    animator->AddAnimation(std::make_shared<Animation>(
        [&](const double deltaTime, const double elapsedTime)
        {
            auto color = cube->GetFillColor();

            internalAlpha -= 500 * deltaTime;

            auto alpha = std::clamp(internalAlpha, 0.0F, (float)MAX_ALPHA);

            cube->SetFillColor(color.r, color.g, color.b, alpha);

            return alpha == 0 ? 0 : 1;
        }));

    // Pause
    animator->AddAnimation(std::make_shared<Animation>(
        [&](const double deltaTime, const double elapsedTime)
        { return elapsedTime > 0.1 ? 0 : 1; }));

    game->AddChildObject(animator);

    return game->Run();
}
