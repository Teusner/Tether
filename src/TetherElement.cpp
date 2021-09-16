#include "tether/TetherElement.hpp"
#include "tether/constants.hpp"

#include <chrono>
#include <memory>

#include <ignition/math6/ignition/math/PID.hh>
#include <eigen3/Eigen/Dense>


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

	Eigen::Vector3d TetherElement::Position() const {
		return m_X;
	}

	Eigen::Vector3d TetherElement::Velocity() const {
		return m_dX;
	}

	Eigen::Vector3d TetherElement::Acceleration() const {
		return Fg() + Fb() + Ft_prev() + Ft_next() + Ff();
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

	void TetherElement::SetPID(const ignition::math::PID &length_pid) {
		m_length_prev_PID = length_pid;
		m_length_next_PID = length_pid;
	}

	void TetherElement::SetPrevious(const std::shared_ptr<TetherElement> previous) {
		m_previous = previous;
	}

	void TetherElement::SetNext(const std::shared_ptr<TetherElement> next) {
		m_next = next;
	}

	std::shared_ptr<TetherElement> TetherElement::Previous() const {
		return m_previous;
	}

	std::shared_ptr<TetherElement> TetherElement::Next() const {
		return m_next;
	}

	std::double_t TetherElement::PreviousLength() const {
		return (m_previous->Position() - Position()).norm();
	}

	std::double_t TetherElement::NextLength() const {
		return (m_next->Position() - Position()).norm();
	}

	Eigen::Vector3d TetherElement::Fg() const {
		return m_mass * constants::earth::g;
	}

	Eigen::Vector3d TetherElement::Fb() const {
		return - constants::water::rho * m_volume * constants::earth::g;
	}

	Eigen::Vector3d TetherElement::Ff() const  {
		return - m_drag_f * (m_dX.cwiseAbs().array() * m_dX.array()).matrix();
	}

	Eigen::Vector3d TetherElement::Ft_prev() const {
		if (m_previous != nullptr)
			return - m_length_prev_PID.Cmd() * (m_previous->Position() - Position()) / PreviousLength();
		else
			return Eigen::Vector3d::Zero(3);
	}

	Eigen::Vector3d TetherElement::Ft_next() const {
		if (m_next != nullptr)
			return - m_length_next_PID.Cmd() * (m_next->Position() - Position()) / NextLength();
		else
			return Eigen::Vector3d::Zero(3);
	}

	Eigen::Vector3d TetherElement::Fr_prev(const std::double_t h) {
		Eigen::Vector3d force = Eigen::Vector3d::Zero(3);

		if (m_previous != nullptr) {
			// Updating PID
			m_twist_prev_PID.Update(m_X[3] - m_previous->Position()[3], std::chrono::duration<double>(h));

			// Computing force
			force[3] = - m_twist_prev_PID.Cmd();
		}
		return force;
	}

	Eigen::Vector3d TetherElement::Fr_next(const std::double_t h) {
		Eigen::Vector3d force = Eigen::Vector3d::Zero(3);

		if (m_next != nullptr) {
			// Updating PID
			m_twist_prev_PID.Update(m_next->Position()[3] - m_X[3], std::chrono::duration<double>(h));

			// Computing force
			force[3] = - m_twist_next_PID.Cmd();
		}
		return force;
	}

	void TetherElement::Step(const std::double_t h) {
		if ((m_previous != nullptr) && (m_next != nullptr)) {
			// Updating PID
			m_length_prev_PID.Update(PreviousLength() - m_length, std::chrono::duration<std::double_t>(h * 1000));
			m_length_next_PID.Update(NextLength() - m_length, std::chrono::duration<std::double_t>(h * 1000));

			// Computing next state using Euler's integration
			m_dX += h * Acceleration();
			m_X += h * m_dX;
		}
	}
} // namespace tether