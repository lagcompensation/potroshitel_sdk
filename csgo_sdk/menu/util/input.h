#pragma once

namespace input {
	void init();
	void undo();

	long __stdcall wnd_proc(HWND hwnd, uint32_t msg, uint32_t w_param, uint32_t l_param);

	inline HWND m_hwnd;
	inline WNDPROC m_original_wnd_proc;
};