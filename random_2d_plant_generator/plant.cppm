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
		Branch::OnCanBranch on_branch_can_branch;
		std::list<Branch> branches;

		auto do_on_branch_can_branch(Branch const& branch) -> void;
	};
}
