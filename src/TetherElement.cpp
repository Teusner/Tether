#include "tether/TetherElement.hpp"
#include "tether/constants.hpp"

#include <chrono>
#include <memory>

#include <ignition/math6/ignition/math/PID.hh>
#include <ignition/math6/ignition/math/Vector4.hh>


namespace tether {

	std::double_t TetherElement::X() const {
		return m_X[0];
	}

	std::double_t TetherElement::Y() const {
		return m_X[1];
	}

	std::double_t TetherElement::Z() const {
		return m_X[2];
	}

	std::double_t TetherElement::Theta() const {
		return m_X[3];
	}

	ignition::math::Vector4d TetherElement::Position() const {
		return m_X;
	}

	ignition::math::Vector4d TetherElement::Velocity() const {
		return m_dX;
	}

	ignition::math::Vector4d TetherElement::Acceleration() const {
		return m_ddX;
	}

	std::double_t TetherElement::Volume() const {
		return m_volume;
	}

	std::double_t TetherElement::Mass() const {
		return m_mass;
	}

	std::double_t TetherElement::Length() const {
		return m_length;
	}

	void TetherElement::SetPrevious(std::shared_ptr<TetherElement> previous) {
		m_previous = previous;
	}

	void TetherElement::SetNext(std::shared_ptr<TetherElement> next) {
		m_next = next;
	}

	std::shared_ptr<TetherElement> TetherElement::Previous() const {
		return m_previous;
	}

	std::shared_ptr<TetherElement> TetherElement::Next() const {
		return m_next;
	}

	ignition::math::Vector4d TetherElement::Fg() {
		ignition::math::Vector4d force(0., 0., - m_mass * constants::earth::g, 0.);
		return force;
	}

	ignition::math::Vector4d TetherElement::Fb() {
		ignition::math::Vector4d force(0., 0., constants::water::rho * m_volume * constants::earth::g, 0.);
		return force;
	}

	ignition::math::Vector4d TetherElement::Ff() {
		ignition::math::Vector4d force = - m_drag_f * m_dX.Abs() * m_dX;
		return force;
	}

	ignition::math::Vector4d TetherElement::Ft_prev(double h) {
		ignition::math::Vector4d force = ignition::math::Vector4d::Zero;

		if (m_previous != nullptr) {
			ignition::math::Vector4d u = (m_previous->Position() - m_X);
			u[3] = 0.;
			u.Normalize();

			// Updating PID
			m_length_prev_PID.Update(u.Length() - m_length, std::chrono::duration<double>(h));

			// Computing force
			force = - m_length_prev_PID.Cmd() * u;
		}
		return force;
	}

	ignition::math::Vector4d TetherElement::Ft_next(double h) {
		ignition::math::Vector4d force = ignition::math::Vector4d::Zero;

		if (m_next != nullptr) {
			ignition::math::Vector4d u = (m_next->Position() - m_X);
			u[3] = 0.;
			u.Normalize();

			// Updating PID
			m_length_next_PID.Update(u.Length() - m_length, std::chrono::duration<double>(h));

			// Computing force
			force = - m_length_next_PID.Cmd() * u;
		}
		return force;
	}

	ignition::math::Vector4d TetherElement::Fr_prev(double h) {
		ignition::math::Vector4d force = ignition::math::Vector4d::Zero;

		if (m_previous != nullptr) {
			// Updating PID
			m_twist_prev_PID.Update(m_X[3] - m_previous->Position()[3], std::chrono::duration<double>(h));

			// Computing force
			force[3] = - m_twist_prev_PID.Cmd();
		}
		return force;
	}

	ignition::math::Vector4d TetherElement::Fr_next(double h) {
		ignition::math::Vector4d force = ignition::math::Vector4d::Zero;

		if (m_next != nullptr) {
			// Updating PID
			m_twist_prev_PID.Update(m_next->Position()[3] - m_X[3], std::chrono::duration<double>(h));

			// Computing force
			force[3] = - m_twist_next_PID.Cmd();
		}
		return force;
	}

	void TetherElement::Step(double h) {
		// Getting sum of the forces
		m_ddX = Fg() + Fb() + Ft_prev(h) + Ft_next(h) + Ff();

		// Computing next state using Euler's integration
		if (m_previous && m_next) {
			m_dX += h * m_ddX;
			m_X += h * m_dX;
		}
	}
} // namespace tether