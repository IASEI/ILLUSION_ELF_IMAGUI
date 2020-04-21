#include "PQEControlGUI.h"

namespace PQE
{
	PQEControlGUI::PQEControlGUI():mChildFlags(ImGuiWindowFlags_None | ImGuiWindowFlags_MenuBar)
	{
		for(int i=0;i<90;i++)
			values.push(0);
	}

	PQEControlGUI::~PQEControlGUI()
	{
	}

	void PQEControlGUI::Render()
	{
		float size=ImGui::GetStyle().WindowRounding;
		ImGui::GetStyle().WindowRounding = 0;
		ImGui::Begin("measure");
		mMeasure = ImGui::FindWindowByName("measure");
		ImGui::Text(" pos.x:%f pos.y:%f \n width:%f height:%f", mMeasure->Pos.x, mMeasure->Pos.y, mMeasure->Size.x, mMeasure->Size.y);

		ImGui::End();
		ImGui::GetStyle().WindowRounding = size;
	}

	void PQEControlGUI::WindowRender()
	{
		ImGui::BeginChild("Render", ImVec2(1210, 586), true, mChildFlags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Render"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::EndChild();
	}

	void PQEControlGUI::WindowPerformance()
	{
		ImGui::BeginChild("Performance", ImVec2(1210, 144), true, mChildFlags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Performance"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::EndChild();
	}

	void PQEControlGUI::WindowFPS()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
			{
				ImGui::BeginChild("FPS", ImVec2(613, 254), true, mChildFlags);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("FPS"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
					static float valuesCopy[60] = {};
					static int values_offset = 0;
					static double refresh_time = 0.0;
					if (refresh_time == 0.0)
						refresh_time = ImGui::GetTime();
					static float phase = 0.0f;

					for (int i = 0; i < 59; i++)
					{
						valuesCopy[i] = valuesCopy[i + 1];
					}
					valuesCopy[59] = ImGui::GetIO().Framerate ;
					ImGui::Text("FPS:%f", ImGui::GetIO().Framerate);
					char overlay[32]="";
					ImGui::PlotLines("Lines", valuesCopy, IM_ARRAYSIZE(valuesCopy), values_offset, overlay, 0.0f, 120.0f, ImVec2(613, 200));
				}
				ImGui::EndChild();
			}
			ImGui::PopStyleVar();
		}
		ImGui::PopStyleVar();
	}

	void PQEControlGUI::WindowRenderAuxiliary()
	{
		ImGui::BeginChild("RenderAuxiliary", ImVec2(613, 254), true, mChildFlags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("RenderAuxiliary"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::EndChild();
	}

	void PQEControlGUI::WindowModel()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10,10));
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
			{
				ImGui::BeginChild("model", ImVec2(598, 586), true, mChildFlags);
				{
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("model"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}
					static bool mbool = true;
					ImGui::Checkbox("model", &mbool); ImGui::Separator();
					ImGui::Checkbox("model", &mbool); ImGui::Separator();
					ImGui::Checkbox("model", &mbool); ImGui::Separator();
					ImGui::Checkbox("model", &mbool); ImGui::Separator();
					ImGui::Checkbox("model", &mbool);

				}
				ImGui::EndChild();
			}
			ImGui::PopStyleVar();
		}
		ImGui::PopStyleVar();
	}

	void PQEControlGUI::WindowShader()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
			{
				ImGui::BeginChild("shader", ImVec2(598, 586), true, mChildFlags);
				{
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("shader"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}
					static bool mbool = true;
					ImGui::Checkbox("shader", &mbool); ImGui::Separator();
					ImGui::Checkbox("shader", &mbool); ImGui::Separator();
					ImGui::Checkbox("shader", &mbool); ImGui::Separator();
					ImGui::Checkbox("shader", &mbool); ImGui::Separator();
					ImGui::Checkbox("shader", &mbool);

				}
				ImGui::EndChild();
			}
			ImGui::PopStyleVar();
		}
		ImGui::PopStyleVar();
	}

	void PQEControlGUI::WindowLeftList()
	{
		ImGui::BeginChild("List", ImVec2(45, 1080), true, ImGuiWindowFlags_None);
			ImGui::BeginChild("tiaomu", ImVec2(-1, 50));
			ImGui::EndChild();
		ImGui::EndChild();
	}

	void PQEControlGUI::pageone()
	{
		ImVec2 size = ImGui::GetStyle().ItemInnerSpacing;
		ImGui::GetStyle().WindowPadding= ImVec2(0, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15, 15));
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 0);
		ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, IM_COL32(0, 0, 0, 0));
		WindowLeftList();
		ImGui::SameLine();
			ImGui::BeginChild("content",ImVec2(1875,1080), false, ImGuiWindowFlags_None);
			{
				ImGui::BeginChild("tiaomu1", ImVec2(-1, 50), true, ImGuiWindowFlags_None);
				ImGui::EndChild();

				ImGui::BeginChild("content_1", ImVec2(1212, 1030), false, ImGuiWindowFlags_None);
				{
					ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, IM_COL32(0, 0, 0, 50));
					WindowRender();
					WindowPerformance();
					WindowModel(); ImGui::SameLine();
					WindowShader();
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("content_2", ImVec2(1210, 1030), false, ImGuiWindowFlags_None);
				{
					ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, IM_COL32(0, 0, 0, 50));
					WindowRenderAuxiliary();
					WindowFPS();
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		//ImGui::GetStyle().ItemInnerSpacing = size;
	}
}