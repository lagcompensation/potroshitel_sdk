#include "hooks.h"

namespace hooks {
	void init() {
		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_d3d_device = std::make_unique<memory::hook_t>(interfaces::m_d3d_device);

		m_d3d_device->hook(ui::reset::index, ui::reset::hook);
		m_d3d_device->hook(ui::present::index, ui::present::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_surface = std::make_unique<memory::hook_t>(interfaces::m_surface);

		m_surface->hook(ui::lock_cursor::index, ui::lock_cursor::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_client = std::make_unique<memory::hook_t>(interfaces::m_client_dll);

		m_client->hook(client::create_move::index, client::create_move::proxy);

		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_render = std::make_unique<memory::hook_t>(interfaces::m_model_render);

		m_render->hook(render::draw_model_execute::index, render::draw_model_execute::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */
	}

	void undo() {
		m_d3d_device->unhook();
		m_surface->unhook();
		m_client->unhook();
		m_render->unhook();
	}
}