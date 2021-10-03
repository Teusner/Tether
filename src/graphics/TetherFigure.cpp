#include "TetherFigure.hpp"
#include "vibes.hpp"

#include <memory>
#include <string>

namespace tether {
    std::string TetherFigure::Name() const {
        return m_name;
    }

    int TetherFigure::X() const {
        return m_x;
    }

    int TetherFigure::Y() const {
        return m_y;
    }

    int TetherFigure::Width() const {
        return m_width;
    }

    int TetherFigure::Height() const {
        return m_height;
    }
} // namespace tether