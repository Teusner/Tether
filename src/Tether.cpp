#include "tether/Tether.hpp"

#include <cmath>
#include <cstddef>
#include <memory>


namespace tether {
	Tether::Tether() {
		m_n = 100;

		// Temporary variables
		double mass = 1;
		double volume = 1;
		double length = 1;


		ignition::math::Vector4d X = ignition::math::Vector4d::Zero;

		std::shared_ptr<TetherElement> previous_tether_element = std::make_shared<TetherElement>(mass, volume, length, X);
		std::shared_ptr<TetherElement> next_tether_element;
		m_head = previous_tether_element;

		for (std::size_t i = 1; i < m_n; i++) {
			X.X() += 0.1;
			X.Y() = sin((double)i/15.);
			next_tether_element = std::make_shared<TetherElement>(mass, volume, length, X);
			previous_tether_element->SetNext(next_tether_element);
			next_tether_element->SetPrevious(previous_tether_element);
			previous_tether_element = next_tether_element;
		}
		m_tail = next_tether_element;
	}

	std::size_t Tether::N() {
		return m_n;
	}

	std::double_t Tether::Length() {
		return m_l;
	}
	
	std::shared_ptr<TetherElement> Tether::Head() {
		return m_head;
	}

	std::shared_ptr<TetherElement> Tether::Tail() {
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