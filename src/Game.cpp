#include "../include/Game.hpp"
#include <iostream>
#include <algorithm>
static const int UI_MARGIN = 50;

Game::Game()
    : m_window(),
      m_windowWidth(1440),
      m_windowHeight(900),
      m_font(),
      m_zooName(),
      m_nameEntered(false),
      m_prompt(),
      m_inputText(),
      m_gridWidth(40),
      m_gridHeight(25),
      m_tileSize(0),
      m_grassTexture(),
      m_wallTexture(),
      m_tiles(),
      m_isBuildingHabitat(false),
      m_showHabitatOptions(false),
      m_selectedHabitatType(""),
      m_habitatTextures(),
      m_buildHabitatButton(),
      m_buildHabitatButtonText(),
      m_habitatOptionButtons(),
      m_habitatOptionTexts(),
      m_habitatBuildings()
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
    {
        sf::Texture temp;
        loadTexture(temp, "images/habitats/desertNormal.png", "../images/habitats/desertNormal.png",
                    sf::Color(210, 180, 140));
        m_habitatTextures["Desert"] = temp;
        loadTexture(temp, "images/habitats/forestNormal.png", "../images/habitats/forestNormal.png", sf::Color::Green);
        m_habitatTextures["Forest"] = temp;
        loadTexture(temp, "images/habitats/mountainNormal.png", "../images/habitats/mountainNormal.png",
                    sf::Color(169, 169, 169));
        m_habitatTextures["Mountain"] = temp;
        loadTexture(temp, "images/habitats/oceanNormal.png", "../images/habitats/oceanNormal.png", sf::Color::Blue);
        m_habitatTextures["Ocean"] = temp;
        loadTexture(temp, "images/habitats/savannaNormal.png", "../images/habitats/savannaNormal.png",
                    sf::Color(238, 232, 170));
        m_habitatTextures["Savanna"] = temp;
    }
    m_tileSize = std::min(m_windowWidth / int(m_gridWidth), (m_windowHeight - UI_MARGIN) / int(m_gridHeight));
    std::cout << "Grid: " << m_gridWidth << "x" << m_gridHeight << " | Tile size: " << m_tileSize << "px" << std::endl;
    m_tiles.resize(m_gridHeight, std::vector<sf::Sprite>(m_gridWidth));
    for (unsigned int y = 0; y < m_gridHeight; y++)
        for (unsigned int x = 0; x < m_gridWidth; x++)
        {
            bool isPerimeter = (x == 0 || y == 0 || x == m_gridWidth - 1 || y == m_gridHeight - 1);
            sf::Texture &tileTexture = isPerimeter ? m_wallTexture : m_grassTexture;
            sf::Vector2u textureSize = tileTexture.getSize();
            m_tiles[y][x].setTexture(tileTexture);
            m_tiles[y][x].setScale(float(m_tileSize) / textureSize.x, float(m_tileSize) / textureSize.y);
            m_tiles[y][x].setPosition(x * m_tileSize, y * m_tileSize);
        }
    int gridAreaHeight = m_gridHeight * m_tileSize;
    m_buildHabitatButton.setSize(sf::Vector2f(150, 40));
    m_buildHabitatButton.setFillColor(sf::Color(100, 100, 200));
    m_buildHabitatButton.setPosition(10, gridAreaHeight + (UI_MARGIN - m_buildHabitatButton.getSize().y) / 2);
    m_buildHabitatButtonText.setFont(m_font);
    m_buildHabitatButtonText.setCharacterSize(20);
    m_buildHabitatButtonText.setFillColor(sf::Color::White);
    m_buildHabitatButtonText.setString("Build Habitat");
    m_buildHabitatButtonText.setPosition(m_buildHabitatButton.getPosition().x + 10,
                                         m_buildHabitatButton.getPosition().y + 5);
    std::vector<std::string> options = {"Desert", "Forest", "Mountain", "Ocean", "Savanna"};
    float btnWidth = 120, btnHeight = 40;
    float startX = m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 10;
    float startY = gridAreaHeight + (UI_MARGIN - btnHeight) / 2;
    for (size_t i = 0; i < options.size(); i++)
    {
        sf::RectangleShape optionBtn;
        optionBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
        optionBtn.setFillColor(sf::Color(100, 200, 100));
        optionBtn.setPosition(startX + i * (btnWidth + 10), startY);
        m_habitatOptionButtons.push_back(optionBtn);
        sf::Text optionText;
        optionText.setFont(m_font);
        optionText.setCharacterSize(18);
        optionText.setFillColor(sf::Color::White);
        optionText.setString(options[i]);
        optionText.setPosition(optionBtn.getPosition().x + 10, optionBtn.getPosition().y + 5);
        m_habitatOptionTexts.push_back(optionText);
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
                    m_zooName += static_cast<char>(event.text.unicode);
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
        {
            m_window.close();
            return;
        }
        else if (event.type == sf::Event::Resized)
        {
            handleResize(event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            if (!m_isBuildingHabitat && !m_showHabitatOptions)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    m_showHabitatOptions = true;
            }
            else if (m_showHabitatOptions)
            {
                for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
                {
                    if (m_habitatOptionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        m_selectedHabitatType = m_habitatOptionTexts[i].getString();
                        m_isBuildingHabitat = true;
                        m_showHabitatOptions = false;
                        break;
                    }
                }
            }
            else if (m_isBuildingHabitat)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    m_isBuildingHabitat = false;
                    m_selectedHabitatType = "";
                    std::cout << "Habitat construction canceled." << std::endl;
                }
                else
                {
                    int cellX = mousePos.x / m_tileSize;
                    int cellY = mousePos.y / m_tileSize;
                    if (cellX >= 1 && cellY >= 1 && (cellX + 3) <= (int(m_gridWidth) - 1) && (cellY + 3) <= (
                            int(m_gridHeight) - 1))
                    {
                        sf::IntRect newRect(cellX, cellY, 3, 3);
                        bool canPlace = true;
                        for (auto &b: m_habitatBuildings)
                        {
                            int bx, by;
                            std::string type;
                            std::tie(bx, by, type) = b;
                            sf::IntRect existRect(bx, by, 3, 3);
                            if (newRect.intersects(existRect))
                            {
                                canPlace = false;
                                break;
                            }
                        }
                        if (canPlace)
                        {
                            m_habitatBuildings.push_back(std::make_tuple(cellX, cellY, m_selectedHabitatType));
                            m_selectedHabitatType = "";
                            m_isBuildingHabitat = false;
                        }
                        else
                            std::cout << "Cannot place habitat here: overlapping another habitat." << std::endl;
                    }
                }
            }
        }
    }
}

void Game::handleResize(unsigned int width, unsigned int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    sf::FloatRect visibleArea(0, 0, width, height);
    m_window.setView(sf::View(visibleArea));
    int newTileSize = std::min(int(width) / int(m_gridWidth), (int(height) - UI_MARGIN) / int(m_gridHeight));
    if (newTileSize != m_tileSize)
    {
        m_tileSize = newTileSize;
        for (unsigned int y = 0; y < m_gridHeight; y++)
            for (unsigned int x = 0; x < m_gridWidth; x++)
            {
                bool isPerimeter = (x == 0 || y == 0 || x == m_gridWidth - 1 || y == m_gridHeight - 1);
                sf::Texture &tileTexture = isPerimeter ? m_wallTexture : m_grassTexture;
                sf::Vector2u textureSize = tileTexture.getSize();
                m_tiles[y][x].setScale(float(m_tileSize) / textureSize.x, float(m_tileSize) / textureSize.y);
                m_tiles[y][x].setPosition(x * m_tileSize, y * m_tileSize);
            }
        int gridAreaHeight = m_gridHeight * m_tileSize;
        m_buildHabitatButton.setPosition(10, gridAreaHeight + (UI_MARGIN - m_buildHabitatButton.getSize().y) / 2);
        m_buildHabitatButtonText.setPosition(m_buildHabitatButton.getPosition().x + 10,
                                             m_buildHabitatButton.getPosition().y + 5);
        float btnWidth = 120, btnHeight = 40;
        float startX = m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 10;
        float startY = gridAreaHeight + (UI_MARGIN - btnHeight) / 2;
        for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
        {
            m_habitatOptionButtons[i].setSize(sf::Vector2f(btnWidth, btnHeight));
            m_habitatOptionButtons[i].setPosition(startX + i * (btnWidth + 10), startY);
            m_habitatOptionTexts[i].setPosition(m_habitatOptionButtons[i].getPosition().x + 10,
                                                m_habitatOptionButtons[i].getPosition().y + 5);
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

    for (auto &b: m_habitatBuildings)
    {
        int bx, by;
        std::string type;
        std::tie(bx, by, type) = b;
        if (m_habitatTextures.find(type) != m_habitatTextures.end())
        {
            sf::Sprite habitatSprite;
            habitatSprite.setTexture(m_habitatTextures[type]);
            sf::Vector2u texSize = m_habitatTextures[type].getSize();
            float scaleX = (3 * m_tileSize) / float(texSize.x);
            float scaleY = (3 * m_tileSize) / float(texSize.y);
            habitatSprite.setScale(scaleX, scaleY);
            habitatSprite.setPosition(bx * m_tileSize, by * m_tileSize);
            m_window.draw(habitatSprite);
        }
    }
    if (m_isBuildingHabitat)
    {
        m_buildHabitatButtonText.setString("Cancel Habitat");
        m_buildHabitatButton.setFillColor(sf::Color::Red);
    }
    else
    {
        m_buildHabitatButtonText.setString("Build Habitat");
        m_buildHabitatButton.setFillColor(sf::Color(100, 100, 200));
    }
    m_window.draw(m_buildHabitatButton);
    m_window.draw(m_buildHabitatButtonText);
    if (m_showHabitatOptions)
        for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
        {
            m_window.draw(m_habitatOptionButtons[i]);
            m_window.draw(m_habitatOptionTexts[i]);
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
