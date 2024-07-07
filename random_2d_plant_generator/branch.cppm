module;

#include <functional>
#include <SFML/Graphics.hpp>

export module random_2d_plant_generator:branch;

namespace random_2d_plant_generator
{
	class Branch
	{
	public:
		using OnGrewUp = std::function<void(Branch const& branch)>;

		explicit Branch
		(
			OnGrewUp do_on_grew_up,
			Branch const* p_parent,
			sf::Vector2f position = sf::Vector2f(0, 0)
		);

		auto update(float delta_time) -> void;
		auto draw(sf::RenderWindow& window) const -> void;

		[[nodiscard]] auto get_tip_position() const -> sf::Vector2f;
		[[nodiscard]] auto get_size() const -> sf::Vector2f;

	private:
		[[nodiscard]]
		static auto create_shape(sf::Vector2f position) -> sf::RectangleShape;

		sf::RectangleShape shape;
		bool has_grown_up;
		OnGrewUp do_on_grew_up;
		Branch const* p_parent;

		auto grow(float delta_time) -> void;
	};
}
