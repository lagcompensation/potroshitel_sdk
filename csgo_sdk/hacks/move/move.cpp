#include "../hacks.h"

void c_movement::handle(c_user_cmd* cmd) {
	if (cfg->m_move.m_bhop
		/* u can add other some checks, but again, this is for example */
		&& !(local_player->self()->get_flags().has(FL_ONGROUND)))
		cmd->m_buttons.remove(IN_JUMP);
}

void c_movement::correct(c_user_cmd* cmd, qangle_t old_angles) {
	/* movement correction, u can improve this urself but again, this is for example */
	const auto move_type = local_player->self()->get_move_type();
	if (move_type == MOVE_TYPE_NOCLIP
		|| move_type == MOVE_TYPE_LADDER)
		return;

	vec3_t right;
	auto fwd = cmd->m_view_angles.vectors(&right);

	if (fwd.z) {
		fwd.z = 0.f;
		fwd.normalize();
	}

	if (right.z) {
		right.z = 0.f;
		right.normalize();
	}

	if (const auto div = right.y * fwd.x - right.x * fwd.y) {
		vec3_t old_right;
		auto old_fwd = old_angles.vectors(&old_right);

		if (old_fwd.z) {
			old_fwd.z = 0.f;
			old_fwd.normalize();
		}

		if (old_right.z) {
			old_right.z = 0.f;
			old_right.normalize();
		}

		const vec2_t old_vel(
			old_fwd.x * cmd->m_move.x + old_right.x * cmd->m_move.y,
			old_fwd.y * cmd->m_move.x + old_right.y * cmd->m_move.y
		);

		cmd->m_move.y = (old_vel.y * fwd.x - old_vel.x * fwd.y) / div;
		cmd->m_move.x = (old_vel.x * right.y - old_vel.y * right.x) / div;

		static const auto cl_forwardspeed = interfaces::m_cvar_system->find_var(HASH("cl_forwardspeed"));
		static const auto cl_backspeed = interfaces::m_cvar_system->find_var(HASH("cl_backspeed"));
		static const auto cl_sidespeed = interfaces::m_cvar_system->find_var(HASH("cl_sidespeed"));

		const auto max_fwd_speed = cl_forwardspeed->get_float();
		const auto max_back_speed = cl_backspeed->get_float();
		const auto max_side_speed = cl_sidespeed->get_float();

		if ((cmd->m_move.x = std::clamp(cmd->m_move.x, -max_back_speed, max_fwd_speed)))
			cmd->m_buttons.add(cmd->m_move.x > 0.f
				? IN_FORWARD : IN_BACK);

		if ((cmd->m_move.y = std::clamp(cmd->m_move.y, -max_side_speed, max_side_speed)))
			cmd->m_buttons.add(cmd->m_move.y > 0.f
				? IN_MOVERIGHT : IN_MOVELEFT);
	}
}