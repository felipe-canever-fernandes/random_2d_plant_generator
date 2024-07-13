#include <memory>
#include <SFML/Graphics.hpp>

import random_2d_plant_generator;

auto main() -> int
{
	auto const desktop_mode = sf::VideoMode::getDesktopMode();

	auto window = sf::RenderWindow
	(
		desktop_mode, "Random 2D Plant Generator", sf::Style::Fullscreen
	);

	auto const create_plant =
	[desktop_mode]
	{
		return std::make_unique<random_2d_plant_generator::Plant>
		(
			sf::Vector2f
			(
				static_cast<float>(desktop_mode.width) / 2,
				static_cast<float>(desktop_mode.height)
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
