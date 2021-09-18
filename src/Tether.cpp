#include "tether/Tether.hpp"

#include <cmath>
#include <cstddef>
#include <memory>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

#include <Eigen/Dense>


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
			X[0] += 0.08;
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

	std::double_t Tether::ComputeLength() const {
		std::double_t length = 0;
		std::shared_ptr<TetherElement> tether_element = m_head;
		while (tether_element != m_tail) {
			length += tether_element->NextLength();
			tether_element = tether_element->Next();
		}
		return length;
	}
	
	std::shared_ptr<TetherElement> Tether::Head() const {
		return m_head;
	}

	std::shared_ptr<TetherElement> Tether::Tail() const {
		return m_tail;
	}

	void Tether::Step(const std::double_t h) {
		std::shared_ptr<TetherElement> tether_element = m_head;
		while (tether_element != m_tail) {
			tether_element->Step(h);
			tether_element = tether_element->Next();
		}
		tether_element->Step(h);
	}

	int Tether::GSLCatenary(const gsl_vector *p, void *params, gsl_vector *f) {
		const double c1 = gsl_vector_get(p, 0);
		const double c2 = gsl_vector_get(p, 1);
		const double c3 = gsl_vector_get(p, 2);

		const double rmax = std::sqrt(std::pow(Tail()->X() - Head()->X(), 2) + std::pow(Tail()->X() - Head()->X(), 2));
		const double eqn1 = c1 * (std::sinh((rmax + c2) / c1) - std::sinh((c2) / c1)) - m_length;
		const double eqn2 = c1 * std::cosh((c2) / c1) + c3 - Head()->Y();
		const double eqn3 = c1 * std::cosh((rmax + c2) / c1) + c3 - Tail()->Y();

		gsl_vector_set(f, 0, eqn1);
		gsl_vector_set(f, 1, eqn2);
		gsl_vector_set(f, 2, eqn3);

		return GSL_SUCCESS;
	}

	// struct rparams {
	// 	double a;
	// };

	// void Tether::SolveCatenary(double &c1, double &c2, double &c3) {
	// 	const gsl_multiroot_fsolver_type *T;
	// 	gsl_multiroot_fsolver *s;

	// 	int status;
	// 	size_t i, iter = 0;

	// 	const size_t n = 3;
	// 	struct rparams p = {1.0};
	// 	gsl_multiroot_function f = {&Tether::GSLCatenary, n, &p};
	// 	gsl_vector *x = gsl_vector_alloc (n);

	// 	gsl_vector_set (x, 0, 1);
	// 	gsl_vector_set (x, 1, - (Head()->X() + Tail()->X()) / 2);
	// 	gsl_vector_set (x, 2, (Head()->Y() + Tail()->Y()) / 2);

	// 	T = gsl_multiroot_fsolver_hybrids;
	// 	s = gsl_multiroot_fsolver_alloc (T, 3);
	// 	gsl_multiroot_fsolver_set (s, &f, x);

	// 	do {
	// 		iter++;
	// 		status = gsl_multiroot_fsolver_iterate (s);
	// 		if (status)   /* check if solver is stuck */
	// 			break;
	// 		status = gsl_multiroot_test_residual (s->f, 1e-7);
	// 	}
	// 	while (status == GSL_CONTINUE && iter < 1000);

	// 	c1 = gsl_vector_get (s->x, 0);
	// 	c2 = gsl_vector_get (s->x, 1);
	// 	c3 = gsl_vector_get (s->x, 2);

	// 	gsl_multiroot_fsolver_free (s);
	// 	gsl_vector_free (x);
	// }
}