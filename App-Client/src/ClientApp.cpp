#include "Walnut/ApplicationGUI.h"
#include "Walnut/EntryPoint.h"

#include "ClientLayer.h"

const static uint64_t s_BufferSize = 1024;
static uint8_t* s_Buffer = new uint8_t[s_BufferSize];

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Chat Client";
	spec.IconPath = "res/Walnut-Icon.png";
	spec.CustomTitlebar = true;
	spec.CenterWindow = true;

	Walnut::Application* app = new Walnut::Application(spec);
	std::shared_ptr<ClientLayer> clientLayer = std::make_shared<ClientLayer>();
	app->PushLayer(clientLayer);
	app->SetMenubarCallback([app, clientLayer]()
	{
		//菜单按钮
		if (ImGui::BeginMenu("File"))
		{
			//子按钮
			if (ImGui::MenuItem("Disconnect"))
				clientLayer->OnDisconnectButton();
			//退出
			if (ImGui::MenuItem("Exit"))
				app->Close();

			ImGui::EndMenu();
		}
	});
	return app;
}