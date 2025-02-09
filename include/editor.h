#ifndef _EDITOR_H
#define _EDITOR_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include "map.h"

class Editor
{
public:
  Editor(sf::RenderWindow &window);
  void run(sf::RenderWindow &window, Map &map);

  void handleEvent(const sf::Event &event);
  std::string savedFileName;

private:
  sf::RectangleShape cell;
  bool isFirstMouse;
  sf::Vector2i lastMousePos;
  sf::View view;
  int textureNo;
  int currentLayer;
};
#endif // !_EDITOR_H