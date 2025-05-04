#include "../include/Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game()
    : m_windowWidth(1440), m_windowHeight(900),
      m_gridWidth(40), m_gridHeight(25),
      m_nameEntered(false)
{
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Zoo Tycoon - Enter Zoo Name");
    if (!m_font.loadFromFile("fonts/DUSHICK.otf"))
        m_font.loadFromFile("../fonts/DUSHICK.otf");
    m_prompt.setFont(m_font);
    m_prompt.setCharacterSize(30);
    m_prompt.setFillColor(sf::Color::White);
    m_prompt.setString("Enter Zoo Name:");
    m_inputText.setFont(m_font);
    m_inputText.setCharacterSize(40);
    m_inputText.setFillColor(sf::Color::Yellow);
    nameInput();
    if (m_zooName.empty())
        m_zooName = "ZooTycoon";
    m_window.setTitle(m_zooName);
    loadTexture(m_grassTexture, "images/grass.png", "../images/grass.png", sf::Color::Green);
    loadTexture(m_wallTexture, "images/wall.png", "../images/wall.png", sf::Color(139, 69, 19));
    m_tileSize = std::min(m_windowWidth / int(m_gridWidth), m_windowHeight / int(m_gridHeight));
    std::cout << "Grid: " << m_gridWidth << "x" << m_gridHeight << " | Tile size: " << m_tileSize << "px" << std::endl;
    m_tiles.resize(m_gridHeight, std::vector<sf::Sprite>(m_gridWidth));
    for (unsigned int y = 0; y < m_gridHeight; y++)
    {
        for (unsigned int x = 0; x < m_gridWidth; x++)
        {
            bool isPerimeter = (x == 0 || y == 0 || x == m_gridWidth - 1 || y == m_gridHeight - 1);
            sf::Texture &tileTexture = isPerimeter ? m_wallTexture : m_grassTexture;
            sf::Vector2u textureSize = tileTexture.getSize();
            m_tiles[y][x].setTexture(tileTexture);
            m_tiles[y][x].setScale(float(m_tileSize) / textureSize.x, float(m_tileSize) / textureSize.y);
            m_tiles[y][x].setPosition(x * m_tileSize, y * m_tileSize);
        }
    }
}

bool Game::loadTexture(sf::Texture &texture, const std::string &primaryPath, const std::string &backupPath,
                       sf::Color fallbackColor)
{
    if (texture.loadFromFile(primaryPath))
    {
        std::cout << "Loaded texture from " << primaryPath << std::endl;
        return true;
    }
    if (texture.loadFromFile(backupPath))
    {
        std::cout << "Loaded texture from " << backupPath << std::endl;
        return true;
    }
    sf::Image fallbackImage;
    fallbackImage.create(64, 64, fallbackColor);
    texture.loadFromImage(fallbackImage);
    std::cout << "Using fallback texture" << std::endl;
    return false;
}

void Game::nameInput()
{
    while (m_window.isOpen() && !m_nameEntered)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return;
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (!m_zooName.empty())
                        m_zooName.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != 13)
                {
                    m_zooName += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (!m_zooName.empty())
                    m_nameEntered = true;
            }
        }
        m_inputText.setString(m_zooName);
        m_prompt.setPosition(m_windowWidth / 2.f - m_prompt.getLocalBounds().width / 2.f, m_windowHeight / 3.f);
        m_inputText.setPosition(m_windowWidth / 2.f - m_inputText.getLocalBounds().width / 2.f, m_windowHeight / 2.f);
        m_window.clear(sf::Color(50, 50, 50));
        m_window.draw(m_prompt);
        m_window.draw(m_inputText);
        m_window.display();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
        else if (event.type == sf::Event::Resized)
            handleResize(event.size.width, event.size.height);
    }
}

void Game::handleResize(unsigned int width, unsigned int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    sf::FloatRect visibleArea(0, 0, width, height);
    m_window.setView(sf::View(visibleArea));
    int newTileSize = std::min(int(width) / int(m_gridWidth), int(height) / int(m_gridHeight));
    if (newTileSize != m_tileSize)
    {
        m_tileSize = newTileSize;
        for (unsigned int y = 0; y < m_gridHeight; y++)
        {
            for (unsigned int x = 0; x < m_gridWidth; x++)
            {
                bool isPerimeter = (x == 0 || y == 0 || x == m_gridWidth - 1 || y == m_gridHeight - 1);
                sf::Texture &tileTexture = isPerimeter ? m_wallTexture : m_grassTexture;
                sf::Vector2u textureSize = tileTexture.getSize();
                m_tiles[y][x].setScale(float(m_tileSize) / textureSize.x, float(m_tileSize) / textureSize.y);
                m_tiles[y][x].setPosition(x * m_tileSize, y * m_tileSize);
            }
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    m_window.clear(sf::Color(50, 50, 50));
    for (unsigned int y = 0; y < m_gridHeight; y++)
    {
        for (unsigned int x = 0; x < m_gridWidth; x++)
        {
            m_window.draw(m_tiles[y][x]);
        }
    }
    m_window.display();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}
