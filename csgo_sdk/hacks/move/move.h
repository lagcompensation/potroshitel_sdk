#pragma once

#include "../../globals.h"

class c_movement : public c_singleton<c_movement> {
public:
	void handle(c_user_cmd* cmd);
	void correct(c_user_cmd* cmd, qangle_t old_angles);
};

#define movement c_movement::instance()