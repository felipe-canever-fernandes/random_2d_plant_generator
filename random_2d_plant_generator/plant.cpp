module random_2d_plant_generator;

namespace random_2d_plant_generator
{
    Plant::Plant(): shape(create_shape()) {}

    auto Plant::draw(sf::RenderWindow& window) const -> void
    {
        window.draw(shape);
    }

    auto Plant::create_shape() -> sf::RectangleShape
    {
        auto rectangle = sf::RectangleShape({100, 300});
        rectangle.setFillColor(sf::Color::Green);
        return rectangle;
    }
}
