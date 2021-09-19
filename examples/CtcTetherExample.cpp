#include "tether/CtcTether.hpp"
#include <ibex.h>
#include <vibes.h>
#include <codac.h>

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

    codac::VIBesFig fig("Tether Bounding Box");
    fig.set_properties(100, 100, 400, 200);
    fig.axis_limits(ibex::IntervalVector({{-5,5},{-5,5}}));
    Eigen::Vector3d x = (m_tether->Tail()->Position() + m_tether->Head()->Position()) / 2.);
    fig.drawEllipse(x[0], x[2], );
    fig.draw_box(x, "#A02400[#A0240077]");
    vibes::endDrawing();

    return EXIT_SUCCESS;
}