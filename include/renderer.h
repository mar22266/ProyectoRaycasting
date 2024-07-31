#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "player.h"
#include "map.h"

constexpr float SCREEN_W = 1500.0f;
constexpr float SCREEN_H = 1000.0f;

class Renderer
{
public:
    void init();
    void draw3dView(sf::RenderTarget &target, const Player &player, const Map &map);
    void drawRays(sf::RenderTarget &target, const Player &player, const Map &map);

private:
    sf::Texture wallTexture;
    sf::Sprite wallSprite;
};

#endif