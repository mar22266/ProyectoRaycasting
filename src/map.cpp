#include "../include/map.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ios>

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}
Map::Map(float cellSize, int width, int height)
    : cellSize(cellSize), grid(height, std::vector(width, 0)) {}

Map::Map(float cellSize, const std::string &filename)
    : cellSize(cellSize)
{
    sf::Image image;
    if (!image.loadFromFile(filename))
    {
        std::cerr << "Failed to load image file: " << filename << std::endl;
        return;
    }
    grid = std::vector(image.getSize().y, std::vector(image.getSize().x, 0));
    for (size_t y = 0; y < image.getSize().y; y++)
    {
        for (size_t x = 0; x < image.getSize().x; x++)
        {
            grid[y][x] = image.getPixel(x, y) == sf::Color::Black ? 0 : 1;
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
    background.setFillColor(sf::Color::Yellow);
    target.draw(background);

    sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));

    for (std::size_t y = 0; y < grid.size(); y++)
    {
        for (std::size_t x = 0; x < grid[y].size(); x++)
        {
            cell.setFillColor(grid[y][x] ? sf::Color::White : sf::Color::Black);

            cell.setPosition(sf::Vector2f(x, y) * cellSize + sf::Vector2f(cellSize * 0.025f, cellSize * 0.025f));
            target.draw(cell);
        }
    }
}

void Map::setMapCell(int x, int y, int value)
{
    if (y >= 0 && y < grid.size() && x >= 0 && x < grid[y].size())
    {
        grid[y][x] = value;
    }
}

void Map::load(const std::filesystem::path &path)
{
    std::ifstream in{path, std::ios::in | std::ios::binary};
    if (!in.is_open())
    {
        std::cerr << "Failed to open file : " << path << "for input\n";
    }

    size_t w, h;

    in.read(reinterpret_cast<char *>(&w), sizeof(w));
    in.read(reinterpret_cast<char *>(&h), sizeof(h));

    grid = std::vector(h, std::vector(w, 0));
    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size(); x++)
        {
            in.read(reinterpret_cast<char *>(&grid[y][x]), sizeof(grid[y][x]));
        }
    }
}

void Map::save(const std::filesystem::path &path)
{
    std::ofstream out{path, std::ios::out | std::ios::binary};
    if (!out.is_open())
    {
        std::cerr << "Failed to open file : " << path << "for outpu\n";
    }

    if (grid.empty())
    {
        return;
    }
    size_t w = grid.size();
    size_t h = grid[0].size();
    out.write(reinterpret_cast<const char *>(&w), sizeof(w));
    out.write(reinterpret_cast<const char *>(&h), sizeof(h));
    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size(); x++)
        {
            out.write(reinterpret_cast<const char *>(&grid[y][x]), sizeof(grid[y][x]));
        }
    }
}

const MapGrid &Map::getGrid() const
{
    return grid;
}
float Map::getCellSize() const
{
    return cellSize;
}