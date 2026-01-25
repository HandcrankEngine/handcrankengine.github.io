// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#include <fstream>
#include <vector>

#include "../nlohmann/json.hpp"

using json = nlohmann::json;

struct TiledTile
{
    uint32_t tileID;
    int x;
    int y;
};

struct TiledLayer
{
    std::string name;
    std::vector<TiledTile> tiles;
};

inline const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
inline const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
inline const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

inline auto LoadTiledLayersFromString(const std::string &contents)
    -> std::vector<TiledLayer>
{
    std::vector<TiledLayer> tiledLayers;

    auto data = json::parse(contents);

    if (data.contains("layers") && data["layers"].is_array())
    {
        for (const auto &layer : data["layers"])
        {
            TiledLayer currentLayer;

            currentLayer.name = layer.at("name").get<std::string>();

            int mapWidth = layer.at("width").get<int>();
            int mapHeight = layer.at("height").get<int>();
            auto rawData = layer.at("data").get<std::vector<uint64_t>>();

            for (int i = 0; i < rawData.size(); i += 1)
            {
                auto id = (uint32_t)(rawData[i] & ~(FLIPPED_HORIZONTALLY_FLAG |
                                                    FLIPPED_VERTICALLY_FLAG |
                                                    FLIPPED_DIAGONALLY_FLAG));

                if (id != 0)
                {
                    TiledTile tile;
                    tile.tileID = id;
                    tile.x = i % mapWidth;
                    tile.y = i / mapWidth;
                    currentLayer.tiles.push_back(tile);
                }
            }

            tiledLayers.emplace_back(currentLayer);
        }
    }

    return tiledLayers;
}

inline auto LoadTiledLayersFromFile(const std::string &path)
    -> std::vector<TiledLayer>
{
    std::vector<TiledLayer> tiledLayers;

    std::ifstream file(path);

    std::string contents((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    return LoadTiledLayersFromString(contents);
}
