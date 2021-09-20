#include "VIBesTetherFigure.hpp"
#include "vibes.hpp"

#include <Eigen/Dense>

#include <memory>
#include <string>


namespace tether {
    VIBesTetherFigure::VIBesTetherFigure() {
        m_head_tether_element_color = "#27ae60[#27ae60]";
        m_tail_tether_element_color = "#c0392b[#c0392b]";
        m_tether_color = "#f1c40f[#f1c40f]";
        m_radius = 0.15;
    }

    VIBesTetherFigure::VIBesTetherFigure(std::shared_ptr<Tether> tether) {
        m_tether = tether;
        m_head_tether_element_color = "#27ae60[#27ae60]";
        m_tail_tether_element_color = "#c0392b[#c0392b]";
        m_tether_color = "#f1c40f[#f1c40f]";
        m_radius = 0.15;
    }

    void VIBesTetherFigure::AddTether(std::shared_ptr<Tether> tether) {
        m_tether = tether;
    }

    void VIBesTetherFigure::ShowTether() {
        // Showing the Tether
        std::shared_ptr<TetherElement> tether_element = m_tether->Head();
        std::vector<double> tether_x = {tether_element->X()};
        std::vector<double> tether_y = {tether_element->Z() + m_radius};
        while (tether_element != m_tether->Tail()) {
            tether_element = tether_element->Next();
            tether_x.push_back(tether_element->X());
            tether_y.push_back(tether_element->Z() + m_radius);
        }
        tether_x.push_back(tether_element->X());
        tether_y.push_back(tether_element->Z() - m_radius);
        while (tether_element != m_tether->Head()) {
            tether_element = tether_element->Previous();
            tether_x.push_back(tether_element->X());
            tether_y.push_back(tether_element->Z() - m_radius);
        }
        vibes::drawPolygon(tether_x, tether_y, m_tether_color);

        // Showing Head
        Eigen::Vector3d head_position = m_tether->Head()->Position();
        vibes::drawCircle(head_position[0], head_position[2], m_radius, m_head_tether_element_color);

        // Showing Tail
        Eigen::Vector3d tail_position = m_tether->Tail()->Position();
        vibes::drawCircle(tail_position[0], tail_position[2], m_radius, m_tail_tether_element_color);
    }
}
