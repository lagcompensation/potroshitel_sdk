#include "../hooks.h"
#include "../../menu/menu.h"

long __stdcall hooks::ui::present::hook(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region) {
	static const auto original = m_d3d_device->get_original<fn>(ui::present::index);

	IDirect3DVertexDeclaration9* vert_declaration;
	IDirect3DVertexShader9* vert_shader;
	DWORD old_d3drs_colorwriteenable;

	device->GetRenderState(D3DRS_COLORWRITEENABLE, &old_d3drs_colorwriteenable);
	device->GetVertexDeclaration(&vert_declaration);
	device->GetVertexShader(&vert_shader);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu::render();

	ImGui::EndFrame();
	ImGui::Render();

	device->SetRenderState(D3DRS_COLORWRITEENABLE, old_d3drs_colorwriteenable);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	device->SetVertexDeclaration(vert_declaration);
	device->SetVertexShader(vert_shader);

	return original(device, src_rect, dest_rect, dest_wnd_override, dirty_region);
}

long __stdcall hooks::ui::reset::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params) {
	static const auto original = m_d3d_device->get_original<fn>(ui::reset::index);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto ret = original(device, present_params);

	ImGui_ImplDX9_CreateDeviceObjects();

	return ret;
}

void __fastcall hooks::ui::lock_cursor::hook(i_surface* ecx, void* edx) {
	static const auto original = m_surface->get_original<fn>(ui::lock_cursor::index);

	return menu::m_opened ? ecx->unlock_cursor() : original(ecx);
}
