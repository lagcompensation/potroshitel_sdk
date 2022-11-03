#include "common_includes.h"
#include "globals.h"
#include "menu/util/input.h"
#include "menu/menu.h"
#include "hooks/hooks.h"

int __stdcall undo() {
	hooks::undo();

	input::undo();

	menu::undo();

	return 1;
}

unsigned long __stdcall init(LPVOID module) {
	do {
		memory::get_all_modules();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (memory::m_modules.find(FNV1A("serverbrowser.dll")) == memory::m_modules.end());

	interfaces::init();

	input::init();

	menu::init();

	netvars::init();

	hooks::init();

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	undo();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(module), 0);
}

int __stdcall DllMain(HMODULE module, unsigned long reason_for_call, void* reserved) {
	if (reason_for_call != DLL_PROCESS_ATTACH)
		return 0;

	DisableThreadLibraryCalls(module);

	if (const auto thread = CreateThread(0, 0, init, module, 0, 0)) {
		CloseHandle(thread);
	}

	return 1;
}