#pragma once
#include "../globals.h"

namespace hacks {
	class c_prediction {
	public:
		void update();
		void start(c_user_cmd* cmd);
		void end(c_user_cmd* cmd);
	};

	inline const auto g_prediction = std::make_unique<c_prediction>();
}