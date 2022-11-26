#include "menu.h"

const char* player_models_type[] {
	"regular",
	"flat"
};

namespace menu {
	void render() {
		if (!m_opened)
			return;

		ImGui::Begin("csgo sdk");

		ImGui::Checkbox("bhop", &cfg->m_move.m_bhop);

		ImGui::Combo("player models type", &cfg->m_models.m_player_models_type, player_models_type, ARRAYSIZE(player_models_type));

		ImGui::Checkbox("player models chams", &cfg->m_models.m_player_models);
		ImGui::ColorEdit4("player models chams color", cfg->m_models.m_player_models_clr);

		ImGui::Checkbox("player models chams occluded", &cfg->m_models.m_player_models_occluded);
		ImGui::ColorEdit4("player models chams occluded color", cfg->m_models.m_player_models_occluded_clr);

		ImGui::End();
	}

	void init() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(input::m_hwnd);
		ImGui_ImplDX9_Init(interfaces::m_d3d_device);

		ImGui::GetStyle().WindowMinSize = ImVec2(500, 500);

		auto& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	}

	void undo() {
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}
