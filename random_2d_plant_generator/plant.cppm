module;

#include <list>
#include <random>

#include <SFML/Graphics.hpp>

export module random_2d_plant_generator:plant;

import :branch;

namespace random_2d_plant_generator
{
	export class Plant
	{
	public:
		explicit Plant(sf::Vector2f position);

		[[nodiscard]] auto get_color() const -> sf::Color;
		[[nodiscard]] auto get_position() const -> sf::Vector2f;

		auto update(float delta_time) -> void;
		auto draw(sf::RenderWindow& window) const -> void;

	private:
		static std::mt19937 random_engine;

		static std::normal_distribution<float>
			branching_relative_height_distribution;

		static std::normal_distribution<float> size_ratio_distribution;
		static std::binomial_distribution<> branching_count_distribution;

		float branching_relative_height;
		sf::Vector2f size_ratio;
		int branching_count;

		Branch::OnCanBranch on_branch_can_branch;
		std::list<Branch> branches;
		Branch& trunk;

		[[nodiscard]] auto create_trunk(sf::Vector2f position) const -> Branch;
		auto do_on_branch_can_branch(Branch const& branch) -> void;
	};
}
