#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include "player.h"
#include "map.h"

constexpr float SCREEN_W = 1500.0f;
constexpr float SCREEN_H = 1000.0f;

class Renderer
{
public:
    void init();
    void draw3dView(sf::RenderTarget &target, const Player &player, const Map &map);

private:
    sf::Texture skyTexture;

    sf::Texture screenBuffer;
    sf::Sprite screenBufferSprite;
};

#endif