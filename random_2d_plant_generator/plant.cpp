module;

#include <functional>
#include <print>

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

		branches({Branch(on_branch_grew_up, nullptr, position)})
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
		branches.emplace_back(on_branch_grew_up, &branch);
	}
}
