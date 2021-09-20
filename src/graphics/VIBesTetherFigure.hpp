#pragma once

#include "vibes.hpp"
#include "Tether.hpp"
#include "TetherElement.hpp"

#include <memory>
#include <string>

namespace tether {
	class VIBesTetherFigure {

		public: VIBesTetherFigure();

		public: VIBesTetherFigure(std::shared_ptr<Tether> tether);

		public: void AddTether(std::shared_ptr<Tether> tether);
		public: void ShowTether();
		public: void ShowEllipse();

		private: std::string m_figure_name;
        private: std::string m_tether_color;
        private: std::string m_head_tether_element_color;
        private: std::string m_tail_tether_element_color;
        private: std::string m_ellipse_color;
		private: std::shared_ptr<Tether> m_tether;
		private: std::double_t m_radius;
    };
};