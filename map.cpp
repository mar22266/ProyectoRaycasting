#include "map.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

Map::Map(float cellSize, int width, int height)
    : cellSize(cellSize), grid(height, std::vector(width, sf::Color::Black)) {}

Map::Map(float cellSize, const std::string &filename)
    : cellSize(cellSize)
{
    sf::Image image;
    if (!image.loadFromFile(filename))
    {
        std::cerr << "Failed to load image file: " << filename << std::endl;
        return;
    }
    grid = std::vector(image.getSize().y, std::vector(image.getSize().x, sf::Color::Black));
    for (size_t y = 0; y < image.getSize().y; y++)
    {
        for (size_t x = 0; x < image.getSize().x; x++)
        {
            grid[y][x] = image.getPixel(x, y);
        }
    }
}

void Map::draw(sf::RenderTarget &target)
{
    if (grid.empty())
    {
        return;
    }

    sf::RectangleShape background(sf::Vector2f((float)grid[0].size() * cellSize, (float)grid.size() * cellSize));
    background.setFillColor(sf::Color::Green);
    target.draw(background);

    sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));

    for (std::size_t y = 0; y < grid.size(); y++)
    {
        for (std::size_t x = 0; x < grid[y].size(); x++)
        {
            cell.setFillColor(grid[y][x]);

            cell.setPosition(sf::Vector2f(x, y) * cellSize + sf::Vector2f(cellSize * 0.025f, cellSize * 0.025f));
            target.draw(cell);
        }
    }
}

const std::vector<std::vector<sf::Color>> &Map::getGrid() const
{
    return grid;
}
float Map::getCellSize() const
{
    return cellSize;
}