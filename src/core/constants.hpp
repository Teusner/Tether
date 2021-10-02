#pragma once

#include <Eigen/Dense>

namespace constants {
    
    namespace earth {
        const Eigen::Vector3d g (0., 0., -9.81); // m.s^{-2}
    } // namespace earth

    namespace water {
        constexpr std::double_t rho = 997.0; // kg.m^{-3}
    } // namespace water

} // namespace constants