#include <iostream>

#include "HandcrankEngine/HandcrankEngine.hpp"

using namespace HandcrankEngine;

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

auto main(int argc, char *argv[]) -> int
{
    auto game = std::make_unique<Game>();

    game->SetScreenSize(1000, 600);

    game->AddChildObject(std::move(std::make_unique<LoopDebugger>()));

    return game->Run();
}
