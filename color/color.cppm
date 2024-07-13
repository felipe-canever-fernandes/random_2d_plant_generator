module;

#include <SFML/Graphics.hpp>

export module color;

namespace color
{
	export [[nodiscard]] auto calculate_new_shade
		(sf::Color color, float ratio, bool keeps_alpha) -> sf::Color;
}