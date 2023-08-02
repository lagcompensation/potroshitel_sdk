#include "../hooks.h"

__declspec (naked) void __stdcall hooks::client::create_move::proxy(int sequence_number, float input_sample_frame_time, bool active) {
	__asm {
		push ebp
		mov ebp, esp

		push ebx
		push esp
		push dword ptr[ebp + 16]
		push dword ptr[ebp + 12]
		push dword ptr[ebp + 8]

		call hook

		pop ebx

		pop ebp
		retn 12
	}
}

void __stdcall hooks::client::create_move::hook(int sequence_number, float input_sample_frame_time, bool active, bool& send_packet) {
	static const auto original = m_client->get_original<fn>(client::create_move::index);

	original(interfaces::m_client_dll, sequence_number, input_sample_frame_time, active);

	/* add this shit in frame_stage_notify too */
	/* but i very lazy for hooking frame_stage_notify */
	local_player->m_local = reinterpret_cast<c_cs_player*>(interfaces::m_entity_list->get_client_entity(interfaces::m_engine->get_local_player()));

	if (!interfaces::m_engine->is_in_game() 
		|| !local_player->self()
		|| !local_player->self()->is_alive())
		return;

	const auto cmd = interfaces::m_input->get_user_cmd(sequence_number);
	if (!cmd
		|| !cmd->m_command_number)
		return;

	const auto old_angles = cmd->m_view_angles;

	local_player->update();

	movement->handle(cmd);

	local_player->start(cmd);

	/* here some stuff... */
	/* ..................  */

	local_player->end();

	cmd->m_view_angles.sanitize();

	movement->correct(cmd, old_angles);

	const auto verified = interfaces::m_input->get_verified_user_cmd(sequence_number);

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_check_sum();
}
