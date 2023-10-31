#include "InspectorWindow.h"
#include "MathUtils.h"

InspectorWindow::InspectorWindow(std::string name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	ImGui::Begin("Inspector Window");

	AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

	if(selectedObject == nullptr)
	{
		ImGui::Text("No object selected. Select an object from the scene.");
	}
	else
	{
		std::string temp = "selectedObject" + selectedObject->getName();
		ImGui::Text(temp.c_str());

		bool isActive = selectedObject->getActive();

		if (ImGui::Checkbox("Enabled", &isActive))
		{
			selectedObject->setActive(isActive);
		}

		Vector3D pos = selectedObject->getLocalPosition();
		Vector3D rot = selectedObject->getLocalRotation();
		Vector3D sca = selectedObject->getLocalScale();

		float position[] = { pos.x, pos.y, pos.z };
		float rotation[] = { MathUtils::toDegrees(rot.x), MathUtils::toDegrees(rot.y), MathUtils::toDegrees(rot.z) };
		float scale[] = { sca.x, sca.y, sca.z };

		ImGui::DragFloat3("Position", position, 0.05f);
		ImGui::DragFloat3("Rotation", rotation, 0.05f);
		ImGui::DragFloat3("Scale", scale, 0.05f);

		selectedObject->setPosition(position[0], position[1], position[2]);
		selectedObject->setRotation(MathUtils::toRadians(rotation[0]), MathUtils::toRadians(rotation[1]), MathUtils::toRadians(rotation[2]));
		selectedObject->setScale(scale[0], scale[1], scale[2]);

	}


	ImGui::End();
}
