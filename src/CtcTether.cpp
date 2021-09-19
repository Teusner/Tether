#include "tether/CtcTether.hpp"
#include <Eigen/Dense>
#include <cmath>

namespace tether {

    void CtcTether::AddTether(std::shared_ptr<Tether> tether) {
        m_tether = tether;
        m_a = m_tether->Length() / 2.;
        m_c = (m_tether->Head()->Position() - m_tether->Tail()->Position()).norm() / 2.;
        m_b = std::sqrt(std::pow(m_a, 2) - std::pow(m_c, 2));
        m_theta = std::atan2(m_b, m_c);

        Eigen::Vector3d x = m_tether->Tail()->Position() - m_tether->Head()->Position();
        m_alpha = std::atan2(x[2], x[0]);

        m_r = std::sqrt(std::pow(m_a, 2) + std::pow(m_b, 2));

        Eigen::Vector3d y = (m_tether->Tail()->Position() + m_tether->Head()->Position()) / 2.;
        m_mid = ibex::IntervalVector(2);
        m_mid[0] = ibex::Interval(y[0] - m_r * std::cos(m_alpha + m_theta), y[0] + m_r * std::cos(m_alpha + m_theta));
        m_mid[1] = ibex::Interval(y[2] -  m_r * std::sin(m_alpha + m_theta), y[2] +  m_r * std::sin(m_alpha + m_theta));
    }

    void CtcTether::contract(ibex::IntervalVector& box) {
        std::cout << m_a << " " << m_b << " " << m_c << std::endl;
        std::cout << m_alpha << " " << m_theta << " " << m_r << std::endl;
       
        box[0] &= m_mid[0];
        box[1] &= m_mid[0];
    }
}