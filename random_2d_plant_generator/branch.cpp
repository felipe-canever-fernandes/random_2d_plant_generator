module;

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

import :branch;

namespace random_2d_plant_generator
{
	Branch::Branch
	(
		OnGrewUp const do_on_grew_up,
		Branch const* const p_parent,
		sf::Vector2f const position
	):
		shape(create_shape(position)),
		has_grown_up(false),
		do_on_grew_up(do_on_grew_up),
		p_parent(p_parent)
	{}

	auto Branch::update(float const delta_time) -> void
	{
		grow(delta_time);

		if (p_parent != nullptr)
			shape.setPosition(p_parent->get_tip_position());
	}

	auto Branch::draw(sf::RenderWindow& window) const -> void
	{
		window.draw(shape);
	}

	auto Branch::get_tip_position() const -> sf::Vector2f
	{
		auto const size = shape.getSize();
		auto const offset = sf::Vector2f(0, -size.y);
		return shape.getPosition() + offset;
	}

	auto Branch::get_size() const -> sf::Vector2f
	{
		return shape.getSize();
	}

	auto Branch::create_shape(sf::Vector2f const position) -> sf::RectangleShape
	{
		auto rectangle = sf::RectangleShape();

		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(position);

		return rectangle;
	}

	auto Branch::grow(float delta_time) -> void
	{
		static auto const maximum_size = sf::Vector2f({100, 300});
		static constexpr auto growth_speed = 10.0f;

		if (has_grown_up)
			return;

		static auto const calculate_new =
		[delta_time]
		(
			float const current,
			float const maximum,
			bool& has_reached_maximum
		)
		{
			if (current >= maximum)
			{
				has_reached_maximum = true;
				return current;
			}

			return current + delta_time * growth_speed;
		};

		auto const current_size = shape.getSize();

		auto has_x_grown_up = false;
		auto has_y_grown_up = false;

		auto const new_size = sf::Vector2f
		({
			calculate_new(current_size.x, maximum_size.x, has_x_grown_up),
			calculate_new(current_size.y, maximum_size.y, has_y_grown_up)
		});

		shape.setSize(new_size);
		shape.setOrigin({new_size.x / 2, new_size.y});

		has_grown_up = has_x_grown_up && has_y_grown_up;

		if (has_grown_up)
			do_on_grew_up(*this);
	}
}
