#include "tether/vtkTetherFigure.hpp"

#include <vtkAnimationCue.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkAnimationScene.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkGlyph3D.h>


using namespace tether;

vtkStandardNewMacro(vtkCustomAnimationCue);

int main(int argc, char *argv[]) {

    std::shared_ptr<Tether> t = std::make_shared<Tether>(10, 100);

    // Creating a color solver
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    // Creating a render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    // Adding a renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(colors->GetColor3d("blue_light").GetData());
    renderWindow->SetMultiSamples(0);
    renderWindow->AddRenderer(renderer);

    // Creating a sphere source 
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(0.1);
    sphereSource->SetPhiResolution(50);
    sphereSource->SetThetaResolution(50);

    // Creating a point vector to hold TetherElement centers
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    // Render a sphere for each TetherElements
    std::shared_ptr<TetherElement> tether_element = t->Head();
    for (std::size_t i = 0; i < t->N(); i++) {
        points->InsertNextPoint(tether_element->X(), tether_element->Y(), tether_element->Z());
        tether_element = tether_element->Next();
    }
    
    // Creating a polydata
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    // Creating a glych
    vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
    glyph3D->OrientOff();
    glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
    glyph3D->SetInputData(polydata);
    glyph3D->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(glyph3D->GetOutputPort());
    mapper->ScalarVisibilityOff(); // use color from actor

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    // actor->GetProperty()->SetColor(tether_element_colors->GetColor3d("cadmium_lemon").GetData());
    actor->SetMapper(mapper);

    mapper->Update();

    renderer->AddActor(actor);


    // Create an Animation Scene
    vtkSmartPointer<vtkAnimationScene> scene = vtkSmartPointer<vtkAnimationScene>::New();
    scene->SetModeToSequence();
    scene->SetFrameRate(30);
    scene->SetStartTime(0);
    scene->SetEndTime(1);

    // Create an Animation Cue to animate the camera.
    vtkSmartPointer<vtkCustomAnimationCue> cue1 = vtkSmartPointer<vtkCustomAnimationCue>::New();
    cue1->m_polydata = polydata;
    cue1->m_points = points;
    cue1->m_tether = t;
    cue1->m_renderWindow = renderWindow;
    cue1->SetTimeModeToRelative();
    cue1->SetStartTime(0);
    cue1->SetEndTime(1.0);
    scene->AddCue(cue1);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    scene->Play();
    scene->Stop();

    renderWindowInteractor->Start();

    return 0;
}