#include "../utils.h"

namespace math {
	void sin_cos(float rad, float& sin, float& cos) {
		sin = std::sin(rad);
		cos = std::cos(rad);
	}
}
