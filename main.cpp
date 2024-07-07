#include <SFML/Graphics.hpp>

import random_2d_plant_generator;

auto main() -> int
{
   auto const desktop_mode = sf::VideoMode::getDesktopMode();
   constexpr auto window_size_ratio = 0.8;

   auto window = sf::RenderWindow
   (
      sf::VideoMode
      (
         static_cast<unsigned int>(desktop_mode.width * window_size_ratio),
         static_cast<unsigned int>(desktop_mode.height * window_size_ratio)
      ),

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
