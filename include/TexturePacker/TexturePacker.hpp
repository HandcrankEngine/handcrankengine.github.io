// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#include <fstream>
#include <vector>

#include <SDL3/SDL.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct SpriteFrame
{
    std::string filename;
    SDL_Rect rect;
};

inline auto LoadTexturePackerFramesFromFile(const std::string &path,
                                            const std::string &prefix = "")
    -> std::vector<SpriteFrame>
{
    std::vector<SpriteFrame> spriteFrames;

    std::ifstream contents(path);

    auto data = json::parse(contents);

    if (data.contains("frames") && data["frames"].is_array())
    {
        for (const auto &frame : data["frames"])
        {
            std::string filename = frame.at("filename").get<std::string>();

            if (prefix.empty() || filename.find(prefix) == 0)
            {
                const auto &rect = frame.at("frame");

                SpriteFrame frameData;

                frameData.filename = filename;
                frameData.rect = {
                    rect.at("x").get<int>(), rect.at("y").get<int>(),
                    rect.at("w").get<int>(), rect.at("h").get<int>()};

                spriteFrames.emplace_back(frameData);
            };
        }
    }

    return spriteFrames;
}
