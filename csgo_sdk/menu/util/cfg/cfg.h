#pragma once

class c_cfg {
public:
	struct move_t {
		bool m_bhop;
	} m_move{};
};

inline const auto g_cfg = std::make_unique<c_cfg>();