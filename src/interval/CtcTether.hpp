#include "Tether.hpp"
#include <ibex.h>
#include <memory>


namespace tether {
    class CtcTether : public ibex::Ctc {

        public: CtcTether() : ibex::Ctc(2) {};

        public: void AddTether(std::shared_ptr<Tether> tether);

        public: void contract(ibex::IntervalVector& box);

        private: std::shared_ptr<Tether> m_tether;

        private: std::double_t m_a;
        private: std::double_t m_b;
        private: std::double_t m_c;
        private: std::double_t m_theta;
        private: std::double_t m_alpha;
        private: std::double_t m_r;
        private: ibex::IntervalVector m_mid;
    };
}; // namespace tether