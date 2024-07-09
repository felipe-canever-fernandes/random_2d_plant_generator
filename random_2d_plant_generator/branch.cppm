module;

#include <functional>
#include <SFML/Graphics.hpp>

export module random_2d_plant_generator:branch;

namespace random_2d_plant_generator
{
	class Branch
	{
	public:
		using OnCanBranch = std::function<void(Branch const& branch)>;

		explicit Branch
		(
			sf::Vector2f maximum_size,
			float rotation,
			float branching_relative_height,
			OnCanBranch do_on_can_branch,
			Branch const* p_parent,
			sf::Vector2f position = sf::Vector2f(0, 0)
		);

		auto update(float delta_time) -> void;
		auto draw(sf::RenderWindow& window) const -> void;

		[[nodiscard]] auto get_maximum_size() const -> sf::Vector2f;

		[[nodiscard]] auto get_tip_position() const -> sf::Vector2f;
		[[nodiscard]] auto get_size() const -> sf::Vector2f;
		[[nodiscard]] auto get_rotation() const -> float;

	private:
		[[nodiscard]]
		static auto create_shape
		(
			sf::Vector2f position,
			float rotation
		) -> sf::RectangleShape;

		sf::RectangleShape shape;
		sf::Vector2f maximum_size;
		float branching_relative_height;
		bool has_reached_branching_height;
		bool has_grown_up;
		OnCanBranch do_on_can_branch;
		Branch const* p_parent;

		auto grow(float delta_time) -> void;
	};
}
