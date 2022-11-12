#pragma once

#include "../globals.h"

namespace menu {
	void render();
	void init();
	void undo();

	inline bool m_opened;
}