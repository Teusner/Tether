#pragma once

#include <chrono>
#include <memory>
#include <math.h>
#include <string>

#include <ignition/math6/ignition/math/PID.hh>
#include <ignition/math6/ignition/math/Vector4.hh>

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
    /// \snippet examples/TetherElementExample.cpp example
	class TetherElement {

		/// \brief Constructor, TetherElement with mass, volume and length
		///
		/// \param[in] mass  The mass of the TetherElement.
		/// \param[in] length  The length between two TetherElements.
		/// \param[in] volume  The volume of the TetherElement.
		public: TetherElement(std::double_t mass, std::double_t volume, std::double_t length) : m_mass(mass), m_volume(volume), m_length(length) {};

		/// \brief Constructor, TetherElement with mass, volume, length and an initial state
		///
		/// \param[in] mass  The mass of the TetherElement.
		/// \param[in] length  The length between two TetherElements.
		/// \param[in] volume  The volume of the TetherElement.
		/// \param[in] X0  The initial state of the TetherElement.
		public: TetherElement(std::double_t mass, std::double_t volume, std::double_t length, ignition::math::Vector4d X0) : m_mass(mass), m_volume(volume), m_length(length), m_X(X0) {};

		/// \brief Default destructor of the TetherElement
		public: ~TetherElement() = default;


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

		/// \brief theta getter
		/// \return theta
		public: std::double_t Theta() const;

		/// \brief Position getter
		/// \return The current TetherElement Position
		public: ignition::math::Vector4d Position() const;

		/// \brief Velocity getter
		/// \return The current TetherElement Velocity
		public: ignition::math::Vector4d Velocity() const;

		/// \brief Acceleration getter
		/// \return The current TetherElement Acceleration
		public: ignition::math::Vector4d Acceleration() const;


		/// \brief Previous TetherElement
		/// \return Pointer to the previous TetherElement
		public: std::shared_ptr<TetherElement> Previous() const;

		/// \brief Next TetherElement
		/// \return Pointer to the next TetherElement
		public: std::shared_ptr<TetherElement> Next() const;



		/// \brief Previous TetherElement setter
		///
		/// Set the previous TetherElement pointer
		///
		public: void SetPrevious(std::shared_ptr<TetherElement> previous);

		/// \brief Next TetherElement setter
		///
		/// Set the next TetherElement pointer
		///
		public: void SetNext(std::shared_ptr<TetherElement> next);


		/// \brief Setter for the behavioral force and twist PID
		/// 
		/// \param[in] length_pid the PID used for length
		/// \param[in] twist_pid the PID used for twist
		public: void set_PID(const ignition::math::PID &length_pid, const ignition::math::PID &twist_pid);


		/// \brief Step method
		///
		/// The method used to compute and update the TetherElement state
		/// with the integration time-step h.
		///
		/// \param[in] h integration time in seconds
		public: void Step(std::double_t h);



		/// \brief State of the TetherElement
		/// The State of the TetherElement is X = [x, y, z, theta]
		private: ignition::math::Vector4d m_X = ignition::math::Vector4d::Zero;

		/// \brief Derivative state of the TetherElement
		private: ignition::math::Vector4d m_dX = ignition::math::Vector4d::Zero;

		/// \brief Two-time derivative state of the TetherElement
		private: ignition::math::Vector4d m_ddX = ignition::math::Vector4d::Zero;

		/// \brief the mass of the TetherElement
		private: std::double_t m_mass;

		/// The length of the adjacents links
		private: std::double_t m_length;

		/// \brief The volume of the TetherElement
		private: std::double_t m_volume;

		/// \brief Pointer to the previous TetherElement
		private: std::shared_ptr<TetherElement> m_previous = nullptr;

		/// \brief Pointer to the next TetherElement
		private: std::shared_ptr<TetherElement> m_next = nullptr;
		

		private:

			// Forces functions
			ignition::math::Vector4d Fg();
			ignition::math::Vector4d Fb();
			ignition::math::Vector4d Ff();
			ignition::math::Vector4d Ft_prev(double h);
			ignition::math::Vector4d Ft_next(double h);
			ignition::math::Vector4d Fr_prev(double h);
			ignition::math::Vector4d Fr_next(double h);

			// Behavioral Force PID on length and twist
			ignition::math::PID m_length_prev_PID;
			ignition::math::PID m_length_next_PID;
			ignition::math::PID m_twist_prev_PID;
			ignition::math::PID m_twist_next_PID;

			// Drag coefficient
			double m_drag_f = 10.;
	};
}; // namespace tether