#include "tether/Tether.hpp"
#include "tether/vtkTetherFigure.hpp"

#include <chrono>
#include <thread>

using namespace tether;

vtkStandardNewMacro(vtkCustomAnimationCue);

int main(int, char*[]) {
    std::double_t length = 10;
    std::size_t n = 100;

    std::shared_ptr<tether::Tether> t = std::make_shared<Tether>(length, n);
    
    tether::vtkTetherFigure Tfigure(t);
    Tfigure.Show();

    return EXIT_SUCCESS;
}