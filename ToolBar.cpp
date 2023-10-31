#include "ToolBar.h"

ToolBar::ToolBar(std::string name) : AUIScreen (name)
{
	
}

ToolBar::~ToolBar()
{
}

void ToolBar::drawUI()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("New");
		ImGui::MenuItem("Save");
		ImGui::MenuItem("Open");
		ImGui::MenuItem("Exit");


		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		
		if (ImGui::MenuItem("Plane"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		
		if(ImGui::MenuItem("Sphere"))
		{}

		if (ImGui::BeginMenu("Light")) {
			ImGui::MenuItem("Create Point Light");
			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}



	ImGui::EndMainMenuBar();

}
