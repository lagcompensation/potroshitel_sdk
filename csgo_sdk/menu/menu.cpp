#include "menu.h"

namespace menu {
	void render() {
		if (!input::m_opened)
			return;

		ImGui::Begin("csgo sdk");

		/* your menu elements here..... */
		ImGui::Checkbox("bhop", &g_cfg->m_move.m_bhop);

		ImGui::End();
	}

	void init() {
		ImGui::CreateContext();

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