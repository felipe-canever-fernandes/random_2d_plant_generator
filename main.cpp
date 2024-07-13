#include <memory>
#include <SFML/Graphics.hpp>

import random_2d_plant_generator;

auto main() -> int
{
	auto const desktop_mode = sf::VideoMode::getDesktopMode();

	auto window = sf::RenderWindow
	(
		desktop_mode,
		"Random 2D Plant Generator",
		sf::Style::Fullscreen,

		[]
		{
			auto context_settings = sf::ContextSettings();
			context_settings.antialiasingLevel = 8;
			return context_settings;
		}()
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
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
				p_plant = create_plant();

		auto const delta_time = delta_time_clock.getElapsedTime().asSeconds();
		p_plant->update(delta_time);

		window.clear();
		p_plant->draw(window);
		window.display();
	}
}
