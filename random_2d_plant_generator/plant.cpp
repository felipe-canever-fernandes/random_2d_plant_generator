module;

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

namespace random_2d_plant_generator
{
    Plant::Plant(sf::Vector2f const position):
    branch(position)
    {}

    auto Plant::update(float const delta_time) -> void
    {
        branch.update(delta_time);
    }

    auto Plant::draw(sf::RenderWindow& window) const -> void
    {
        branch.draw(window);
    }
}
