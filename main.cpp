#include <memory>
#include <SFML/Graphics.hpp>

import random_2d_plant_generator;

auto main() -> int
{
	auto const desktop_mode = sf::VideoMode::getDesktopMode();
	constexpr auto window_size_ratio = 0.8;

	auto const window_size = sf::Vector2u
	(
		static_cast<unsigned int>(desktop_mode.width * window_size_ratio),
		static_cast<unsigned int>(desktop_mode.height * window_size_ratio)
	);

	auto window = sf::RenderWindow
	(
		sf::VideoMode(window_size.x, window_size.y),
		"Random 2D Plant Generator"
	);

	auto const create_plant =
	[window_size]
	{
		return std::make_unique<random_2d_plant_generator::Plant>
		(
			sf::Vector2f
			(
				static_cast<float>(window_size.x) / 2,
				static_cast<float>(window_size.y)
			)
		);
	};

	auto p_plant = create_plant();
	auto const delta_time_clock = sf::Clock();

	while (window.isOpen())
	{
		for (auto event = sf::Event(); window.pollEvent(event);)
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonReleased:
				p_plant = create_plant();
				break;

			default:
				break;
			}

		auto const delta_time = delta_time_clock.getElapsedTime().asSeconds();
		p_plant->update(delta_time);

		window.clear();
		p_plant->draw(window);
		window.display();
	}
}
