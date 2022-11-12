#include "interfaces.h"

namespace interfaces {
	void init() {
		m_client_dll = get<i_base_client_dll*>(HASH("client.dll"), HASH("VClient018"));
		m_engine = get<i_engine_client*>(HASH("engine.dll"), HASH("VEngineClient014"));
		m_entity_list = get<i_client_entity_list*>(HASH("client.dll"), HASH("VClientEntityList003"));

		m_client_mode = **memory::get_vfunc<memory::address_t>(m_client_dll, 10).self_offset(0x5).cast<i_client_mode***>();
		m_global_vars = **memory::get_vfunc<memory::address_t>(m_client_dll, 11).self_offset(0xA).cast<i_global_vars***>();
		m_client_state = **memory::get_vfunc<memory::address_t>(m_engine, 12).self_offset(0x10).cast<i_client_state***>();

		m_mem_alloc = *EXPORT("tier0.dll", "g_pMemAlloc").cast<i_mem_alloc**>();
		m_key_values_system = EXPORT("vstdlib.dll", "KeyValuesSystem").cast<i_key_values_system*(*)()>()();

		m_model_info = get<i_model_info*>(HASH("engine.dll"), HASH("VModelInfoClient004"));
		m_surface = get<i_surface*>(HASH("vguimatsurface.dll"), HASH("VGUI_Surface031"));

		m_input = *SIG("client.dll", "B9 ? ? ? ? 8B 40 38 FF D0 84 C0 0F 85").self_offset(0x1).cast<i_input**>();
		m_move_helper = **SIG("client.dll", "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01").self_offset(0x2).cast<i_move_helper***>();

		m_prediction = get<i_prediction*>(HASH("client.dll"), HASH("VClientPrediction001"));
		m_game_movement = get<i_game_movement*>(HASH("client.dll"), HASH("GameMovement001"));
		m_debug_overlay = get<i_debug_overlay*>(HASH("engine.dll"), HASH("VDebugOverlay004"));
		m_cvar_system = get<i_cvar_system*>(HASH("vstdlib.dll"), HASH("VEngineCvar007"));
		m_event_manager = get<i_game_event_manager*>(HASH("engine.dll"), HASH("GAMEEVENTSMANAGER002"));
		m_trace_system = get<i_engine_trace*>(HASH("engine.dll"), HASH("EngineTraceClient004"));
		m_surface_data = get<i_surface_data*>(HASH("vphysics.dll"), HASH("VPhysicsSurfaceProps001"));
		m_input_system = get<i_input_system*>(HASH("inputsystem.dll"), HASH("InputSystemVersion001"));

		m_game_rules = *SIG("client.dll", "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A").self_offset(0x1).cast<i_game_rules***>();

		m_game_types = get<i_game_types*>(HASH("matchmaking.dll"), HASH("VENGINE_GAMETYPES_VERSION002"));
		m_model_cache = get<i_mdl_cache*>(HASH("datacache.dll"), HASH("MDLCache004"));
		m_model_render = get<i_model_render*>(HASH("engine.dll"), HASH("VEngineModel016"));
		m_material_system = get<i_material_system*>(HASH("materialsystem.dll"), HASH("VMaterialSystem080"));

		m_glow_manager = *SIG("client.dll", "0F 11 05 ? ? ? ? 83 C8 01").self_offset(0x3).cast<i_glow_object_manager**>();
		m_beams = *SIG("client.dll", "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9").self_offset(0x1).cast<i_view_render_beams**>();
		m_weapon_system = *SIG("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0").self_offset(0x2).cast<i_weapon_system**>();
		m_player_resource = *SIG("client.dll", "8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7").self_offset(0x2).cast<i_cs_player_resource***>();

		m_localize = get<i_localize*>(HASH("localize.dll"), HASH("Localize_001"));
		m_panel = get<i_panel*>(HASH("vgui2.dll"), HASH("VGUI_Panel009"));
		m_render_view = get<i_render_view*>(HASH("engine.dll"), HASH("VEngineRenderView014"));

		m_d3d_device = **SIG("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C").self_offset(0x1).cast<IDirect3DDevice9***>();
	}
}
