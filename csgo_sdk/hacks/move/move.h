#pragma once

#include "../../globals.h"

namespace hacks {
	class c_move {
	public:
		void handle(c_user_cmd* cmd);
		void correct(c_user_cmd* cmd, qangle_t old_angles);
	};

	inline const auto g_move = std::make_unique<c_move>();
}