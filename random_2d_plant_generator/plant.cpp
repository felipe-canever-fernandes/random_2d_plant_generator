module;

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <random>

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

import color;

namespace random_2d_plant_generator
{
	std::mt19937 Plant::random_engine = std::mt19937(std::random_device()());

	std::normal_distribution<float>
		Plant::branching_relative_height_distribution(0.5f, 0.25f);

	std::normal_distribution<float>
		Plant::size_ratio_distribution(0.75f, 0.15f);

	std::binomial_distribution<> Plant::branching_count_distribution(5, 0.6);

	Plant::Plant(sf::Vector2f const position):
		branching_relative_height(0.25f),

		size_ratio
		(
			std::clamp(size_ratio_distribution(random_engine), 0.0f, 1.0f),
			std::clamp(size_ratio_distribution(random_engine), 0.0f, 1.0f)
		),

		branching_count
			(std::max(branching_count_distribution(random_engine), 1)),

		on_branch_can_branch(
			std::bind
			(
				&Plant::do_on_branch_can_branch,
				this,
				std::placeholders::_1
			)
		),

		branches({create_trunk(position)}),
		trunk(*std::begin(branches))
	{}

	auto Plant::get_color() const -> sf::Color
	{
		return trunk.get_color();
	}

	auto Plant::get_position() const -> sf::Vector2f
	{
		return trunk.get_position();
	}

	auto Plant::update(float const delta_time) -> void
	{
		assert(delta_time >= 0);

		for (auto& branch : branches)
			branch.update(delta_time);
	}

	auto Plant::draw(sf::RenderWindow& window) const -> void
	{
		for (auto const& branch : branches)
			branch.draw(window);
	}

	auto Plant::create_trunk(sf::Vector2f const position) const -> Branch
	{
		static auto color_component_distribution =
			std::uniform_int_distribution<unsigned>(0, 255);

		static auto width_distribution =
			std::normal_distribution(50.0f, 50.0f);

		static auto height_distribution =
			std::normal_distribution(200.0f, 100.0f);

		auto const size = sf::Vector2f
		(
			std::abs(width_distribution(random_engine)),
			std::abs(height_distribution(random_engine))
		);

		return Branch
		(
			sf::Color
			(
				color_component_distribution(random_engine),
				color_component_distribution(random_engine),
				color_component_distribution(random_engine),
				220
			),

			size,
			0,
			branching_relative_height,
			on_branch_can_branch,
			nullptr,
			position
		);
	}

	auto Plant::do_on_branch_can_branch(Branch const& branch) -> void
	{
		auto const original_color = branch.get_color();

		auto const new_color =
			color::calculate_new_shade(original_color, 1.1f, true);

		static constexpr auto minimum_component_size = 2.0f;

		auto const new_maximum_size = sf::Vector2f
		(
			branch.get_maximum_size().x * size_ratio.x,
			branch.get_maximum_size().y * size_ratio.y
		);

		if (new_maximum_size.x < minimum_component_size)
			return;

		if (new_maximum_size.y < minimum_component_size)
			return;

		static auto rotation_distribution =
			std::normal_distribution(0.0f, 45.0f);

		for (auto i = 0; i < branching_count; ++i)
		{
			auto const rotation = rotation_distribution(random_engine);

			branches.emplace_back
			(
				new_color,
				new_maximum_size,
				branch.get_rotation() + rotation,
				branching_relative_height,
				on_branch_can_branch,
				&branch
			);
		}
	}
}
