#pragma once

#include <string>

#include "../grid/grid.hpp"
#include "square.hpp"
#include "tetrominoes.hpp"

namespace tptps {

class Board {
public:
    Board(const int columns, const int rows) : grid_{columns, rows, Tetromino::empty} { }

    [[nodiscard]] int width() const { return grid_.width(); }
    [[nodiscard]] int height() const { return grid_.height(); }

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_filled() const;

    [[nodiscard]] Tetromino at(const Square coords) const { return grid_.at(coords); }
    [[nodiscard]] Tetromino& at(const Square coords) { return grid_.at(coords); }

    [[nodiscard]] bool is_empty_square(const Square coords) const { return grid_.at(coords) == Tetromino::empty; }

    [[nodiscard]] std::string print() const;

private:
    Grid<Tetromino, Square> grid_;
};

}  // namespace tptps
