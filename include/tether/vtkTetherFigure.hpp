#pragma once

#include "tether/Tether.hpp"
#include "tether/TetherElement.hpp"

#include <map>

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkAnimationCue.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkAnimationScene.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkCamera.h>


namespace tether {

	class vtkCustomAnimationCue: public vtkAnimationCue {
		public:
			static vtkCustomAnimationCue* New();
			// vtkTypeRevisionMacro(vtkCustomAnimationCue, vtkAnimationCue);
			std::shared_ptr<Tether> m_tether;

			vtkSmartPointer<vtkPoints> m_points;
			vtkSmartPointer<vtkLineSource> m_lineSource;
			vtkSmartPointer<vtkRenderWindow> m_renderWindow;

		protected:
			virtual void TickInternal(double currenttime, double deltatime, double clocktime) {
				// Updating Tether
				m_tether->Step(deltatime);

				// Putting TetherElement center in m_points
				m_points->Reset();
				std::shared_ptr<TetherElement> tether_element = m_tether->Head();
				for (std::size_t i = 0; i < m_tether->N(); i++) {
					m_points->InsertNextPoint(tether_element->X(), tether_element->Y(), tether_element->Z());
					tether_element = tether_element->Next();
				}

				m_lineSource->Modified();
        		m_renderWindow->Render();
			}
	};

	// vtkStandardNewMacro(vtkCustomAnimationCue);
	// vtkCxxRevisionMacro(vtkCustomAnimationCue, "$Revision$");

	/// \class RenderableTether tether/RenderableTether.hpp
    /// \brief Representing Tether using VTK
	class vtkTetherFigure {

		/// \brief Default constructor
		public: vtkTetherFigure(std::shared_ptr<Tether> tether);

		/// \brief Show the Tether
		/// The method render the Tether using VTK
		public: void Show();



		private: std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkSphereSource>> m_tether_element_sphere_source;
		private: std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkActor>> m_link_actor;

		private: std::shared_ptr<Tether> m_tether;

        private: vtkSmartPointer<vtkRenderWindow> m_renderWindow;
		private: vtkSmartPointer<vtkRenderer> m_renderer;
        private: vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor;
		private: vtkSmartPointer<vtkNamedColors> m_colors;
		private: vtkSmartPointer<vtkLineSource> m_lineSource;
		private: vtkSmartPointer<vtkTubeFilter> m_tubeFilter;
		private: vtkSmartPointer<vtkSphereSource> m_sphereSource;
		private: vtkSmartPointer<vtkPolyDataMapper> m_mapper;
		private: vtkSmartPointer<vtkPoints> m_points;
		private: vtkSmartPointer<vtkActor> m_actor;
		private: vtkSmartPointer<vtkAnimationScene> m_scene;
		private: vtkSmartPointer<vtkCustomAnimationCue> m_cue1;
		private: vtkSmartPointer<vtkCamera> m_camera;
    };
};