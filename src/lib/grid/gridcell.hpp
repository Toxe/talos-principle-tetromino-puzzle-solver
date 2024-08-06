#pragma once

#include <cassert>

#include "coords.hpp"

namespace tptps {

template <typename GridPointer, typename CoordsType>
class GridCell : public CoordsType {
public:
    GridCell(GridPointer grid, const CoordsType& coords) : CoordsType(coords)
    {
        assert(grid != nullptr);
        grid_ = grid;
    }

    [[nodiscard]] auto& value() { return grid_->at(*this); }

private:
    GridPointer grid_;
};

}  // namespace tptps
