#pragma once

#include <cmath>
#include <cstddef>
#include <memory>

#include "tether/TetherElement.hpp"

namespace tether {

	/// \class Tether Tether.hpp tether/Tether.hpp
    /// \brief Tether class to simulate tethers using a doubly linked list of TetherElement.
	///
	/// ## Doubly Linked List structure
	///
	/// The Tether is simulated using doubly linked list. This class hold a pointer to the
	/// head and the tail TetherElement accessible through Tether::Head() and Tether::Tail().
    ///
    /// ## Example
	///
	/// Here is a basic example of Tether use. It instanciate a Tether with some parameters,
	/// and show how to access these parameters through methods.
    ///
    /// \snippet examples/TetherExample.cpp example
	class Tether {
		/// \brief Constructor, Tether with length and a number of TetherElements
		///
		/// \param[in] length  The length of the Tether.
		/// \param[in] n  The number of TetherElement used to simulate the Tether.
		public: Tether(std::double_t length, std::size_t n);

		/// \brief Constructor, Tether with length, number of TetherElements and extremities positions
		///
		/// \param[in] length  The length of the Tether.
		/// \param[in] n  The number of TetherElement used to simulate the Tether.
		/// \param[in] Xhead  The initial state of the head TetherElement.
		/// \param[in] Xtail  The initial state of the tail TetherElement.
		public: Tether(std::double_t length, std::size_t n, ignition::math::Vector4d Xhead, ignition::math::Vector4d Xtail);

		/// \brief Destructor
		public: ~Tether() = default;

		/// \brief Tether number of TetherElement
		/// \return The number of TetherElement in the Tether
		public: std::size_t N() const;

		/// \brief Tether length
		/// \return The Tether length
		public: std::double_t Length() const;

		/// \brief Head TetherElement pointer
		/// \return Pointer to the head TetherElement
		public: std::shared_ptr<TetherElement> Head() const;

		/// \brief Tail TetherElement pointer
		/// \return Pointer to the tail TetherElement
		public: std::shared_ptr<TetherElement> Tail() const;

		/// \brief Step method
		///
		/// The method used to compute and update the TetherElement state
		/// with the integration time-step h.
		///
		/// \param[in] h integration time in seconds
		public: void Step(std::double_t h);

		/// \brief The number of the TetherElement
		private: std::size_t m_n;

		/// \brief The length of the Tether
		private: std::double_t m_length;

		/// \brief Pointer to the head TetherElement
		private: std::shared_ptr<TetherElement> m_head;

		/// \brief Pointer to the next TetherElement
		private: std::shared_ptr<TetherElement> m_tail;
	};
};