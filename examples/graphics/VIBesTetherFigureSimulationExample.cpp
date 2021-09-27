#include "VIBesTetherFigure.hpp"
#include "vibes.hpp"

#include <chrono>
#include <ibex.h>
#include <map>
#include <string>
#include <thread>

using namespace tether;


int main(int, char*[]) {
    // Creating a Tether
    std::double_t length = 10;
    std::size_t n = 100;
    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);
    
    // Drawing ellipse and bounding box using VIBes Viewer
    vibes::beginDrawing();

    tether::VIBesTetherFigure fig(t);
    for (std::size_t i = 0; i < 5000; i++) {
        t->Step(0.01);
        vibes::clearFigure();
        vibes::axisLimits(-2.5,7.5, -7.5, 2.5);
        vibes::setFigureProperties(vibesParams("x", 100, "y", 100, "width", 600, "height", 600));
        fig.ShowTether();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    vibes::endDrawing();

    return EXIT_SUCCESS;
}