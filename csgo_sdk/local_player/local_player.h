#pragma once

#include "../globals.h"

class c_local_player : public c_singleton<c_local_player> {
private:
	struct {
		__forceinline void store() {
			m_cur_time = interfaces::m_global_vars->m_cur_time;
			m_frame_time = interfaces::m_global_vars->m_frame_time;

			m_in_prediction = interfaces::m_prediction->m_in_prediction;
			m_first_time_predicted = interfaces::m_prediction->m_first_time_predicted;
		}

		__forceinline void restore() {
			interfaces::m_global_vars->m_cur_time = m_cur_time;
			interfaces::m_global_vars->m_frame_time = m_frame_time;

			interfaces::m_prediction->m_in_prediction = m_in_prediction;
			interfaces::m_prediction->m_first_time_predicted = m_first_time_predicted;
		}

		float m_frame_time, m_cur_time;
		bool m_first_time_predicted, m_in_prediction;
	} m_backup;

	int* m_random_seed;
	c_cs_player* m_player;

	move_data_t* m_move_data;
public:
	c_local_player() {
		m_random_seed = *SIG("client.dll", "A3 ? ? ? ? 66 0F 6E 86").self_offset(0x1).cast<int**>();
		m_player = *SIG("client.dll", "89 35 ? ? ? ? F3 0F 10 48").self_offset(0x2).cast<c_cs_player**>();

		m_move_data = reinterpret_cast<move_data_t*>(interfaces::m_mem_alloc->alloc(sizeof(move_data_t)));
	}

	void update();
	void start(c_user_cmd* cmd);
	void end();

	c_cs_player* m_local;
	c_cs_player* self();
};

#define local_player c_local_player::instance()