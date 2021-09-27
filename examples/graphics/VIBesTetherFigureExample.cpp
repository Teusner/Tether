#include "VIBesTetherFigure.hpp"
#include "vibes.hpp"

#include <map>
#include <string>
#include <ibex.h>

using namespace tether;


int main(int, char*[]) {
    // Creating a Tether
    std::double_t length = 10;
    std::size_t n = 100;
    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);
    
    // Drawing ellipse and bounding box using VIBes Viewer
    vibes::beginDrawing();

    tether::VIBesTetherFigure fig(t);
    // fig.ShowEllipse();
    fig.ShowTether();
    vibes::axisLimits(-2.5,7.5, -7.5, 2.5);
    vibes::setFigureProperties(vibesParams("x", 100, "y", 100, "width", 600, "height", 600));
    vibes::endDrawing();

    return EXIT_SUCCESS;
}