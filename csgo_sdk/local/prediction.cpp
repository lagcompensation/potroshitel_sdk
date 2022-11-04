#include "prediction.h"

/* ONLY ENGINE PREDICTION HEREEEEEEEEEEEE......... */

namespace hacks {
	void c_prediction::update() {
		if (interfaces::m_client_state->m_delta_tick <= 0)
			return;

		interfaces::m_prediction->update(
			interfaces::m_client_state->m_delta_tick, true,
			interfaces::m_client_state->m_last_command_ack, interfaces::m_client_state->m_last_outgoing_command + interfaces::m_client_state->m_choked_commands
		);
	}
}
