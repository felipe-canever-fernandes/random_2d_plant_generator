#include <memory>
#include <SFML/Graphics.hpp>

import color;
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

	constexpr auto ground_height = 50.0f;

	auto const create_plant =
	[desktop_mode, ground_height]
	{
		return std::make_unique<random_2d_plant_generator::Plant>
		(
			sf::Vector2f
			(
				static_cast<float>(desktop_mode.width) / 2,
				static_cast<float>(desktop_mode.height) - ground_height
			)
		);
	};

	auto p_plant = create_plant();

	auto ground = sf::RectangleShape
		(sf::Vector2f(desktop_mode.width, ground_height));

	ground.setOrigin(desktop_mode.width / 2, ground_height);
	ground.setPosition(desktop_mode.width / 2, desktop_mode.height);

	ground.setFillColor
		(color::calculate_new_shade(p_plant->get_color(), 0.5f, false));

	auto const delta_time_clock = sf::Clock();

	while (window.isOpen())
	{
		for (auto event = sf::Event(); window.pollEvent(event);)
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				p_plant = create_plant();

				ground.setFillColor
				(
					color::calculate_new_shade
						(p_plant->get_color(), 0.5f, false)
				);
			}

		auto const delta_time = delta_time_clock.getElapsedTime().asSeconds();
		p_plant->update(delta_time);

		window.clear();
		p_plant->draw(window);
		window.draw(ground);
		window.display();
	}
}
