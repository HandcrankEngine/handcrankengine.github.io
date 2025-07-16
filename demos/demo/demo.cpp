#include "./sdl_logo.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class LogoScreenSaver : public ImageRenderObject
{

  protected:
    int xDirection = 1;
    int yDirection = 1;

    int movementSpeed = 250;

    float x;
    float y;
    int w;
    int h;

    int minX;
    int minY;

    int maxX;
    int maxY;

  public:
    void Start() override
    {
        SetAnchor(RectAnchor::HCENTER | RectAnchor::VCENTER);

        LoadTexture(game->GetRenderer(), images_sdl_logo_png,
                    images_sdl_logo_png_len);

        w = rect.w;
        h = rect.h;

        minX = w / 2;
        minY = h / 2;

        maxX = game->GetWidth() - (w / 2);
        maxY = game->GetHeight() - (h / 2);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        x += movementSpeed * xDirection * deltaTime;
        y += movementSpeed * yDirection * deltaTime;

        if (x > maxX || x < minX)
        {
            xDirection = -xDirection;
        }

        if (y > maxY || y < minY)
        {
            yDirection = -yDirection;
        }

        x = std::clamp<float>(x, minX, maxX);
        y = std::clamp<float>(y, minY, maxY);

        SetPosition(x, y);
    }
};

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    game->AddChildObject(std::move(std::make_unique<LogoScreenSaver>()));

    return game->Run();
}
