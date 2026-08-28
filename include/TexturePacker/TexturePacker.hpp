// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#include <vector>

#include <SDL3/SDL.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

inline auto LoadTexturePackerFramesFromMemory(const void *mem, std::size_t len,
                                              const std::string &prefix = "")
    -> std::vector<SDL_Rect>
{
    std::vector<SDL_Rect> spriteFrames;

    auto data = json::parse(static_cast<const char *>(mem),
                            static_cast<const char *>(mem) + len);

    if (data.contains("frames") && data["frames"].is_array())
    {
        for (const auto &frame : data["frames"])
        {
            std::string filename = frame.at("filename").get<std::string>();

            if (prefix.empty() || filename.find(prefix) == 0)
            {
                const auto &rect = frame.at("frame");

                spriteFrames.emplace_back(
                    SDL_Rect{rect.at("x").get<int>(), rect.at("y").get<int>(),
                             rect.at("w").get<int>(), rect.at("h").get<int>()});
            };
        }
    }

    return spriteFrames;
}

inline auto LoadTexturePackerFramesFromFile(const std::string &path,
                                            const std::string &prefix = "")
    -> std::vector<SDL_Rect>
{
    std::size_t len = 0;
    void *mem = SDL_LoadFile(path.c_str(), &len);

    if (mem == nullptr)
    {
        return {};
    }

    auto spriteFrames = LoadTexturePackerFramesFromMemory(
        static_cast<const char *>(mem), len, prefix);

    SDL_free(mem);

    return spriteFrames;
}
