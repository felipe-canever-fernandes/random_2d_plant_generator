#include <SFML/Graphics.hpp>

import random_2d_plant_generator;

auto main() -> int
{
   auto window = sf::RenderWindow
   (
      sf::VideoMode(800, 600),
      "Random 2D Plant Generator"
   );

   auto const plant = random_2d_plant_generator::Plant();

   while (window.isOpen())
   {
      for (auto event = sf::Event(); window.pollEvent(event);)
         if (event.type == sf::Event::Closed)
            window.close();

      window.clear();
      plant.draw(window);
      window.display();
   }
}
