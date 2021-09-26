/// \file Tether.hpp
/// Implementation of Tether

#pragma once

#include <cmath>
#include <cstddef>
#include <memory>

#include <Eigen/Dense>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

#include "TetherElement.hpp"

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
    /// \snippet examples/core/TetherExample.cpp example
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
		public: Tether(std::double_t length, std::size_t n, Eigen::Vector3d Xhead, Eigen::Vector3d Xtail);

		/// \brief Destructor
		public: ~Tether();

		/// \brief Tether number of TetherElement
		/// \return The number of TetherElement in the Tether
		public: std::size_t N() const;

		/// \brief Tether length
		/// \return The Tether length
		public: std::double_t Length() const;

		/// \brief Compute the current Tether length
		/// Compute the real Tether length by summing length of links
		/// between each TetherElement from head to tail. The result is
		/// the current Tteher length and could be different of the value
		/// returned by Tether::Length.
		/// \return The computed Tether length
		std::double_t ComputeLength() const;

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
		public: void Step(const std::double_t h);

		/// \brief The number of the TetherElement
		private: std::size_t m_n;

		/// \brief The length of the Tether
		private: std::double_t m_length;

		/// \brief Pointer to the head TetherElement
		private: std::shared_ptr<TetherElement> m_head;

		/// \brief Pointer to the next TetherElement
		private: std::shared_ptr<TetherElement> m_tail;

		private: int GSLCatenary(const gsl_vector *p, void *params, gsl_vector *f);
		private: void SolveCatenary();

		private: gsl_multiroot_fsolver *s;

		private: double c1;
		private: double c2;
		private: double c3;
	};
};