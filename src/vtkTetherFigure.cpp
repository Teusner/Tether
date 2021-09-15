#include "tether/vtkTetherFigure.hpp"

#include <string>

#include <vtkSphereSource.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkMath.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkCamera.h>


namespace tether {

    vtkTetherFigure::vtkTetherFigure(std::shared_ptr<Tether> tether) {
        // Tether pointer storage
        m_tether = tether;

        // Creating a color solver
        m_colors = vtkSmartPointer<vtkNamedColors>::New();

        // Creating a render window
        m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

        // Adding a renderer
        m_renderer = vtkSmartPointer<vtkRenderer>::New();
        m_renderer->SetBackground(m_colors->GetColor3d("blue_light").GetData());
        m_renderWindow->SetMultiSamples(0);
        m_renderWindow->AddRenderer(m_renderer);

        // Creating a sphere source 
        m_sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        m_sphereSource->SetRadius(0.1);
        m_sphereSource->SetPhiResolution(50);
        m_sphereSource->SetThetaResolution(50);

        // Creating a point vector to hold TetherElement centers
        m_points = vtkSmartPointer<vtkPoints>::New();

        // Render a sphere for each TetherElements
        std::shared_ptr<TetherElement> tether_element = m_tether->Head();
        for (std::size_t i = 0; i < m_tether->N(); i++) {
            m_points->InsertNextPoint(tether_element->X(), tether_element->Y(), tether_element->Z());
            tether_element = tether_element->Next();
        }

        // Creating LineSource
        m_lineSource = vtkSmartPointer<vtkLineSource>::New();
        m_lineSource->SetPoints(m_points);

        // Creating TubeFilter
        m_tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
        m_tubeFilter->SetInputConnection(m_lineSource->GetOutputPort());
        m_tubeFilter->SetRadius(0.02); // default is .5
        m_tubeFilter->SetNumberOfSides(50);
        m_tubeFilter->Update();

        // Creating a mapper
        m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        m_mapper->SetInputConnection(m_tubeFilter->GetOutputPort());
        
        m_actor = vtkSmartPointer<vtkActor>::New();
        m_actor->GetProperty()->SetColor(m_colors->GetColor3d("cadmium_lemon").GetData());
        m_actor->SetMapper(m_mapper);
        m_mapper->Update();
        m_renderer->AddActor(m_actor);

        m_camera = vtkSmartPointer<vtkCamera>::New();
        Eigen::Vector3d mid = 0.5 * (tether->Head()->Position() + tether->Tail()->Position());
        m_camera->SetPosition(mid[0], mid[1], mid[2] + 25);
        m_camera->SetFocalPoint(mid[0], mid[1], mid[2]);

        m_renderer->SetActiveCamera(m_camera);
    }

    // void vtxTetherFigure::AddTether() {
    //     m_tether = tether;
        
        // Showing sphere at each TetherElement
        // std::shared_ptr<TetherElement> tether_element = tether->Head();
        // for (std::size_t i = 0; i < tether->N(); i++) {
        //     std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkSphereSource>>::iterator lb = m_tether_element_sphere_source.lower_bound(tether_element);

        //     if(lb != m_tether_element_sphere_source.end() && !(m_tether_element_sphere_source.key_comp()(tether_element, lb->first))) {
        //         lb->second->SetCenter(tether_element->x(), tether_element->y(), tether_element->z());
        //         lb->second->Update();
        //     }
        //     else {
        //         // Inserting <TetherElement, vtkActor> into the map
        //         vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        //         sphereSource->SetCenter(tether_element->x(), tether_element->y(), tether_element->z());
        //         sphereSource->SetRadius(0.1);
        //         sphereSource->SetPhiResolution(100);
        //         sphereSource->SetThetaResolution(100);

        //         vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        //         sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

        //         vtkSmartPointer<vtkNamedColors> sphereColor = vtkSmartPointer<vtkNamedColors>::New();

        //         vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
        //         sphereActor->SetMapper(sphereMapper);

        //         std::string color = "cadmium_lemon";
        //         if (tether_element == tether->Head()) {
        //             color = "DarkGreen";
        //         }
        //         else if (tether_element == tether->Tail()) {
        //             color = "DarkRed";
        //         }
             
        //         sphereActor->GetProperty()->SetColor(sphereColor->GetColor3d(color).GetData());
        //         m_tether_element_sphere_source.insert(lb, std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkSphereSource>>::value_type(tether_element, sphereSource));

        //         m_renderer->AddActor(sphereActor);
        //     }
        //     tether_element = tether_element->Next();
        // }


        /////////
        



        // Showing cylinders between each TetherElement
    //     tether_element = tether->Head();
    //     while (tether_element != tether->Tail()) {
    //         std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkActor>>::iterator lb = m_link_actor.lower_bound(tether_element);

    //         if(lb != m_link_actor.end() && !(m_link_actor.key_comp()(tether_element, lb->first))) {
    //             // key already exists
    //             // update lb->second if you care to
    //         }
    //         else {
    //             // Inserting <TetherElement, vtkActor> into the map
    //             vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
    //             cylinderSource->SetResolution(100);

    //             double startPoint[3] = {tether_element->x(), tether_element->y(), tether_element->z()};
    //             double endPoint[3] = {tether_element->Next()->x(), tether_element->Next()->y(), tether_element->Next()->z()};

    //             // Compute a basis
    //             double normalizedX[3];
    //             double normalizedY[3];
    //             double normalizedZ[3];

    //             // The X axis is a vector from start to end
    //             vtkMath::Subtract(endPoint, startPoint, normalizedX);
    //             double length = vtkMath::Norm(normalizedX);
    //             vtkMath::Normalize(normalizedX);

    //             // The Z axis is an arbitrary vector cross X
    //             double arbitrary[3];
    //             vtkSmartPointer<vtkMinimalStandardRandomSequence> rng = vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
    //             for (auto i = 0; i < 3; ++i)
    //             {
    //             	rng->Next();
    //             	arbitrary[i] = rng->GetRangeValue(-10, 10);
    //             }
    //             vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
    //             vtkMath::Normalize(normalizedZ);

    //             // The Y axis is Z cross X
    //             vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
    //             vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();

    //             // Create the direction cosine matrix
    //             matrix->Identity();
    //             for (unsigned int i = 0; i < 3; i++)
    //             {
    //             	matrix->SetElement(i, 0, normalizedX[i]);
    //             	matrix->SetElement(i, 1, normalizedY[i]);
    //             	matrix->SetElement(i, 2, normalizedZ[i]);
    //             }

    //             // Apply the transforms
    //             vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    //             transform->Translate(startPoint);   // translate to starting point
    //             transform->Concatenate(matrix);     // apply direction cosines
    //             transform->RotateZ(-90.0);          // align cylinder to x axis
    //             transform->Scale(0.2, length, 0.2); // scale along the height vector
    //             transform->Translate(0, .5, 0);     // translate to start of cylinder

    //             // Transform the polydata
    //             vtkSmartPointer<vtkTransformPolyDataFilter> transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    //             transformPD->SetTransform(transform);
    //             transformPD->SetInputConnection(cylinderSource->GetOutputPort());

    //             // Create a mapper and actor for the cylinder
    //             vtkSmartPointer<vtkPolyDataMapper> mapperCylinder = vtkSmartPointer<vtkPolyDataMapper>::New();
    //             vtkSmartPointer<vtkActor> actorCylinder = vtkSmartPointer<vtkActor>::New();

    //             vtkSmartPointer<vtkNamedColors> cylinderColor = vtkSmartPointer<vtkNamedColors>::New();

    //             mapperCylinder->SetInputConnection(transformPD->GetOutputPort());
    //             actorCylinder->SetMapper(mapperCylinder);
    //             actorCylinder->GetProperty()->SetColor(cylinderColor->GetColor3d("cadmium_lemon").GetData());
                
    //             m_link_actor.insert(lb, std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkActor>>::value_type(tether_element, actorCylinder));
    //             m_renderer->AddActor(actorCylinder);
    //         }
    //         tether_element = tether_element->Next();
    //     }
    // }

    void vtkTetherFigure::Show() {
        // Create an Animation Scene
        m_scene = vtkSmartPointer<vtkAnimationScene>::New();
        m_scene->SetModeToRealTime();
        m_scene->SetFrameRate(30);
        m_scene->SetStartTime(0);
        m_scene->SetEndTime(7);

        // Create an Animation Cue to animate the camera.
        m_cue1 = vtkSmartPointer<vtkCustomAnimationCue>::New();
        m_cue1->m_lineSource = m_lineSource;
        m_cue1->m_points = m_points;
        m_cue1->m_tether = m_tether;
        m_cue1->m_renderWindow = m_renderWindow;
        m_cue1->SetTimeModeToNormalized();
        m_cue1->SetStartTime(0);
        m_cue1->SetEndTime(1);
        m_scene->AddCue(m_cue1);

        m_renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        m_renderWindowInteractor->SetRenderWindow(m_renderWindow);

        m_scene->Play();
        m_scene->Stop();

        m_renderWindowInteractor->Start();
    }
}
