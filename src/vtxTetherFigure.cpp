#include "tether/vtxTetherFigure.hpp"

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
#include <vtkGlyph3D.h>


namespace tether {

    vtxTetherFigure::vtxTetherFigure(std::shared_ptr<Tether> tether) {
        // Tether pointer storage
        m_tether = tether;

        // Creating a render window
        m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

        // Adding an interactor
        m_renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        m_renderWindowInteractor->SetRenderWindow(m_renderWindow);

        // Creating a color solver
        vtkSmartPointer<vtkNamedColors> m_colors = vtkSmartPointer<vtkNamedColors>::New();

        // Adding a renderer
        m_renderer = vtkSmartPointer<vtkRenderer>::New();
        m_renderer->SetBackground(m_colors->GetColor3d("blue_light").GetData());
        m_renderWindow->AddRenderer(m_renderer);

        // Render a sphere for each TetherElements
        m_points = vtkSmartPointer<vtkPoints>::New();
        // as many points as you like
        std::shared_ptr<TetherElement> tether_element = m_tether->Head();
        for (std::size_t i = 0; i < m_tether->N(); i++) {
            m_points->InsertNextPoint(tether_element->X(), tether_element->Y(), tether_element->Z());
            tether_element = tether_element->Next();
        }

        m_polydata = vtkSmartPointer<vtkPolyData>::New();
        m_polydata->SetPoints(m_points);

        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        sphereSource->SetRadius(0.1);
        // sphereSource->SetPhiResolution(100);
        // sphereSource->SetThetaResolution(100);


        vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
        glyph3D->OrientOff(); // disable orientation
        glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
        glyph3D->SetInputData(m_polydata);
        glyph3D->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(glyph3D->GetOutputPort());
        mapper->ScalarVisibilityOff(); // use color from actor

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->GetProperty()->SetColor(m_colors->GetColor3d("cadmium_lemon").GetData());
        actor->SetMapper(mapper);

        mapper->Update();

        m_renderer->AddActor(actor);
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

    void vtxTetherFigure::Show() {
        m_points->Reset();
        std::shared_ptr<TetherElement> tether_element = m_tether->Head();
        for (std::size_t i = 0; i < m_tether->N(); i++) {
            m_points->InsertNextPoint(tether_element->X(), tether_element->Y(), tether_element->Z());
            tether_element = tether_element->Next();
        }
        m_polydata->Modified();
        m_renderWindow->Render();
        m_renderWindowInteractor->Render();
    }

    void vtxTetherFigure::StartInteractor() {
        m_renderWindowInteractor->Start();
    }
}
