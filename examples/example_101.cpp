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

    std::cout << "Computed length : " << t->ComputeLength() << std::endl;
    std::cout << "First link length : " << t->Head()->NextLength() << std::endl;
    // std::cout << "Gravity : " << t->Head()->Fg() << std::endl;
    // std::cout << "Buoyancy : " << t->Head()->Fb() << std::endl;
    // std::cout << "Drag : " << t->Head()->Ff() << std::endl;
    std::cout << "Ft_prev : " << t->Head()->Ft_prev() << std::endl;
    std::cout << "Ft_next : " << t->Head()->Ft_next() << std::endl;

    return EXIT_SUCCESS;
}