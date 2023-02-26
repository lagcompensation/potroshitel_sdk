#include "common_includes.h"
#include "globals.h"
#include "menu/util/input.h"
#include "menu/menu.h"
#include "hooks/hooks.h"

void init(LPVOID module) {
	do {
		memory::get_all_modules();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (memory::m_modules.find(HASH("serverbrowser.dll")) == memory::m_modules.end());

	interfaces::init();

	input::init();

	menu::init();

	netvars::init();

	hooks::init();

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	hooks::undo();

	input::undo();

	menu::undo();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(module), 0);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason_for_call, LPVOID reserved) {
	if (reason_for_call != DLL_PROCESS_ATTACH)
		return FALSE;

	DisableThreadLibraryCalls(module);

	if (const auto thread = CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(init), module, 0, 0))
		CloseHandle(thread);

	return TRUE;
}
