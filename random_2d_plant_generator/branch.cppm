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

        explicit Branch(sf::Vector2f position, OnGrewUp do_on_grew_up);

        auto update(float delta_time) -> void;
        auto draw(sf::RenderWindow& window) const -> void;

    private:
        sf::RectangleShape shape;
        OnGrewUp do_on_grew_up;

        [[nodiscard]]
        static auto create_shape(sf::Vector2f position) -> sf::RectangleShape;
    };
}