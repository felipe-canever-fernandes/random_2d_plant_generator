module;

#include <algorithm>
#include <cassert>

module color;

namespace color
{
	auto calculate_new_shade
		(sf::Color const color, float const ratio, bool const keeps_alpha)
		-> sf::Color
	{
		assert(ratio >= 0.0f);

		static auto const calculate_new_component =
		[](sf::Uint8 const original_component, float const ratio)
		{
			auto const scaled =
				static_cast<unsigned>(original_component * ratio);

			return static_cast<sf::Uint8>(std::clamp(scaled, 0u, 255u));
		};

		return sf::Color
		(
			calculate_new_component(color.r, ratio),
			calculate_new_component(color.g, ratio),
			calculate_new_component(color.b, ratio),
			keeps_alpha ? color.a : 255
		);
	}
}
