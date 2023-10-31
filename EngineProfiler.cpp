#include "EngineProfiler.h"

EngineProfiler::EngineProfiler(std::string name) : AUIScreen(name)
{
}

EngineProfiler::~EngineProfiler()
{
}

void EngineProfiler::drawUI()
{
	ImGui::Begin("Engine Profiler");

	ImGui::Text("Application AVG %000.00f ms/frame (%000.0f of FPS)", EngineTime::getDeltaTime() * 1000.0f, 1.0f / EngineTime::getDeltaTime());

	ImGui::End();
}
