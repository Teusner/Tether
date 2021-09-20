#include "VIBesTetherFigure.hpp"
#include <ibex.h>
#include "vibes.hpp"

using namespace tether;


int main(int, char*[]) {
    // Creating a Tether
    std::double_t length = 10;
    std::size_t n = 100;
    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);
    
    // Drawing ellipse and bounding box using VIBes Viewer
    vibes::beginDrawing();

    tether::VIBesTetherFigure fig(t);

    fig.ShowTether();
    vibes::endDrawing();

    return EXIT_SUCCESS;
}