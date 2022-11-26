#include "local_player.h"

/* this file using for engine_prediction and other local stuff related to engine_prediction... or got urself.. */

void c_local_player::update() {
	if (interfaces::m_client_state->m_delta_tick <= 0)
		return;

	interfaces::m_prediction->update(
		interfaces::m_client_state->m_delta_tick, true,
		interfaces::m_client_state->m_last_command_ack, interfaces::m_client_state->m_last_outgoing_command + interfaces::m_client_state->m_choked_commands
	);
}

void c_local_player::start(c_user_cmd* cmd) {
	m_backup.store();

	m_player = m_local;
	*m_random_seed = cmd->m_random_seed;

	interfaces::m_prediction->m_in_prediction = true;
	interfaces::m_prediction->m_first_time_predicted = false;

	interfaces::m_global_vars->m_cur_time = TICKS_TO_TIME(m_local->get_tick_base());
	interfaces::m_global_vars->m_frame_time = interfaces::m_prediction->m_engine_paused ? 0.f : interfaces::m_global_vars->m_interval_per_tick;

	interfaces::m_move_helper->set_host(m_local);
	interfaces::m_game_movement->start_track_prediction_errors(m_local);

	interfaces::m_prediction->setup_move(m_local, cmd, interfaces::m_move_helper, m_move_data);
	interfaces::m_game_movement->process_movement(m_local, m_move_data);
	interfaces::m_prediction->finish_move(m_local, cmd, m_move_data);
	interfaces::m_move_helper->process_impacts();

	interfaces::m_game_movement->finish_track_prediction_errors(m_local);
	interfaces::m_move_helper->set_host(nullptr);
	interfaces::m_game_movement->reset();
}

void c_local_player::end() {
	m_player = nullptr;
	*m_random_seed = -1;

	m_backup.restore();
}

c_cs_player* c_local_player::self() {
	/* works fine but not good */
	/* maybe i am wrong idk.. */
	return m_local;
}
