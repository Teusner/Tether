#include "CtcTether.hpp"
#include <ibex.h>
#include "vibes.hpp"

using namespace tether;

int main(int, char*[]) {

    // Creating a Tether
    std::double_t length = 10;
    std::size_t n = 100;
    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);
    
    // Creating a CtcTether
    tether::CtcTether ctc_tether;
    ctc_tether.AddTether(t);

    // Creating a box containing double infinity
    ibex::IntervalVector x(2, ibex::Interval::ALL_REALS);

    // Contracting the box using the Tether contractor
    ctc_tether.contract(x);

    // Drawing ellipse and bounding box using VIBes Viewer
    vibes::beginDrawing();

    vibes::newFigure("Tether Bounding Box");

    std::double_t a = t->Length() / 2.;
    std::double_t c = (t->Head()->Position() - t->Tail()->Position()).norm() / 2.;
    std::double_t b = std::sqrt(std::pow(a, 2) - std::pow(c, 2));
    std::double_t theta = std::atan2(b, c);
    Eigen::Vector3d center = (t->Tail()->Position() + t->Head()->Position()) / 2.;

    vibes::drawEllipse(center[0], center[2], a, b, theta, "#0074A0[#0074A077]");

    std::vector<std::vector<double>> V;
    std::shared_ptr<TetherElement> tether_element = t->Head();
    while (tether_element != t->Tail()) {
        std::vector<double> v{tether_element->Position()[0], tether_element->Position()[2]};
        V.push_back(v);
        tether_element = tether_element->Next();
    }
    std::vector<double> v{tether_element->Position()[0], tether_element->Position()[2]};
    V.push_back(v);
    vibes::drawLine(V);

    vibes::drawBox(x, "#A02400[]");
    vibes::endDrawing();

    return EXIT_SUCCESS;
}