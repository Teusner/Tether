#include "tether/Tether.hpp"
#include "tether/vtxTetherFigure.hpp"

#include <chrono>
#include <thread>

using namespace tether;

int main(int, char*[]) {
    using namespace std::chrono_literals;

    std::double_t length = 10;
    std::size_t n = 100;

    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);

    tether::vtxTetherFigure Tfigure(t);
    Tfigure.Show();

    for (size_t i = 0 ; i < 100; i++) {
        t->Step(0.001);
        Tfigure.Show();
        std::this_thread::sleep_for(1ms);
    }
    Tfigure.StartInteractor();

    return EXIT_SUCCESS;
}