#pragma once

#include "../../globals.h"

class c_models : public c_singleton<c_models> {
private:
	enum e_material_type {
		MATERIAL_TYPE_REGULAR,
		MATERIAL_TYPE_FLAT
	};

	void override_material(const float* clr, bool ignorez);
	i_material* create_material(std::string_view material_name, std::string_view shader_type, std::string_view material_data);

	i_material* m_regular = nullptr;
	i_material* m_regular_z = nullptr;

	i_material* m_flat = nullptr;
	i_material* m_flat_z = nullptr;
public:
	c_models() {
		m_regular = create_material("potroshitel_regular.vmt", "VertexLitGeneric", R"#("VertexLitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$ignorez"      "0"
	"$model"		"1"
	"$flat"			"0"
	"$nocull"		"1"
	"$halflambert"	"1"
	"$nofog"		"1"
	"$wireframe"	"0"
})#");

		m_regular_z = create_material("potroshitel_regular_z.vmt", "VertexLitGeneric", R"#("VertexLitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$ignorez"      "1"
	"$model"		"1"
	"$flat"			"0"
	"$nocull"		"1"
	"$halflambert"	"1"
	"$nofog"		"1"
	"$wireframe"	"0"
})#");

		m_flat = create_material("potroshitel_flat.vmt", "UnlitGeneric", R"#("UnlitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$ignorez"      "0"
	"$model"		"1"
	"$flat"			"1"
	"$nocull"		"1"
	"$selfillum"	"1"
	"$halflambert"	"1"
	"$nofog"		"1"
	"$wireframe"	"0"
})#");

		m_flat_z = create_material("potroshitel_flat_z.vmt", "UnlitGeneric", R"#("UnlitGeneric" {
	"$basetexture" "vgui/white_additive"
	"$ignorez"      "1"
	"$model"		"1"
	"$flat"			"1"
	"$nocull"		"1"
	"$selfillum"	"1"
	"$halflambert"	"1"
	"$nofog"		"1"
	"$wireframe"	"0"
})#");
	}

	bool on_draw_model(i_model_render* ecx, void* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones);
};

#define player_models c_models::instance()
