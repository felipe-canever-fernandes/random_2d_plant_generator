module;

#include <SFML/Graphics.hpp>

export module random_2d_plant_generator;

namespace random_2d_plant_generator
{
    export class Plant
    {
    public:
        explicit Plant();
        auto draw(sf::RenderWindow& window) const -> void;

    private:
        sf::RectangleShape shape;
        [[nodiscard]] static auto create_shape() -> sf::RectangleShape;
    };
}