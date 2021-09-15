#include "tether/Tether.hpp"

#include <cmath>
#include <cstddef>
#include <memory>

#include <eigen3/Eigen/Dense>


namespace tether {
	Tether::Tether(std::double_t length, std::size_t n) {
		m_length = length;
		m_n = n;

		// Temporary variables
		double mass = 1;
		double volume = 0.0001;
		double l = length / (n-1);

		Eigen::Vector3d X = Eigen::Vector3d::Zero(3);

		std::shared_ptr<TetherElement> previous_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
		std::shared_ptr<TetherElement> next_tether_element;
		m_head = previous_tether_element;

		for (std::size_t i = 1; i < m_n; i++) {
			X[0] += 0.1;
			X[1] = sin((double)i/15.);
			next_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
			previous_tether_element->SetNext(next_tether_element);
			next_tether_element->SetPrevious(previous_tether_element);
			previous_tether_element = next_tether_element;
		}
		m_tail = next_tether_element;
	}

	Tether::Tether(std::double_t length, std::size_t n, Eigen::Vector3d Xhead, Eigen::Vector3d Xtail) {
		m_length = length;
		m_n = n;

		// Temporary variables
		double mass = 1;
		double volume = 0.001;
		double l = length / (n-1);

		Eigen::Vector3d X = Xhead;

		std::shared_ptr<TetherElement> previous_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
		std::shared_ptr<TetherElement> next_tether_element;
		m_head = previous_tether_element;

		for (std::size_t i = 1; i < m_n; i++) {
			X[0] += 0.1;
			X[1] = sin((double)i/15.);
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
		tether_element->Step(h);
	}
}