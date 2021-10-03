#include "VIBesTetherFigure.hpp"
#include "vibes.hpp"

#include <Eigen/Dense>

#include <cmath>
#include <iostream>
#include <memory>
#include <string>


namespace tether {
    VIBesTetherFigure::VIBesTetherFigure(std::string name) : TetherFigure(name) {
        vibes::beginDrawing();
        vibes::newFigure(m_name);
        vibes::setFigureProperties(vibesParams("x", m_x, "y", m_y, "width", m_width, "height", m_height));

        vibes::newGroup("Tether");
        vibes::newGroup("Head");
        vibes::newGroup("Tail");

        m_head_tether_element_color = "#27ae60[#27ae60]";
        m_tail_tether_element_color = "#c0392b[#c0392b]";
        m_tether_color = "#f1c40f[#f1c40f]";
        m_ellipse_color = "#3498db[#2980b9]";
        m_radius = 0.1;
    }

    void VIBesTetherFigure::AddTether(std::shared_ptr<Tether> tether) {
        m_tether = tether;
    }

    void VIBesTetherFigure::Axis() const {
        Eigen::Vector3d y = (m_tether->Tail()->Position() + m_tether->Head()->Position()) / 2.;
        vibes::axisLimits(y[0] - m_tether->Length() / 2., y[0] + m_tether->Length() / 2., y[2] - m_tether->Length() / 2., y[2] + m_tether->Length() / 2.);
        vibes::setFigureProperties(vibesParams("x", m_x, "y", m_y, "width", m_width, "height", m_height));
    }

    void VIBesTetherFigure::ShowTether() {
        // Drawing the Tether
        std::size_t i = 1;
        std::shared_ptr<TetherElement> tether_element = m_tether->Head()->Next();
        double theta = M_PI_2 + std::atan2(tether_element->Z() - m_tether->Head()->Z(), tether_element->X() - m_tether->Head()->X());
        std::vector<double> tether_x = {m_tether->Head()->X() + m_radius * std::cos(theta), m_tether->Head()->X() - m_radius * std::cos(theta)};
        std::vector<double> tether_y = {m_tether->Tail()->Z() + m_radius * std::sin(theta), m_tether->Tail()->Z() - m_radius * std::sin(theta)};
        while (tether_element->Next() != nullptr) {
            theta = M_PI_2 + 0.5 * (std::atan2(tether_element->Next()->Z() - tether_element->Z(), tether_element->Next()->X() - tether_element->X()) + std::atan2(tether_element->Z() - tether_element->Previous()->Z(), tether_element->X() - tether_element->Previous()->X()));
            tether_x.insert(tether_x.begin() + i, tether_element->X() + m_radius * std::cos(theta));
            tether_x.insert(tether_x.begin() + i + 1, tether_element->X() - m_radius * std::cos(theta));
            tether_y.insert(tether_y.begin() + i, tether_element->Z() + m_radius * std::sin(theta));
            tether_y.insert(tether_y.begin() + i + 1, tether_element->Z() - m_radius * std::sin(theta));
            tether_element = tether_element->Next();
            i++;
        }
        tether_x.insert(tether_x.begin() + i, tether_element->X() + m_radius * std::cos(theta));
        tether_x.insert(tether_x.begin() + i + 1, tether_element->X() - m_radius * std::cos(theta));
        tether_y.insert(tether_y.begin() + i, tether_element->Z() + m_radius * std::sin(theta));
        tether_y.insert(tether_y.begin() + i + 1, tether_element->Z() - m_radius * std::sin(theta));

        vibes::clearGroup("Tether");
        vibes::drawPolygon(tether_x, tether_y, m_tether_color, vibesParams("group", "Tether"));

        // Showing Head and tail
        vibes::drawCircle(m_tether->Head()->X(), m_tether->Head()->Z(), m_radius, m_head_tether_element_color, vibesParams("group", "Head"));
        vibes::drawCircle(m_tether->Tail()->X(), m_tether->Tail()->Z(), m_radius, m_tail_tether_element_color, vibesParams("group", "Tail"));
        Axis();
    }

    void VIBesTetherFigure::ShowEllipse() {
        double a = m_tether->Length();
        double c = (m_tether->Head()->Position() - m_tether->Tail()->Position()).norm() / 2.;
        double b = std::sqrt(std::pow(a, 2) - std::pow(c, 2));
        double theta = std::atan2(m_tether->Tail()->Z() - m_tether->Head()->Z(), m_tether->Tail()->X() - m_tether->Head()->X());
        double cx = (m_tether->Head()->X() + m_tether->Tail()->X()) / 2.;
        double cy = (m_tether->Head()->Z() + m_tether->Tail()->Z()) / 2.;
        vibes::drawEllipse(cx, cy, a, b, theta, m_ellipse_color);
    }
} // namespace tether