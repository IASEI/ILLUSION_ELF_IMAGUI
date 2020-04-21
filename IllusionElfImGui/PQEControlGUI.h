#ifndef __PQECONTROLGUI_H__
#define __PQECONTROLGUI_H__

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"

#include <queue>

namespace PQE
{
	class PQEControlGUI
	{
	public:
		PQEControlGUI();
		void Render();
		void pageone();

		void WindowRender();
		void WindowPerformance();
		void WindowFPS();
		void WindowRenderAuxiliary();
		void WindowModel();
		void WindowShader();
		void WindowLeftList();

		~PQEControlGUI();
	private:
		std::queue<float> values;
		ImGuiWindow *mMeasure;
		ImGuiWindowFlags mChildFlags;
	};
}
#endif


