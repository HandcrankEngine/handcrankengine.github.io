#include <vector>

#include "HandcrankEngine/Animator.hpp"
#include "HandcrankEngine/HandcrankEngine.hpp"
#include "HandcrankEngine/VertexRenderObject.hpp"

#include "Tiled/Tiled.hpp"

#include "tilemap.h"
#include "tilemap_json.h"

using namespace HandcrankEngine;

class TileMap : public VertexRenderObject
{
  private:
    const float scale = 2.5;
    const int tileWidth = 16;
    const int tileHeight = 16;

    std::vector<TiledLayer> tiledLayers;

  public:
    using VertexRenderObject::VertexRenderObject;

    void Start() override
    {
        LoadTransparentTexture(game->GetRenderer(), images_tilemap_png,
                               images_tilemap_png_len, {0, 0, 0, 0});

        std::string jsonString(reinterpret_cast<char *>(images_tilemap_json),
                               images_tilemap_json_len);

        tiledLayers = LoadTiledLayersFromString(jsonString);

        auto animator =
            std::make_shared<Animator>(Animator::Mode::SEQUENCE, true);

        for (auto i = 0; i < tiledLayers.size(); i += 1)
        {
            animator->AddAnimation(std::make_shared<Animation>(
                [i, this](double deltaTime, double elapsedTime)
                {
                    AddTileSet(tiledLayers[i], tileWidth, tileHeight);

                    return 0;
                }));

            animator->AddDelay(1000);
        }

        AddChildObject(animator);
    }

    void AddTileSet(const TiledLayer &tiledLayer, const int tileWidth,
                    const int tileHeight)
    {
        auto tilesPerCol = textureWidth / tileWidth;

        for (const auto &tile : tiledLayer.tiles)
        {
            auto tileIndex = tile.tileID - 1;
            auto srcX = (tileIndex % (int)tilesPerCol) * tileWidth;
            auto srcY = (tileIndex / tilesPerCol) * tileHeight;

            auto screenX = (float)tile.x * tileWidth * scale;
            auto screenY = (float)tile.y * tileHeight * scale;

            GenerateTextureQuad(
                vertices, indices,
                {screenX, screenY, (float)tileWidth * scale,
                 (float)tileHeight * scale},
                {(float)srcX, (float)srcY, (float)tileWidth, (float)tileHeight},
                {1, 1, 1, 1}, textureWidth, textureHeight);
        }
    }
};

auto game = std::make_unique<Game>();

auto main(int argc, char *argv[]) -> int
{
    game->SetScreenSize(1000, 600);

    game->AddChildObject(std::move(std::make_unique<TileMap>()));

    return game->Run();
}
