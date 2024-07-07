module;

#include <SFML/Graphics.hpp>

module random_2d_plant_generator;

namespace random_2d_plant_generator
{
    Plant::Plant(sf::Vector2f const position):
    shape(create_shape(position))
    {}

    auto Plant::draw(sf::RenderWindow& window) const -> void
    {
        window.draw(shape);
    }

    auto Plant::create_shape(sf::Vector2f const position) -> sf::RectangleShape
    {
        auto const size = sf::Vector2f({100, 300});
        auto rectangle = sf::RectangleShape(size);

        rectangle.setOrigin({size.x / 2, size.y});
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setPosition(position);

        return rectangle;
    }
}
