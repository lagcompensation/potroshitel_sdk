#pragma once

#include "../globals.h"

namespace hooks {
	void init();
	void undo();

	namespace ui {
		namespace reset {
			constexpr auto index = 16u;
			using fn = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params);
		}

		namespace present {
			constexpr auto index = 17u;
			using fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
			long __stdcall hook(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region);
		}

		namespace lock_cursor {
			constexpr auto index = 67u;
			using fn = void(__thiscall*)(i_surface*);
			void __fastcall hook(i_surface* ecx, void* edx);
		}
	}

	namespace client {
		namespace create_move {
			constexpr auto index = 22u;
			using fn = void(__thiscall*)(void*, int, float, bool);
			void __stdcall proxy(int sequence_number, float input_sample_frame_time, bool active);
			void __stdcall hook(int sequence_number, float input_sample_frame_time, bool active, bool& send_packet);
		}
	}

	namespace render {
		namespace draw_model_execute {
			constexpr auto index = 21u;
			using fn = void(__thiscall*)(i_model_render*, void*, const draw_model_state_t&, const model_render_info_t&, matrix3x4_t*);
			void __fastcall hook(i_model_render* ecx, void* edx, void* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones);
		}
	}

	inline std::unique_ptr<memory::hook_t> m_d3d_device;
	inline std::unique_ptr<memory::hook_t> m_surface;
	inline std::unique_ptr<memory::hook_t> m_client;
	inline std::unique_ptr<memory::hook_t> m_render;
}