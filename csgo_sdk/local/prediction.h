#pragma once
#include "../globals.h"

namespace hacks {
	class c_prediction {
	public:
		void update();
	};

	inline const auto g_prediction = std::make_unique<c_prediction>();
}
