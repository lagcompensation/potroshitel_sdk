#include "hooks.h"

namespace hooks {
	void init() {
		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_d3d_device = std::make_unique<memory::hook_t>(interfaces::m_d3d_device);

		m_d3d_device->hook(16u, ui::reset::hook);
		m_d3d_device->hook(17u, ui::present::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_surface = std::make_unique<memory::hook_t>(interfaces::m_surface);

		m_surface->hook(67u, ui::lock_cursor::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */

		m_client = std::make_unique<memory::hook_t>(interfaces::m_client_dll);

		m_client->hook(22u, client::create_move::hook);

		/* // // // // // // // // // // // // // // // // // // // // // // // */
	}

	void undo() {
		m_d3d_device->unhook();
		m_surface->unhook();
		m_client->unhook();
	}
}