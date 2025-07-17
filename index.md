# Handcrank Engine

> The Handcrank Engine is a easy to use game engine based on simple principles that are quick to understand and build with.

<div class="download-buttons">
    <a href="https://github.com/HandcrankEngine/HandcrankEngine" class="download-button"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 496 512"><!--!Font Awesome Free 6.7.2 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license/free Copyright 2025 Fonticons, Inc.--><path d="M165.9 397.4c0 2-2.3 3.6-5.2 3.6-3.3 .3-5.6-1.3-5.6-3.6 0-2 2.3-3.6 5.2-3.6 3-.3 5.6 1.3 5.6 3.6zm-31.1-4.5c-.7 2 1.3 4.3 4.3 4.9 2.6 1 5.6 0 6.2-2s-1.3-4.3-4.3-5.2c-2.6-.7-5.5 .3-6.2 2.3zm44.2-1.7c-2.9 .7-4.9 2.6-4.6 4.9 .3 2 2.9 3.3 5.9 2.6 2.9-.7 4.9-2.6 4.6-4.6-.3-1.9-3-3.2-5.9-2.9zM244.8 8C106.1 8 0 113.3 0 252c0 110.9 69.8 205.8 169.5 239.2 12.8 2.3 17.3-5.6 17.3-12.1 0-6.2-.3-40.4-.3-61.4 0 0-70 15-84.7-29.8 0 0-11.4-29.1-27.8-36.6 0 0-22.9-15.7 1.6-15.4 0 0 24.9 2 38.6 25.8 21.9 38.6 58.6 27.5 72.9 20.9 2.3-16 8.8-27.1 16-33.7-55.9-6.2-112.3-14.3-112.3-110.5 0-27.5 7.6-41.3 23.6-58.9-2.6-6.5-11.1-33.3 2.6-67.9 20.9-6.5 69 27 69 27 20-5.6 41.5-8.5 62.8-8.5s42.8 2.9 62.8 8.5c0 0 48.1-33.6 69-27 13.7 34.7 5.2 61.4 2.6 67.9 16 17.7 25.8 31.5 25.8 58.9 0 96.5-58.9 104.2-114.8 110.5 9.2 7.9 17 22.9 17 46.4 0 33.7-.3 75.4-.3 83.6 0 6.5 4.6 14.4 17.3 12.1C428.2 457.8 496 362.9 496 252 496 113.3 383.5 8 244.8 8zM97.2 352.9c-1.3 1-1 3.3 .7 5.2 1.6 1.6 3.9 2.3 5.2 1 1.3-1 1-3.3-.7-5.2-1.6-1.6-3.9-2.3-5.2-1zm-10.8-8.1c-.7 1.3 .3 2.9 2.3 3.9 1.6 1 3.6 .7 4.3-.7 .7-1.3-.3-2.9-2.3-3.9-2-.6-3.6-.3-4.3 .7zm32.4 35.6c-1.6 1.3-1 4.3 1.3 6.2 2.3 2.3 5.2 2.6 6.5 1 1.3-1.3 .7-4.3-1.3-6.2-2.2-2.3-5.2-2.6-6.5-1zm-11.4-14.7c-1.6 1-1.6 3.6 0 5.9 1.6 2.3 4.3 3.3 5.6 2.3 1.6-1.3 1.6-3.9 0-6.2-1.4-2.3-4-3.3-5.6-2z"/></svg> Download it from GitHub</a>
    <a href="https://github.com/HandcrankEngine/HandcrankEngine">https://github.com/HandcrankEngine/HandcrankEngine</a>
</div>

<canvas id="demo" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/demo/demo.js"></script>
<script>
demoModule({
    canvas: document.querySelector('#demo')
});
</script>

## Getting Started

<canvas id="drawRectRenderer" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/drawRectRenderer/drawRectRenderer.js"></script>
<script>
drawRectRendererModule({
    canvas: document.querySelector('#drawRectRenderer')
});
</script>

```cpp
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
```

## Features

### Simple Event Loop

<canvas id="simpleEventLoop" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/simpleEventLoop/simpleEventLoop.js"></script>
<script>
simpleEventLoopModule({
    canvas: document.querySelector('#simpleEventLoop')
});
</script>

```cpp
#include <iostream>

#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

class LoopDebugger : public RenderObject
{
  public:
    void Update(const double deltaTime) override
    {
        std::cout << "Update " << std::to_string(deltaTime) << std::endl;
    }
    void FixedUpdate(const double fixedDeltaTime) override
    {
        std::cout << "Fixed Update " << std::to_string(fixedDeltaTime)
                  << std::endl;
    }
};

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(500, 300);

    game->AddChildObject(std::move(std::make_unique<LoopDebugger>()));

    return game->Run();
}
```

### Sprite Animations

<canvas id="spriteRenderer" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/spriteRenderer/spriteRenderer.js"></script>
<script>
spriteRendererModule({
    canvas: document.querySelector('#spriteRenderer')
});
</script>

```cpp
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
```

### Tiled Map Support (WIP)

<canvas id="tiledMapSupport" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/tiledMapSupport/tiledMapSupport.js"></script>
<script>
tiledMapSupportModule({
    canvas: document.querySelector('#tiledMapSupport')
});
</script>

### Animations

<canvas id="animation" tabindex="-1" width="1000" height="600" style="width: 100%"></canvas>

<script src="demos/animation/animation.js"></script>
<script>
animationModule({
    canvas: document.querySelector('#animation')
});
</script>

```cpp
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
```

### Audio

### Cross Platform

Support for **Windows**, **macOS**, **Linux** and **WebGL**. Mobile platforms coming soon.

## Demo

## Support Handcrank Engine

If you enjoy this project, consider supporting the project on Github!
