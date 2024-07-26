#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SFML/Graphics/RenderTarget.hpp>

#include "player.h"
#include "map.h"

class Renderer
{
public:
    void drawRays(sf::RenderTarget &target, const Player &player, const Map &map);

private:
};

#endif // _RENDERER_H_ 3.14159265359f;