#include "Tether.hpp"

#include <cmath>
#include <cstddef>
#include <memory>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

#include <Eigen/Dense>

#include <iostream>


namespace tether {
	Tether::Tether(std::double_t length, std::size_t n, Eigen::Vector3d Xhead, Eigen::Vector3d Xtail) {
		m_length = length;
		m_n = n;

		// Temporary variables
		double mass = 1;
		double volume = 0.001;
		double l = length / (n-1);

		m_head = std::make_shared<TetherElement>(mass, volume, l, Xhead);
		m_tail = std::make_shared<TetherElement>(mass, volume, l, Xtail);

		SolveCatenary();

		std::shared_ptr<TetherElement> previous_tether_element = m_head;
		std::shared_ptr<TetherElement> next_tether_element;
		for (std::size_t i = 1; i < n-1; i++) {
			double r = c1 * std::asinh(i * m_length / (m_n * c1) + std::sinh(c2/c1)) - c2;
			double angle = std::atan2(Xtail[1] - Xhead[1], Xtail[0] - Xhead[0]);
			Eigen::Vector3d X(r * std::cos(angle) + Xhead[0], r * std::sin(angle) + Xhead[1], c1 * std::cosh((r + c2) / c1) + c3);
			next_tether_element = std::make_shared<TetherElement>(mass, volume, l, X);
			previous_tether_element->SetNext(next_tether_element);
			next_tether_element->SetPrevious(previous_tether_element);
			previous_tether_element = next_tether_element;
		}
		next_tether_element->SetNext(m_tail);
		m_tail->SetPrevious(next_tether_element);
	}

	Tether::~Tether() {
		gsl_multiroot_fsolver_free(s);
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

	/// Solution seems to be here : https://stackoverflow.com/questions/13074756/how-to-avoid-static-member-function-when-using-gsl-with-c/18181494#18181494
	/// Using lambdas to give parameters : https://stackoverflow.com/questions/19450198/calling-gsl-function-inside-a-class-in-a-shared-library
	/// Using opaque ... : https://stackoverflow.com/questions/47050842/c-class-member-function-to-gsl-ode-solver

	template< typename T >
		class gsl_multiroot_function_pp : public gsl_multiroot_function {
			public:
				gsl_multiroot_function_pp(const T& func) : _func(func) {
					f = &gsl_multiroot_function_pp::invoke;
					n = 3;
					params = this;
				}
			private:
				const T& _func;
				static int invoke(const gsl_vector *x, void *params, gsl_vector *f) {
					return static_cast<gsl_multiroot_function_pp*>(params)->_func(x, params, f);
				}
	};

	int Tether::GSLCatenary(const gsl_vector *p, void *params, gsl_vector *f) {
		const double c1 = gsl_vector_get(p, 0);
		const double c2 = gsl_vector_get(p, 1);
		const double c3 = gsl_vector_get(p, 2);

		const double rmax = std::sqrt(std::pow(Tail()->X() - Head()->X(), 2) + std::pow(Tail()->Y() - Head()->Y(), 2));
		const double eqn1 = c1 * (std::sinh((rmax + c2) / c1) - std::sinh(c2 / c1)) - m_length;
		const double eqn2 = c1 * std::cosh(c2 / c1) + c3 - Head()->Z();
		const double eqn3 = c1 * std::cosh((rmax + c2) / c1) + c3 - Tail()->Z();

		gsl_vector_set(f, 0, eqn1);
		gsl_vector_set(f, 1, eqn2);
		gsl_vector_set(f, 2, eqn3);

		return GSL_SUCCESS;
	}

	void Tether::SolveCatenary() {
		const std::size_t n = 3;

		gsl_vector *x = gsl_vector_alloc(n);
		gsl_vector_set(x, 0, 1);
		gsl_vector_set(x, 1, - (Head()->X() + Tail()->X()) / 2);
		gsl_vector_set(x, 2, ((Head()->Z() + Tail()->Z()) / 2 - m_length)/2);

		auto ptr = [=](const gsl_vector *x, void *params, gsl_vector *f)->int{return this->GSLCatenary(x, params, f);};
		gsl_multiroot_function_pp<decltype(ptr)> Fp(ptr);
		gsl_multiroot_function *F = static_cast<gsl_multiroot_function*>(&Fp); 

		int status;
		std::size_t iter = 0;
		s = gsl_multiroot_fsolver_alloc(gsl_multiroot_fsolver_hybrids, n);
		gsl_multiroot_fsolver_set(s, F, x);
		do {
			iter++;
			status = gsl_multiroot_fsolver_iterate(s);
			if (status)   /* check if solver is stuck */
				break;
			status = gsl_multiroot_test_residual(s->f, 1e-7);
		}
		while (status == GSL_CONTINUE && iter < 1000);

		c1 = gsl_vector_get(s->x, 0);
		c2 = gsl_vector_get(s->x, 1);
		c3 = gsl_vector_get(s->x, 2);
		gsl_vector_free(x);
	}
}