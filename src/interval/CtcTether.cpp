#include "CtcTether.hpp"
#include <Eigen/Dense>
#include <cmath>

namespace tether {

    void CtcTether::AddTether(std::shared_ptr<Tether> tether) {
        m_tether = tether;
        m_a = m_tether->Length() / 2.;
        m_c = (m_tether->Head()->Position() - m_tether->Tail()->Position()).norm() / 2.;
        m_b = std::sqrt(std::pow(m_a, 2) - std::pow(m_c, 2));

        Eigen::Vector3d x = m_tether->Tail()->Position() - m_tether->Head()->Position();
        m_theta = std::atan2(x[2], x[0]);

        m_r = std::sqrt(std::pow(m_a, 2) + std::pow(m_b, 2));

        Eigen::Vector3d y = (m_tether->Tail()->Position() + m_tether->Head()->Position()) / 2.;
        m_mid = ibex::IntervalVector(2);
        m_mid[0] = ibex::Interval(y[0]) + std::sqrt(std::pow(m_a, 2) * std::pow(std::cos(m_theta), 2) + std::pow(m_b, 2) * std::pow(std::sin(m_theta), 2)) * ibex::Interval(-1,1);
        m_mid[1] = ibex::Interval(y[2]) + std::sqrt(std::pow(m_a, 2) * std::pow(std::sin(m_theta), 2) + std::pow(m_b, 2) * std::pow(std::cos(m_theta), 2)) * ibex::Interval(-1,1);
    }

    void CtcTether::contract(ibex::IntervalVector& box) {
        box[0] &= m_mid[0];
        box[1] &= m_mid[1];
    }
}