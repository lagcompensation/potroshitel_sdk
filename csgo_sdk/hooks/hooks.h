#pragma once

#include "../globals.h"

namespace hooks {
	void init();

	void undo();

	namespace ui {
		namespace reset {
			using fn = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params);
		}

		namespace present {
			using fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
			long __stdcall hook(IDirect3DDevice9* device, RECT* src_rect, RECT* dest_rect, HWND dest_wnd_override, RGNDATA* dirty_region);
		}

		namespace lock_cursor {
			using fn = void(__thiscall*)(i_surface*);
			void __fastcall hook(i_surface* ecx, void* edx);
		}
	}

	namespace client {
		namespace create_move {
			using fn = void(__thiscall*)(void*, int, float, bool);
			void __stdcall hook(int sequence_number, float input_sample_frame_time, bool active, bool& send_packet);
			void __stdcall proxy(int sequence_number, float input_sample_frame_time, bool active);
		}
	}

	inline std::unique_ptr<memory::hook_t> m_d3d_device;
	inline std::unique_ptr<memory::hook_t> m_surface;
	inline std::unique_ptr<memory::hook_t> m_client;
}