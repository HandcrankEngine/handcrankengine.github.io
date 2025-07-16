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
