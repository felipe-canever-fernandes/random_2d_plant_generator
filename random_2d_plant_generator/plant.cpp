module;

#include <functional>
#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

namespace random_2d_plant_generator
{
	Plant::Plant(sf::Vector2f const position):
		on_branch_grew_up(
			std::bind
			(
				&Plant::do_on_branch_grew_up,
				this,
				std::placeholders::_1
			)
		),

		branches
		({
			Branch({25, 100}, 0, on_branch_grew_up, nullptr, position)
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

	auto Plant::do_on_branch_grew_up(Branch const& branch) -> void
	{
		static constexpr auto size_ratio = 0.8f;
		static constexpr auto minimum_component_size = 1.0f;

		auto const new_size = branch.get_size() * size_ratio;

		if (new_size.x < minimum_component_size)
			return;

		if (new_size.y < minimum_component_size)
			return;

		static constexpr auto rotation_offset = 15.0f;

		branches.emplace_back
		(
			new_size,
			branch.get_rotation() + rotation_offset,
			on_branch_grew_up,
			&branch
		);
	}
}
