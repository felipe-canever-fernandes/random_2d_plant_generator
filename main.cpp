#include <SFML/Graphics.hpp>

auto main() -> int
{
   auto window = sf::RenderWindow
   (
      sf::VideoMode(800, 600),
      "Random 2D Plant Generator"
   );

   auto const rectangle = []
   {
      auto rectangle =  sf::RectangleShape({100, 300});
      rectangle.setFillColor(sf::Color::Green);
      return rectangle;
   }();

   while (window.isOpen())
   {
      for (auto event = sf::Event(); window.pollEvent(event);)
         if (event.type == sf::Event::Closed)
            window.close();

      window.clear();
      window.draw(rectangle);
      window.display();
   }
}
