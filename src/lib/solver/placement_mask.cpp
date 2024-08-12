#include "placement_mask.hpp"

#include <array>
#include <cassert>
#include <stdexcept>

namespace tptps {

PlacementMask::PlacementMask(const int width, const int height)
{
    assert(width >= 0 && width <= 4);
    assert(height >= 0 && height <= 4);
    assert(width * height > 0);

    width_ = static_cast<int16_t>(width);
    height_ = static_cast<int16_t>(height);
}

std::size_t PlacementMask::bit(const Square square) const
{
    assert(square.x >= 0 && square.x < width_);
    assert(square.y >= 0 && square.y < height_);

    const std::size_t pos = square.x + square.y * width_;

    assert(pos < width_ * height_);

    return pos;
}

PlacementMask placement_mask_from_string(const std::vector<std::string_view>& data)
{
    assert(data.size() > 0);

    const int width = static_cast<int>(data.begin()->size());
    const int height = static_cast<int>(data.size());

    assert(width > 0);

    PlacementMask mask{width, height};
    Square::coordinates_type row = 0;

    for (const auto& line : data) {
        assert(line.size() == static_cast<std::size_t>(mask.width()));

        for (Square::coordinates_type col = 0; col < mask.width(); ++col)
            if (line[static_cast<std::size_t>(col)] != '.')
                mask.set({col, row});

        ++row;
    }

    return mask;
}

PlacementMask get_tetromino_placement_mask(Tetromino tetromino, Rotation rotation)
{
    static std::array<PlacementMask, 4> masks_I{
        placement_mask_from_string({
            "####",
        }),
        placement_mask_from_string({
            "#",
            "#",
            "#",
            "#",
        }),
        placement_mask_from_string({
            "####",
        }),
        placement_mask_from_string({
            "#",
            "#",
            "#",
            "#",
        }),
    };

    static std::array<PlacementMask, 4> masks_O{
        placement_mask_from_string({
            "##",
            "##",
        }),
        placement_mask_from_string({
            "##",
            "##",
        }),
        placement_mask_from_string({
            "##",
            "##",
        }),
        placement_mask_from_string({
            "##",
            "##",
        }),
    };

    static std::array<PlacementMask, 4> masks_T{
        placement_mask_from_string({
            "###",
            ".#.",
        }),
        placement_mask_from_string({
            ".#",
            "##",
            ".#",
        }),
        placement_mask_from_string({
            ".#.",
            "###",
        }),
        placement_mask_from_string({
            "#.",
            "##",
            "#.",
        }),
    };

    static std::array<PlacementMask, 4> masks_J{
        placement_mask_from_string({
            ".#",
            ".#",
            "##",
        }),
        placement_mask_from_string({
            "#..",
            "###",
        }),
        placement_mask_from_string({
            "##",
            "#.",
            "#.",
        }),
        placement_mask_from_string({
            "###",
            "..#",
        }),
    };

    static std::array<PlacementMask, 4> masks_L{
        placement_mask_from_string({
            "#.",
            "#.",
            "##",
        }),
        placement_mask_from_string({
            "###",
            "#..",
        }),
        placement_mask_from_string({
            "##",
            ".#",
            ".#",
        }),
        placement_mask_from_string({
            "..#",
            "###",
        }),
    };

    static std::array<PlacementMask, 4> masks_S{
        placement_mask_from_string({
            ".##",
            "##.",
        }),
        placement_mask_from_string({
            "#.",
            "##",
            ".#",
        }),
        placement_mask_from_string({
            ".##",
            "##.",
        }),
        placement_mask_from_string({
            "#.",
            "##",
            ".#",
        }),
    };

    static std::array<PlacementMask, 4> masks_Z{
        placement_mask_from_string({
            "##.",
            ".##",
        }),
        placement_mask_from_string({
            ".#",
            "##",
            "#.",
        }),
        placement_mask_from_string({
            "##.",
            ".##",
        }),
        placement_mask_from_string({
            ".#",
            "##",
            "#.",
        }),
    };

    assert(tetromino != Tetromino::empty);

    std::array<PlacementMask, 4>* masks = nullptr;

    switch (tetromino) {
        case Tetromino::I: masks = &masks_I; break;
        case Tetromino::O: masks = &masks_O; break;
        case Tetromino::T: masks = &masks_T; break;
        case Tetromino::J: masks = &masks_J; break;
        case Tetromino::L: masks = &masks_L; break;
        case Tetromino::S: masks = &masks_S; break;
        case Tetromino::Z: masks = &masks_Z; break;
        case Tetromino::empty: throw std::runtime_error{"invalid tetromino"};
    }

    std::size_t idx = 0;

    switch (rotation) {
        case Rotation::r0: idx = 0; break;
        case Rotation::r90: idx = 1; break;
        case Rotation::r180: idx = 2; break;
        case Rotation::r270: idx = 3; break;
    }

    assert(masks != nullptr);

    return masks->at(idx);
}

}  // namespace tptps
