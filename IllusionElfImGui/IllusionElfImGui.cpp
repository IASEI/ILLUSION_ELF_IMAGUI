#include "IllusionElfImGui.h"


IllusionElfImGui::IllusionElfImGui()
{
}


IllusionElfImGui::~IllusionElfImGui()
{
}

DimmensionWorldConsole *DimmensionWorldConsole::create(std::string classname)
{
	IllusionElfImGui *t = new IllusionElfImGui();
	return reinterpret_cast<IllusionElfImGui *>(t);
}
