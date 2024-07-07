module;

#include <functional>
#include <print>

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

namespace random_2d_plant_generator
{
	Plant::Plant(sf::Vector2f const position):
		branch
		(
			position,
			std::bind(&Plant::do_on_branch_grew_up, this, std::placeholders::_1)
		)
	{}

	auto Plant::update(float const delta_time) -> void
	{
		branch.update(delta_time);
	}

	auto Plant::draw(sf::RenderWindow& window) const -> void
	{
		branch.draw(window);
	}

	auto Plant::do_on_branch_grew_up(Branch const& branch) -> void
	{
		std::println("Branch grew up.");
	}
}
