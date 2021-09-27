#include "TetherFigure.hpp"

namespace tether {

    std::string TetherFigure::Name() const {
        return m_name;
    }

    std::double_t TetherFigure::X() const {
        return m_x;
    }

    std::double_t TetherFigure::Y() const {
        return m_y;
    }

    std::double_t TetherFigure::Width() const {
        return m_width;
    }

    std::double_t TetherFigure::Height() const {
        return m_height;
    }



} // namespace tether