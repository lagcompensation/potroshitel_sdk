#include "../hooks.h"

void __fastcall hooks::render::draw_model_execute::hook(i_model_render* ecx, void* edx, void* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones) {
	static const auto original = m_render->get_original<fn>(render::draw_model_execute::index);

	if (interfaces::m_model_render->is_forced_material_override())
		return original(ecx, context, state, info, bones);

	if (player_models->on_draw_model(ecx, context, state, info, bones))
		original(ecx, context, state, info, bones);

	interfaces::m_model_render->forced_material_override(nullptr);
}