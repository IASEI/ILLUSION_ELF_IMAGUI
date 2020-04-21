#include "DimmensionWorldConsole.h"
#include "PurpleDreamElf.h"
#include "PQEControlGUI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
class IllusionElfImGui :public DimmensionWorldConsole
{
public:
	IllusionElfImGui();
	~IllusionElfImGui();

	void Init()
	{
		glEnable(GL_DEPTH_TEST);
		id=PDE::TextureFromFile("back.jpg");
	}

	void RenderBasis()
	{
	}

	void RenderImgUI()
	{
		ImGui::Begin("root");
		ImGuiWindow *root = ImGui::FindWindowByName("root");
		root->Pos = ImVec2(0.0f,0.0f);
		root->Size = ImVec2(mScreenWidth, mScreenHeight);
		//ImGui::Image(ImTextureID(id),ImVec2(mScreenWidth, mScreenHeight));
		mCGUI.Render();
		ImGui::End();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0,0, 0,0));
		ImGui::Begin("root1");
		ImGuiWindow *root1 = ImGui::FindWindowByName("root1");
		root1->Pos = ImVec2(-0.0f, 0.0f);
		root1->Size = ImVec2(mScreenWidth, mScreenHeight);
		mCGUI.pageone();
		ImGui::End();
		ImGui::PopStyleColor();
	}

private:
	PQE::PQEControlGUI mCGUI;
	unsigned int id;
};