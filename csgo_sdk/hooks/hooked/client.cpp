#include "../hooks.h"

void __stdcall hooks::client::create_move::hook(int sequence_number, float input_sample_frame_time, bool active, bool& send_packet) {
	static const auto original = m_client->get_original<fn>(22u);

	original(interfaces::m_client_dll, sequence_number, input_sample_frame_time, active);

	/* add this shit in frame_stage_notify too */
	/* but i very lazy for hooking frame_stage_notify */
	globals::m_local = reinterpret_cast<c_cs_player*>(interfaces::m_entity_list->get_client_entity(interfaces::m_engine->get_local_player()));

	if (!interfaces::m_engine->is_in_game() 
		|| !globals::m_local
		|| !globals::m_local->is_alive())
		return;

	const auto cmd = interfaces::m_input->get_user_cmd(sequence_number);
	if (!cmd
		|| !cmd->m_command_number)
		return;

	const auto old_angles = cmd->m_view_angles;

	hacks::g_prediction->update();
	
	hacks::g_move->handle(cmd);

	cmd->m_view_angles.sanitize();

	hacks::g_move->correct(cmd, old_angles);

	const auto verified = interfaces::m_input->get_verified_user_cmd(sequence_number);

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->get_check_sum();
}

__declspec (naked) void __stdcall hooks::client::create_move::proxy(int sequence_number, float input_sample_frame_time, bool active) {
	__asm {
		push ebp
		mov ebp, esp

		push ebx
		push esp
		push dword ptr[ebp + 16]
		push dword ptr[ebp + 12]
		push dword ptr[ebp + 8]

		call hooks::client::create_move::hook

		pop ebx

		pop ebp
		retn 12
	}
}
