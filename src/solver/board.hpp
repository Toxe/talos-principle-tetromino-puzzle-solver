#pragma once

#include <string>

#include "../grid/grid.hpp"
#include "placement_mask.hpp"
#include "square.hpp"
#include "tetrominoes.hpp"

namespace tptps {

struct Placement {
    Square coords;
    Tetromino tetromino;
    Rotation rotation;

    auto operator<=>(const Placement& rhs) const = default;
};

class Board {
public:
    Board(const int columns, const int rows) : grid_{columns, rows, Tetromino::empty} { }

    int width() const { return grid_.width(); }
    int height() const { return grid_.height(); }

    [[nodiscard]] bool can_place(Placement placement, const PlacementMask& mask) const;
    void place(Placement placement);

    [[nodiscard]] Tetromino at(const Square coords) const { return grid_.at(coords); }
    [[nodiscard]] bool is_empty_square(const Square coords) const { return grid_.at(coords) == Tetromino::empty; }

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_finished() const;

    [[nodiscard]] std::string print() const;

private:
    Grid<Tetromino, Square> grid_;
};

}  // namespace tptps
