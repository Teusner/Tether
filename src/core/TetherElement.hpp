/// \file TetherElement.hpp
/// Implementation of TetherElement

#pragma once

#include <chrono>
#include <memory>
#include <math.h>
#include <string>

#include "PID.hpp"

#include <Eigen/Dense>


namespace tether {

	/// \class TetherElement TetherElement.hpp tether/TetherElement.hpp
    /// \brief TetherElement to hold the state of a discretized tether element.
	///
	/// ## Doubly Linked List structure
	///
	/// TetherElement has to be used as node in a doubly linked list to simulate a Tether.
	/// The idea is to set the previous and the next TetherElement using
	/// TetherElement::SetPrevious and TetherElement::SetNext
    ///
    /// ## Example
	///
	/// Here is a basic example of TetherElement use. It instanciate a TetherElement with some parameters,
	/// and show how to access these parameters through methods.
    ///
    /// \snippet examples/core/TetherElementExample.cpp example
	class TetherElement {

		/// \name Definition
      	/// @{

		/// \brief Constructor, TetherElement with mass, volume and length
		///
		/// \param[in] mass  The mass of the TetherElement.
		/// \param[in] length  The length between two TetherElements.
		/// \param[in] volume  The volume of the TetherElement.
		public: explicit TetherElement(std::double_t mass, std::double_t volume, std::double_t length) : m_mass(mass), m_volume(volume), m_length(length) {};

		/// \brief Constructor, TetherElement with mass, volume, length and an initial state
		///
		/// \param[in] mass  The mass of the TetherElement.
		/// \param[in] length  The length between two TetherElements.
		/// \param[in] volume  The volume of the TetherElement.
		/// \param[in] X0  The initial state of the TetherElement.
		public: explicit TetherElement(std::double_t mass, std::double_t volume, std::double_t length, Eigen::Vector3d X0) : m_mass(mass), m_volume(volume), m_length(length), m_X(X0) {};

		/// \brief Default destructor of the TetherElement
		public: ~TetherElement() = default;

		/// @}
		/// \name Accessing values
      	/// @{

		/// \brief Length getter
		/// \return Length between the TetherElement and its neighbors
		public: std::double_t Length() const;

		/// \brief Mass getter
		/// \return Mass of the TetherElement
		public: std::double_t Mass() const;

		/// \brief Volume getter
		/// \return Volume of the TetherElement
		public: std::double_t Volume() const;

		/// \brief x-axis coordinate getter
		/// \return x-axis coordinate
		public: std::double_t X() const;

		/// \brief y-axis coordinate getter
		/// \return y-axis coordinate
		public: std::double_t Y() const;

		/// \brief z-axis coordinate getter
		/// \return z-axis coordinate
		public: std::double_t Z() const;

		/// \brief Position getter
		/// \return The current TetherElement Position
		public: Eigen::Vector3d Position() const;

		/// \brief Velocity getter
		/// \return The current TetherElement Velocity
		public: Eigen::Vector3d Velocity() const;

		/// \brief Acceleration getter
		/// \return The current TetherElement Acceleration
		public: Eigen::Vector3d Acceleration() const;

		/// \brief Previous TetherElement
		/// \return Pointer to the previous TetherElement
		public: std::shared_ptr<TetherElement> Previous() const;

		/// \brief Next TetherElement
		/// \return Pointer to the next TetherElement
		public: std::shared_ptr<TetherElement> Next() const;

		/// \brief Previous TetherElement setter
		/// Set the previous TetherElement pointer
		public: std::double_t PreviousLength() const;

		/// \brief Next TetherElement setter
		/// Set the next TetherElement pointer
		public: std::double_t NextLength() const;

		/// @}
		/// \name Setting values
		/// @{

		/// \brief Previous TetherElement setter
		/// Set the previous TetherElement pointer
		public: void SetPrevious(const std::shared_ptr<TetherElement> previous);

		/// \brief Next TetherElement setter
		/// Set the next TetherElement pointer
		public: void SetNext(const std::shared_ptr<TetherElement> next);

		/// @}
		/// \name Forces
		/// @{

		/// \brief Gravity force
		/// Compute the gravity force applied on the TetherElement
		/// \f$\mathbf{F_g} = - m \cdot \mathbf{g}\f$
		/// \return The computed gravity force
		public: Eigen::Vector3d Fg() const;

		/// \brief The buoyancy force
		/// Compute the buoyancy force applied on the TetherElement
		/// \f$\mathbf{F_b} = - \rho \cdot V \cdot \mathbf{g}\f$
		/// \return The computed gravity force
		public: Eigen::Vector3d Fb() const;

		/// \brief The hydrodynamic drag force
		/// Compute the hydrodynamic drag force applied on the TetherElement
		/// \f$\mathbf{F_f} = - f \cdot |\mathbf{V}| \cdot \mathbf{V}\f$
		/// \return The computed gravity force
		/// \return The hydrodynamic drag force applied to the TetherElement
		public: Eigen::Vector3d Ff() const;

		/// \brief The previous behavioral force
		/// The previous force induced by the previous TetherElement
		/// on the current TetherElement. For this force a behavioral model
		/// based on a PID corrector is purposed to reach a correct distance
		/// between the current TetherElement and the previous one.
		/// \return The previous behavioral force 
		public: Eigen::Vector3d Ft_prev() const;

		/// \brief The next behavioral force
		/// The next force induced by the next TetherElement
		/// on the current TetherElement. For this force a behavioral model
		/// based on a PID corrector is purposed to reach a correct distance
		/// between the current TetherElement and the next one.
		/// \return The next behavioral force 
		public: Eigen::Vector3d Ft_next() const;

		/// \brief Set the PID for the behavioral model
		/// Set the PID used to compute the behavioral model of force
		/// generated by neighbors and applied on each TetherElement.
		/// \param[in] length_pid the PID used for length
		public: void SetPID(const PID &length_pid);

		/// @}
		/// \name Simulation
		/// @{

		/// \brief Step method
		///
		/// The method used to compute and update the TetherElement state
		/// with the integration time-step h.
		///
		/// \param[in] h integration time in seconds
		public: void Step(const std::double_t h);

		/// @}

		/// \brief the mass of the TetherElement
		private: std::double_t m_mass;

		/// \brief The volume of the TetherElement
		private: std::double_t m_volume;

		/// The length of the adjacents links
		private: std::double_t m_length;

		/// \brief State of the TetherElement
		private: Eigen::Vector3d m_X = Eigen::Vector3d::Zero(3);

		/// \brief Derivative state of the TetherElement
		/// The derivative State of the TetherElement is dX = [dx, dy, dz]
		private: Eigen::Vector3d m_dX = Eigen::Vector3d::Zero(3);

		/// \brief Two-time derivative state of the TetherElement
		/// The derivative State of the TetherElement is ddX = [ddx, ddy, ddz]
		private: Eigen::Vector3d m_ddX = Eigen::Vector3d::Zero(3);

		/// \brief Pointer to the previous TetherElement
		private: std::shared_ptr<TetherElement> m_previous = nullptr;

		/// \brief Pointer to the next TetherElement
		private: std::shared_ptr<TetherElement> m_next = nullptr;

		private:
			// Forces functions
			Eigen::Vector3d Fr_prev(std::double_t h);
			Eigen::Vector3d Fr_next(std::double_t h);

			// Behavioral Force PID on length and twist
			PID m_length_prev_PID = PID(30.0, 0.0, 2.0);
			PID m_length_next_PID = PID(30.0, 0.0, 2.0);
			PID m_twist_prev_PID;
			PID m_twist_next_PID;

			// Drag coefficient
			double m_drag_f = 10.;
	};
}; // namespace tether