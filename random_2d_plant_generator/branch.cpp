module;

#include <cassert>
#include <cmath>
#include <numbers>

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

import :branch;

namespace random_2d_plant_generator
{
	Branch::Branch
	(
		sf::Vector2f const maximum_size,
		float const rotation,
		float const branching_relative_height,
		OnCanBranch const do_on_can_branch,
		Branch const* const p_parent,
		sf::Vector2f const position
	):
		shape(create_shape(position, rotation)),
		maximum_size(validate_size(maximum_size)),

		branching_relative_height
		(
			validate_relative_value(branching_relative_height)
		),

		has_reached_branching_height(false),
		has_grown_up(false),
		do_on_can_branch(do_on_can_branch),
		p_parent(p_parent)
	{}

	auto Branch::update(float const delta_time) -> void
	{
		assert(delta_time >= 0);

		grow(delta_time);

		if (p_parent != nullptr)
			shape.setPosition(p_parent->get_tip_position());
	}

	auto Branch::draw(sf::RenderWindow& window) const -> void
	{
		window.draw(shape);
	}

	auto Branch::get_maximum_size() const -> sf::Vector2f
	{
		return maximum_size;
	}

	auto Branch::get_tip_position() const -> sf::Vector2f
	{
		static constexpr auto pi = std::numbers::pi_v<float>;

		auto const height = get_size().y;
		auto const rotation_in_radians = get_rotation() * pi / 180.0f;

		auto const offset = sf::Vector2f
		(
			height * std::sin(rotation_in_radians),
			-height * std::cos(rotation_in_radians)
		);

		return shape.getPosition() + offset;
	}

	auto Branch::get_size() const -> sf::Vector2f
	{
		return shape.getSize();
	}

	auto Branch::get_rotation() const -> float
	{
		return shape.getRotation();
	}

	auto Branch::validate_size(sf::Vector2f const size) -> sf::Vector2f
	{
		assert(size.x > 0);
		assert(size.y > 0);

		return size;
	}

	auto Branch::validate_relative_value(float const value) -> float
	{
		assert(value >= 0);
		assert(value <= 1);

		return value;
	}

	auto Branch::create_shape
	(
		sf::Vector2f const position,
		float const rotation
	) -> sf::RectangleShape
	{
		auto rectangle = sf::RectangleShape();

		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(position);
		rectangle.setRotation(rotation);

		return rectangle;
	}

	auto Branch::grow(float delta_time) -> void
	{
		assert(delta_time >= 0);

		static constexpr auto growth_speed = 3.0f;

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

		if (has_reached_branching_height)
			return;

		auto const branching_height =
			maximum_size.y * branching_relative_height;

		if (new_size.y >= branching_height)
		{
			has_reached_branching_height = true;
			do_on_can_branch(*this);
		}
	}
}
