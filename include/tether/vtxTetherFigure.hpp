#pragma once

#include "tether/Tether.hpp"

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

namespace tether {

	/// \class RenderableTether tether/RenderableTether.hpp
    /// \brief Representing Tether using VTK
	class vtxTetherFigure {

		/// \brief Default constructor
		public: vtxTetherFigure(std::shared_ptr<Tether> tether);

		/// \brief Show the Tether
		/// The method render the Tether using VTK
		public: void Show();

		public: void StartInteractor();


		private: std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkSphereSource>> m_tether_element_sphere_source;
		private: std::map<std::shared_ptr<TetherElement>, vtkSmartPointer<vtkActor>> m_link_actor;

		private: std::shared_ptr<Tether> m_tether;

		private: vtkSmartPointer<vtkRenderer> m_renderer;
        private: vtkSmartPointer<vtkRenderWindow> m_renderWindow;
        private: vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor;
		private: vtkSmartPointer<vtkNamedColors> m_colors;
		private: vtkSmartPointer<vtkPolyData> m_polydata;
		private: vtkSmartPointer<vtkPoints> m_points;
    };
};