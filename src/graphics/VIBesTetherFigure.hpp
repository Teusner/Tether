#pragma once

#include "TetherFigure.hpp"
#include "Tether.hpp"

#include <memory>
#include <string>
#include <cmath>

namespace tether {
	class VIBesTetherFigure : public TetherFigure {

		public: VIBesTetherFigure(std::string name = "");

		public: ~VIBesTetherFigure() = default;

		public: void AddTether(std::shared_ptr<Tether> tether);
		public: void ShowTether();
		public: void ShowEllipse();

		private: std::shared_ptr<Tether> m_tether;
        private: std::string m_tether_color;
        private: std::string m_head_tether_element_color;
        private: std::string m_tail_tether_element_color;
        private: std::string m_ellipse_color;
		private: std::double_t m_radius;
    };
} // namespace tether