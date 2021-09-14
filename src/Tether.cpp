#include "tether/Tether.hpp"

#include <cmath>
#include <cstddef>
#include <memory>


namespace tether {
	Tether::Tether(std::double_t length, std::size_t n) {
		m_length = length;
		m_n = n;

		// Temporary variables
		double mass = 1;
		double volume = 1;
		double l = 1;

		ignition::math::Vector4d X = ignition::math::Vector4d::Zero;

		std::shared_ptr<TetherElement> previous_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
		std::shared_ptr<TetherElement> next_tether_element;
		m_head = previous_tether_element;

		for (std::size_t i = 1; i < m_n; i++) {
			X.X() += 0.1;
			X.Y() = sin((double)i/15.);
			next_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
			previous_tether_element->SetNext(next_tether_element);
			next_tether_element->SetPrevious(previous_tether_element);
			previous_tether_element = next_tether_element;
		}
		m_tail = next_tether_element;
	}

	Tether::Tether(std::double_t length, std::size_t n, ignition::math::Vector4d Xhead, ignition::math::Vector4d Xtail) {
		m_length = length;
		m_n = n;

		// Temporary variables
		double mass = 1;
		double volume = 1;
		double l = 1;

		ignition::math::Vector4d X = Xhead;

		std::shared_ptr<TetherElement> previous_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
		std::shared_ptr<TetherElement> next_tether_element;
		m_head = previous_tether_element;

		for (std::size_t i = 1; i < m_n; i++) {
			X.X() += 0.1;
			X.Y() = sin((double)i/15.);
			next_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
			previous_tether_element->SetNext(next_tether_element);
			next_tether_element->SetPrevious(previous_tether_element);
			previous_tether_element = next_tether_element;
		}
		m_tail = next_tether_element;
	}

	std::size_t Tether::N() const {
		return m_n;
	}

	std::double_t Tether::Length() const {
		return m_length;
	}
	
	std::shared_ptr<TetherElement> Tether::Head() const {
		return m_head;
	}

	std::shared_ptr<TetherElement> Tether::Tail() const {
		return m_tail;
	}

	void Tether::Step(double h) {
		std::shared_ptr<TetherElement> tether_element = m_head;
		while (tether_element != m_tail) {
			tether_element->Step(h);
			tether_element = tether_element->Next();
		}
	}
}