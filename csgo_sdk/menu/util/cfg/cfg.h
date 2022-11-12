#pragma once

#include "../../../utils/singleton.h"

class c_cfg : public c_singleton<c_cfg> {
public:
	struct move_t {
		bool m_bhop;
	} m_move;

	struct models_t {
		int m_player_models_type;

		bool m_player_models;
		float m_player_models_clr[4] = { 1.f, 1.f, 1.f, 1.f };

		bool m_player_models_occluded;
		float m_player_models_occluded_clr[4] = { 1.f, 1.f, 1.f, 1.f };
	} m_models;
};

#define cfg c_cfg::instance()