#pragma once

namespace math {
	constexpr auto m_pi = 3.14159265358979323846f;
	constexpr auto m_rad_pi = 180.f / m_pi;
	constexpr auto m_deg_pi = m_pi / 180.f;
	
	void sin_cos(float rad, float& sin, float& cos);

	__forceinline float rad_to_deg(float rad) { return rad * m_rad_pi; }

	__forceinline float deg_to_rad(float deg) { return deg * m_deg_pi; }
}
