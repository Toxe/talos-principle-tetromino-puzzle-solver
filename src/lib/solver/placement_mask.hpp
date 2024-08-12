#pragma once

#include <bitset>
#include <string_view>
#include <vector>

#include "rotation.hpp"
#include "square.hpp"
#include "tetrominoes.hpp"

namespace tptps {

class PlacementMask {
public:
    PlacementMask(int width, int height);

    void set(Square square) { bits_.set(bit(square)); }
    [[nodiscard]] bool at(Square square) const { return bits_[bit(square)]; }

    [[nodiscard]] int width() const { return width_; }
    [[nodiscard]] int height() const { return height_; }

    bool operator==(const PlacementMask& rhs) const { return bits_ == rhs.bits_; }

private:
    std::bitset<16> bits_;

    int16_t width_;
    int16_t height_;

    [[nodiscard]] std::size_t bit(Square square) const;
};

PlacementMask placement_mask_from_string(const std::vector<std::string_view>& data);
PlacementMask get_tetromino_placement_mask(Tetromino tetromino, Rotation rotation);

}  // namespace tptps
