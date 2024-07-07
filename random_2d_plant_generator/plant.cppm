module;

#include <list>
#include <SFML/Graphics.hpp>

export module random_2d_plant_generator:plant;

import :branch;

namespace random_2d_plant_generator
{
	export class Plant
	{
	public:
		explicit Plant(sf::Vector2f position);

		auto update(float delta_time) -> void;
		auto draw(sf::RenderWindow& window) const -> void;

	private:
		Branch::OnGrewUp on_branch_grew_up;
		std::list<Branch> branches;

		auto do_on_branch_grew_up(Branch const& branch) -> void;
	};
}
