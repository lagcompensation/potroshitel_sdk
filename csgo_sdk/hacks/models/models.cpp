#include "../hacks.h"
#include "../../hooks/hooks.h"

i_material* c_models::create_material(std::string_view material_name, std::string_view shader_type, std::string_view material_data) {
	const auto key_values = reinterpret_cast<c_key_values*>(interfaces::m_mem_alloc->alloc(36u));

	key_values->init(shader_type.data());
	key_values->load_from_buffer(material_name.data(), material_data.data());

	return interfaces::m_material_system->create_material(material_name.data(), key_values);
}

void c_models::override_material(const float* clr, bool ignorez) {
	i_material* material = nullptr;

	/* example how to use player chams material */
	switch (cfg->m_models.m_player_models_type) {
	case MATERIAL_TYPE_REGULAR: 
		material = ignorez ? m_regular_z : m_regular; 
		break;
	case MATERIAL_TYPE_FLAT: 
		material = ignorez ? m_flat_z : m_flat; 
		break;
	default:
		break;
	}

	material->alpha_modulate(clr[3]);
	material->color_modulate(clr[0], clr[1], clr[2]);

	if (const auto $envmaptint = material->find_var("$envmaptint", nullptr, false))
		$envmaptint->set_value(vec3_t(clr[0], clr[1], clr[2]));

	interfaces::m_model_render->forced_material_override(material);
}

bool c_models::on_draw_model(i_model_render* ecx, void* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones) {
	static const auto original = hooks::m_render->get_original<hooks::render::draw_model_execute::fn>(hooks::render::draw_model_execute::index);

	/* this is for example */
	/* but this works fine! */
	/* u can rework / improve urself */
	const auto entity = reinterpret_cast<c_base_entity*>(interfaces::m_entity_list->get_client_entity(info.m_index));
	if (!entity
		|| !entity->is_player())
		return true;

	const auto player = reinterpret_cast<c_cs_player*>(entity);
	if (!player->is_alive()
		|| !player->is_enemy(local_player->self()))
		return true;

	const auto is_player = strstr(info.m_model->m_name, "models/player");
	if (is_player) {
		if (cfg->m_models.m_player_models) {
			if (cfg->m_models.m_player_models_occluded) {
				override_material(cfg->m_models.m_player_models_occluded_clr, true);
				original(ecx, context, state, info, bones);
			}

			override_material(cfg->m_models.m_player_models_clr, false);
		}

		return true;
	}
	else
		return true;

	return false;
}
