module;

#include <functional>
#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

namespace random_2d_plant_generator
{
	Plant::Plant(sf::Vector2f const position):
		on_branch_can_branch(
			std::bind
			(
				&Plant::do_on_branch_can_branch,
				this,
				std::placeholders::_1
			)
		),

		branches
		({
			Branch({10, 100}, 0, 0.5f, on_branch_can_branch, nullptr, position)
		})
	{}

	auto Plant::update(float const delta_time) -> void
	{
		for (auto& branch : branches)
			branch.update(delta_time);
	}

	auto Plant::draw(sf::RenderWindow& window) const -> void
	{
		for (auto const& branch : branches)
			branch.draw(window);
	}

	auto Plant::do_on_branch_can_branch(Branch const& branch) -> void
	{
		static constexpr auto size_ratio = 0.8f;
		static constexpr auto minimum_component_size = 1.0f;

		auto const new_maximum_size = branch.get_maximum_size() * size_ratio;

		if (new_maximum_size.x < minimum_component_size)
			return;

		if (new_maximum_size.y < minimum_component_size)
			return;

		static constexpr auto rotation_spread = 30.0f;

		for (auto const rotation_offset : {-rotation_spread, rotation_spread})
		{
			branches.emplace_back
			(
				new_maximum_size,
				branch.get_rotation() + rotation_offset,
				0.25f,
				on_branch_can_branch,
				&branch
			);
		}
	}
}
