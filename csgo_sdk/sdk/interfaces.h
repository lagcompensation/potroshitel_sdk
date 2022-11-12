#pragma once
#include "sdk.h"

namespace interfaces {
	template <typename T>
	__forceinline T get(uint32_t module_hash, uint32_t interface_hash) {
		auto addr = memory::get_export(module_hash, HASH("CreateInterface"));

		if (*addr.offset(0x4) == 0xE9
			&& *addr.self_rel32(0x5).offset(0x5) == 0x35) {
			addr = **addr.offset(0x6).cast<memory::address_t**>();
		}
		else if (*addr.offset(0x2) == 0x35) {
			addr = **addr.offset(0x3).cast<memory::address_t**>();
		}
		else {
			return 0;
		}

		using create_fn_t = uintptr_t*(__cdecl*)();

		for (; addr; addr = *addr.offset<memory::address_t*>(0x8)) {
			const auto name = *addr.offset<const char**>(0x4);
			if (!name
				|| HASH_RT(name) != interface_hash)
				continue;

			return reinterpret_cast<T>((*addr.cast<create_fn_t*>())());
		}

		return 0;
	}

	void init();

	inline i_base_client_dll*		m_client_dll;
	inline i_engine_client*			m_engine;
	inline i_client_entity_list*	m_entity_list;
	inline i_client_mode*			m_client_mode;
	inline i_global_vars*			m_global_vars;
	inline i_client_state*			m_client_state;
	inline i_mem_alloc*				m_mem_alloc;
	inline i_key_values_system*		m_key_values_system;
	inline i_model_info*			m_model_info;
	inline i_surface*				m_surface;
	inline i_input*					m_input;
	inline i_move_helper*			m_move_helper;
	inline i_prediction*			m_prediction;
	inline i_game_movement*			m_game_movement;
	inline i_debug_overlay*			m_debug_overlay;
	inline i_cvar_system*			m_cvar_system;
	inline i_game_event_manager*	m_event_manager;
	inline i_engine_trace*			m_trace_system;
	inline i_surface_data*			m_surface_data;
	inline i_input_system*			m_input_system;
	inline i_game_rules**			m_game_rules;
	inline i_game_types*			m_game_types;
	inline i_mdl_cache*				m_model_cache;
	inline i_model_render*			m_model_render;
	inline i_material_system*		m_material_system;
	inline i_glow_object_manager*	m_glow_manager;
	inline i_view_render_beams*		m_beams;
	inline i_weapon_system*			m_weapon_system;
	inline i_cs_player_resource**	m_player_resource;
	inline i_localize*				m_localize;
	inline i_panel*					m_panel;
	inline i_render_view*			m_render_view;

	inline IDirect3DDevice9*		m_d3d_device;
}