#include "placement_mask.hpp"

#include <array>
#include <cassert>
#include <stdexcept>

namespace tptps {

PlacementMask placement_mask_from_string(const std::vector<std::string_view>& data)
{
    assert(data.size() > 0);

    const int width = static_cast<int>(data.begin()->size());
    const int height = static_cast<int>(data.size());

    assert(width > 0);

    PlacementMask mask{width, height};
    int row = 0;

    for (const auto& line : data) {
        assert(line.size() == static_cast<std::size_t>(mask.width()));

        for (int col = 0; col < mask.width(); ++col)
            mask.at(col, row) = line[static_cast<std::size_t>(col)] != '.' ? 1 : 0;

        ++row;
    }

    return mask;
}

using placement_mask_def = std::vector<std::string_view>;

PlacementMask get_tetromino_placement_mask(Tetromino tetromino, Rotation rotation)
{
    static std::array<placement_mask_def, 4> masks_I{
        placement_mask_def{
            "####",
        },
        placement_mask_def{
            "#",
            "#",
            "#",
            "#",
        },
        placement_mask_def{
            "####",
        },
        placement_mask_def{
            "#",
            "#",
            "#",
            "#",
        },
    };

    static std::array<placement_mask_def, 4> masks_O{
        placement_mask_def{
            "##",
            "##",
        },
        placement_mask_def{
            "##",
            "##",
        },
        placement_mask_def{
            "##",
            "##",
        },
        placement_mask_def{
            "##",
            "##",
        },
    };

    static std::array<placement_mask_def, 4> masks_T{
        placement_mask_def{
            "###",
            ".#.",
        },
        placement_mask_def{
            ".#",
            "##",
            ".#",
        },
        placement_mask_def{
            ".#.",
            "###",
        },
        placement_mask_def{
            "#.",
            "##",
            "#.",
        },
    };

    static std::array<placement_mask_def, 4> masks_J{
        placement_mask_def{
            ".#",
            ".#",
            "##",
        },
        placement_mask_def{
            "#..",
            "###",
        },
        placement_mask_def{
            "##",
            "#.",
            "#.",
        },
        placement_mask_def{
            "###",
            "..#",
        },
    };

    static std::array<placement_mask_def, 4> masks_L{
        placement_mask_def{
            "#.",
            "#.",
            "##",
        },
        placement_mask_def{
            "###",
            "#..",
        },
        placement_mask_def{
            "##",
            ".#",
            ".#",
        },
        placement_mask_def{
            "..#",
            "###",
        },
    };

    static std::array<placement_mask_def, 4> masks_S{
        placement_mask_def{
            ".##",
            "##.",
        },
        placement_mask_def{
            "#.",
            "##",
            ".#",
        },
        placement_mask_def{
            ".##",
            "##.",
        },
        placement_mask_def{
            "#.",
            "##",
            ".#",
        },
    };

    static std::array<placement_mask_def, 4> masks_Z{
        placement_mask_def{
            "##.",
            ".##",
        },
        placement_mask_def{
            ".#",
            "##",
            "#.",
        },
        placement_mask_def{
            "##.",
            ".##",
        },
        placement_mask_def{
            ".#",
            "##",
            "#.",
        },
    };

    assert(tetromino != Tetromino::empty);

    std::array<placement_mask_def, 4>* masks = nullptr;

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

    return placement_mask_from_string(masks->at(idx));
}

}  // namespace tptps
