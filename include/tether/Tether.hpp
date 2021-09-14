#pragma once

#include <cmath>
#include <cstddef>
#include <memory>

#include "tether/TetherElement.hpp"

namespace tether {

	/// \class TetherElement TetherElement.hpp tether/TetherElement.hpp
    /// \brief TetherElement to represent a discretized element of tether.
	class Tether {
		/// \brief Default constructor
		public: Tether();

		/// \brief Destructor
		public: ~Tether() = default;

		/// \brief Step method
		///
		/// The method used to compute and update the TetherElement state
		/// with the integration time-step h.
		///
		/// \param[in] h integration time in seconds
		public: void Step(double h);

		/// \brief Tether length getter
		/// \return The Tether length
		public: std::double_t Length();

		public: std::size_t N();

		public: std::shared_ptr<TetherElement> Head();
		public: std::shared_ptr<TetherElement> Tail();

		/// \brief The number of the TetherElement
		private: std::size_t m_n;

		/// \brief The length of the Tether
		private: double m_l;

		/// \brief Pointer to the head TetherElement
		private: std::shared_ptr<TetherElement> m_head;

		/// \brief Pointer to the next TetherElement
		private: std::shared_ptr<TetherElement> m_tail;
	};
};