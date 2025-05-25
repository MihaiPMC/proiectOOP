#include "../include/Game.hpp"
#include "../include/exception/ZooExceptions.hpp"
#include "../include/exception/BudgetException.hpp"
#include "../include/exception/HabitatException.hpp"
#include "../include/exception/AnimalException.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
static const int UI_MARGIN = 50;

Game::Game()
    : m_window(),
      m_windowWidth(1440),
      m_windowHeight(1000),
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
      m_habitatBuildings(),
      m_addAnimalButton(),
      m_addAnimalButtonText(),
      m_isAddingAnimal(false),
      m_showAnimalOptionsForAnimal(false),
      m_statusMessage(),
      m_selectedHabitatIndex(-1),
      m_selectedAnimalType(""),
      m_animalOptionButtons(),
      m_animalOptionTexts(),
      m_animalTextures(),
      m_animalsInHabitat(),
      m_moveHabitatButton(),
      m_moveHabitatButtonText(),
      m_isMovingHabitat(false),
      m_movingHabitatIndex(-1),
      m_originalHabitatX(0),
      m_originalHabitatY(0),
      m_zoo("Default Zoo", {}, 0, true)
{
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Zoo Tycoon - Enter Zoo Name");
    if (!m_font.loadFromFile("fonts/DUSHICK.otf"))
        m_font.loadFromFile("../fonts/DUSHICK.otf");
    m_prompt.setFont(m_font);
    m_prompt.setCharacterSize(30);
    m_prompt.setFillColor(sf::Color::White);
    m_prompt.setString("Hello. Welcome to Zoo Tycoon. Please enter your zoo name:");
    m_inputText.setFont(m_font);
    m_inputText.setCharacterSize(40);
    m_inputText.setFillColor(sf::Color::Yellow);
    nameInput();
    showTutorial();
    if (m_zooName.empty())
        m_zooName = "ZooTycoon";
    m_window.setTitle(m_zooName);

    m_zoo.setName(m_zooName);

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
    m_addAnimalButton.setSize(sf::Vector2f(150, 40));
    m_addAnimalButton.setFillColor(sf::Color(100, 200, 100));
    m_addAnimalButton.setPosition(m_buildHabitatButton.getPosition().x,
                                  m_buildHabitatButton.getPosition().y + m_buildHabitatButton.getSize().y + 10);
    m_addAnimalButtonText.setFont(m_font);
    m_addAnimalButtonText.setCharacterSize(20);
    m_addAnimalButtonText.setFillColor(sf::Color::White);
    m_addAnimalButtonText.setString("Add Animal");
    m_addAnimalButtonText.setPosition(m_addAnimalButton.getPosition().x + 10, m_addAnimalButton.getPosition().y + 5);
    
    m_moveHabitatButton.setSize(sf::Vector2f(150, 40));
    m_moveHabitatButton.setFillColor(sf::Color(200, 100, 200));
    m_moveHabitatButton.setPosition(m_buildHabitatButton.getPosition().x,
                                  m_addAnimalButton.getPosition().y + m_addAnimalButton.getSize().y + 10);
    m_moveHabitatButtonText.setFont(m_font);
    m_moveHabitatButtonText.setCharacterSize(20);
    m_moveHabitatButtonText.setFillColor(sf::Color::White);
    m_moveHabitatButtonText.setString("Move Habitat");
    m_moveHabitatButtonText.setPosition(m_moveHabitatButton.getPosition().x + 10, m_moveHabitatButton.getPosition().y + 5);
    
    m_statusMessage.setFont(m_font);
    m_statusMessage.setCharacterSize(16);
    m_statusMessage.setFillColor(sf::Color::Yellow);
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
    if (m_zooName.empty())
        m_zooName = "ZooTycoon";

    if (!m_habitatBuildings.empty())
    {
        m_habitatBuildings.clear();
    }
    if (!m_animalsInHabitat.empty())
    {
        m_animalsInHabitat.clear();
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

void Game::showTutorial()
{
    sf::Text tutorial;
    tutorial.setFont(m_font);
    tutorial.setCharacterSize(24);
    tutorial.setFillColor(sf::Color::White);
    tutorial.setString(
        "Tutorial:\nClick 'Build Habitat' to construct a habitat,\nthen click 'Add Animal' to add animals.\nPress any key to continue.");
    tutorial.setPosition(m_windowWidth / 2.f - tutorial.getLocalBounds().width / 2.f, m_windowHeight / 3.f);

    bool tutorialDone = false;
    while (m_window.isOpen() && !tutorialDone)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                tutorialDone = true;
            }
        }
        m_window.clear(sf::Color(50, 50, 50));
        m_window.draw(tutorial);
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
            if (m_isAddingAnimal && m_addAnimalButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                m_isAddingAnimal = false;
                m_selectedHabitatIndex = -1;
                m_selectedAnimalType = "";
                m_animalOptionButtons.clear();
                m_animalOptionTexts.clear();
                std::cout << "Animal addition canceled." << std::endl;
                continue;
            }
            else if (!m_isAddingAnimal && !m_isMovingHabitat && m_addAnimalButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                m_isAddingAnimal = true;
                m_selectedHabitatIndex = -1;
                m_showAnimalOptionsForAnimal = false;
                m_animalOptionButtons.clear();
                m_animalOptionTexts.clear();
            }
            else if (m_isMovingHabitat && m_moveHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                m_isMovingHabitat = false;
                m_movingHabitatIndex = -1;
                std::cout << "Habitat move canceled." << std::endl;
                continue;
            }
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && m_moveHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                m_isMovingHabitat = true;
                m_movingHabitatIndex = -1;
                std::cout << "Select a habitat to move." << std::endl;
            }
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && !m_isMovingHabitat)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    m_showHabitatOptions = true;
            }
            else if (m_showHabitatOptions)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    m_showHabitatOptions = false;
                    std::cout << "Habitat selection cancelled." << std::endl;
                }
                else
                {
                    for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
                    {
                        if (m_habitatOptionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            m_selectedHabitatType = m_habitatOptionTexts[i].getString();
                            m_isBuildingHabitat = true;
                            m_showHabitatOptions = false;
                            std::cout << "Selected habitat type: " << m_selectedHabitatType << std::endl;
                            break;
                        }
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
            
                    try {
                        if (m_zoo.buildHabitatAt(m_selectedHabitatType, cellX, cellY, m_gridWidth, m_gridHeight))
                        {
                            std::string builtType = m_selectedHabitatType;
                            m_habitatBuildings.push_back(std::make_tuple(cellX, cellY, m_selectedHabitatType));
                            m_animalsInHabitat.push_back({});
                            m_selectedHabitatType = "";
                            m_isBuildingHabitat = false;
                            std::cout << "Successfully built " << builtType << " habitat at position (" 
                                      << cellX << "," << cellY << ")" << std::endl;
                        }
                    }
                    catch (const HabitatException& e) {
                        std::cout << e.what() << std::endl;
                    }
                    catch (const BudgetException& e) {
                        std::cout << e.what() << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                }
            }
            else if (m_isMovingHabitat)
            {
                if (m_movingHabitatIndex == -1)
                {
                    int gridX = mousePos.x / m_tileSize;
                    int gridY = mousePos.y / m_tileSize;
                    
                    for (size_t i = 0; i < m_habitatBuildings.size(); i++)
                    {
                        int hx, hy;
                        std::string type;
                        std::tie(hx, hy, type) = m_habitatBuildings[i];
                        
                        if (gridX >= hx && gridX < hx + 3 && gridY >= hy && gridY < hy + 3)
                        {
                            m_movingHabitatIndex = i;
                            m_originalHabitatX = hx;
                            m_originalHabitatY = hy;
                            std::cout << "Selected habitat at (" << hx << "," << hy << ") for moving." << std::endl;
                            break;
                        }
                    }
                }
                else
                {
                    int newX = mousePos.x / m_tileSize;
                    int newY = mousePos.y / m_tileSize;
                    
                    bool isValidPosition = true;
                    
                    if (newX < 1 || newY < 1 || newX + 2 >= static_cast<int>(m_gridWidth) - 1 || newY + 2 >= static_cast<int>(m_gridHeight) - 1)
                    {
                        isValidPosition = false;
                    }
                    
                    if (isValidPosition)
                    {
                        for (size_t i = 0; i < m_habitatBuildings.size(); i++)
                        {
                            if (static_cast<int>(i) == m_movingHabitatIndex) 
                                continue;
                            int hx, hy;
                            std::tie(hx, hy, std::ignore) = m_habitatBuildings[i];
                            
                            bool overlapsX = (newX < hx + 3) && (newX + 3 > hx);
                            bool overlapsY = (newY < hy + 3) && (newY + 3 > hy);
                            
                            if (overlapsX && overlapsY)
                            {
                                isValidPosition = false;
                                break;
                            }
                        }
                    }
                    
                    if (isValidPosition)
                    {
                        int oldX, oldY;
                        std::string type;
                        std::tie(oldX, oldY, type) = m_habitatBuildings[m_movingHabitatIndex];
                        
                        m_habitatBuildings[m_movingHabitatIndex] = std::make_tuple(newX, newY, type);
                        
                        if (m_movingHabitatIndex >= 0 && static_cast<size_t>(m_movingHabitatIndex) < m_zoo.getHabitats().size()) {
                            m_zoo.moveHabitat(static_cast<size_t>(m_movingHabitatIndex), newX, newY);
                        }
                        
                        std::cout << "Moved habitat from (" << oldX << "," << oldY << ") to (" 
                                << newX << "," << newY << ")" << std::endl;
                        
                        m_isMovingHabitat = false;
                        m_movingHabitatIndex = -1;
                    }
                    else
                    {
                        std::cout << "Cannot place habitat at (" << newX << "," << newY 
                                << ") - invalid position" << std::endl;
                    }
                }
            }
            else if (m_isAddingAnimal)
            {
                if (m_selectedHabitatIndex == -1)
                {
                    int gridX = mousePos.x / m_tileSize;
                    int gridY = mousePos.y / m_tileSize;
                    
                    int habitatIndex = m_zoo.findHabitatAt(gridX, gridY);
                    
                    if (habitatIndex != -1)
                    {
                        m_selectedHabitatIndex = habitatIndex;
                        
                        std::string type;
                        if (habitatIndex < static_cast<int>(m_habitatBuildings.size())) {
                            std::tie(std::ignore, std::ignore, type) = m_habitatBuildings[habitatIndex];
                        } else {
                            type = m_zoo.getHabitats()[habitatIndex].getType();
                        }
                        
                        std::vector<std::string> allowed = Habitat::getAllowedAnimals(type);
            
                        m_animalOptionButtons.clear();
                        m_animalOptionTexts.clear();
            
                        float optWidth = 120, optHeight = 40;
                        float optStartX = m_addAnimalButton.getPosition().x + m_addAnimalButton.getSize().x + 10;
                        float optStartY = m_addAnimalButton.getPosition().y;
            
                        for (size_t j = 0; j < allowed.size(); j++)
                        {
                            sf::RectangleShape btn;
                            btn.setSize(sf::Vector2f(optWidth, optHeight));
                            btn.setFillColor(sf::Color(200, 200, 100));
                            btn.setPosition(optStartX + j * (optWidth + 10), optStartY);
                            m_animalOptionButtons.push_back(btn);
            
                            sf::Text txt;
                            txt.setFont(m_font);
                            txt.setCharacterSize(18);
                            txt.setFillColor(sf::Color::Black);
                            txt.setString(allowed[j]);
                            txt.setPosition(btn.getPosition().x + 10, btn.getPosition().y + 5);
                            m_animalOptionTexts.push_back(txt);
            
                            if (m_animalTextures.find(allowed[j]) == m_animalTextures.end())
                            {
                                std::string lowerType;
                                for (char ch: type) lowerType.push_back(std::tolower(ch));
                                std::stringstream ss;
                                ss << "images/" << lowerType << "/" << allowed[j] << ".png";
                                std::string primaryPath = ss.str();
                                std::string backupPath = "../" + primaryPath;
                                sf::Texture tex;
                                loadTexture(tex, primaryPath, backupPath, sf::Color::Magenta);
                                m_animalTextures[allowed[j]] = tex;
                            }
                        }
                        m_showAnimalOptionsForAnimal = true;
                    }
                }
                else if (m_showAnimalOptionsForAnimal)
                {
                    for (size_t i = 0; i < m_animalOptionButtons.size(); i++)
                    {
                        if (m_animalOptionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            m_selectedAnimalType = m_animalOptionTexts[i].getString();

                            try {
                                if (m_zoo.addAnimalTo(m_selectedHabitatIndex, m_selectedAnimalType))
                                {
                                    m_animalsInHabitat[m_selectedHabitatIndex].push_back(m_selectedAnimalType);
                                }
                            }
                            catch (const HabitatException& e) {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const AnimalException& e) {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const BudgetException& e) {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const std::exception& e) {
                                std::cout << "Error: " << e.what() << std::endl;
                            }

                            m_isAddingAnimal = false;
                            m_showAnimalOptionsForAnimal = false;
                            m_selectedHabitatIndex = -1;
                            m_animalOptionButtons.clear();
                            m_animalOptionTexts.clear();
                            break;
                        }
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
        m_addAnimalButton.setPosition(m_buildHabitatButton.getPosition().x,
                                      m_buildHabitatButton.getPosition().y + m_buildHabitatButton.getSize().y + 10);
        m_addAnimalButtonText.setPosition(m_addAnimalButton.getPosition().x + 10,
                                          m_addAnimalButton.getPosition().y + 5);
        m_moveHabitatButton.setPosition(m_buildHabitatButton.getPosition().x,
                                      m_addAnimalButton.getPosition().y + m_addAnimalButton.getSize().y + 10);
        m_moveHabitatButtonText.setPosition(m_moveHabitatButton.getPosition().x + 10,
                                          m_moveHabitatButton.getPosition().y + 5);
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
        if (m_showAnimalOptionsForAnimal)
        {
            float optWidth = 120, optHeight = 40;
            float optStartX = m_addAnimalButton.getPosition().x + m_addAnimalButton.getSize().x + 10;
            float optStartY = m_addAnimalButton.getPosition().y;
            for (size_t i = 0; i < m_animalOptionButtons.size(); i++)
            {
                m_animalOptionButtons[i].setSize(sf::Vector2f(optWidth, optHeight));
                m_animalOptionButtons[i].setPosition(optStartX + i * (optWidth + 10), optStartY);
                m_animalOptionTexts[i].setPosition(m_animalOptionButtons[i].getPosition().x + 10,
                                                   m_animalOptionButtons[i].getPosition().y + 5);
            }
        }
    }
}

void Game::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    
    if (m_isMovingHabitat) {
        if (m_movingHabitatIndex == -1) {
            m_statusMessage.setString("Select a habitat to move");
        } else {
            int newX = mousePos.x / m_tileSize;
            int newY = mousePos.y / m_tileSize;
            
            m_statusMessage.setString("Moving habitat to: (" + std::to_string(newX) + 
                                     "," + std::to_string(newY) + ") - Click to place");
        }
        m_statusMessage.setPosition(10, m_windowHeight - 30);
    }
    else if (m_isBuildingHabitat) {
        int cellX = mousePos.x / m_tileSize;
        int cellY = mousePos.y / m_tileSize;
        
        m_statusMessage.setString("Building: " + m_selectedHabitatType + 
                                 " | Grid position: (" + std::to_string(cellX) + 
                                 "," + std::to_string(cellY) + ")");
        m_statusMessage.setPosition(10, m_windowHeight - 30);
    }
    else {
        m_statusMessage.setString("");
    }
}

void Game::render()
{
    m_window.clear(sf::Color(50, 50, 50));
    for (unsigned int y = 0; y < m_gridHeight; y++)
    {
        for (unsigned int x = 0; x < m_gridWidth; x++)
        {
            m_window.draw(m_tiles[y][x]);

            if (m_isBuildingHabitat) {
                if (x >= 1 && y >= 1 && x + 2 < m_gridWidth - 1 && y + 2 < m_gridHeight - 1) {
                    bool isValid = true;

                    for (const auto& habitat : m_habitatBuildings) {
                        int hx = std::get<0>(habitat);
                        int hy = std::get<1>(habitat);

                        bool overlapsX = (static_cast<int>(x) < hx + 3) && (static_cast<int>(x) + 3 > hx);
                        bool overlapsY = (static_cast<int>(y) < hy + 3) && (static_cast<int>(y) + 3 > hy);
                        
                        if (overlapsX && overlapsY) {
                            isValid = false;
                            break;
                        }
                    }
                    
                    if (isValid) {
                        sf::RectangleShape highlight;
                        highlight.setSize(sf::Vector2f(m_tileSize, m_tileSize));
                        highlight.setPosition(x * m_tileSize, y * m_tileSize);
                        highlight.setFillColor(sf::Color(0, 255, 0, 40));
                        m_window.draw(highlight);
                    }
                }
            }
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
    for (size_t i = 0; i < m_habitatBuildings.size(); i++)
    {
        int bx, by;
        std::string type;
        std::tie(bx, by, type) = m_habitatBuildings[i];
        float habitatX = bx * m_tileSize;
        float habitatY = by * m_tileSize;
        float habitatWidth = 3 * m_tileSize;
        float habitatHeight = 3 * m_tileSize;
        int animalCount = m_animalsInHabitat[i].size();
        for (int j = 0; j < animalCount; j++)
        {
            const std::string &animal = m_animalsInHabitat[i][j];
            if (m_animalTextures.find(animal) != m_animalTextures.end())
            {
                sf::Sprite animalSprite;
                animalSprite.setTexture(m_animalTextures[animal]);
                sf::Vector2u texSize = m_animalTextures[animal].getSize();
                float factor = 0.03f;
                animalSprite.setScale(factor, factor);
                int scaledWidth = int(texSize.x * factor);
                int scaledHeight = int(texSize.y * factor);
                int maxOffsetX = std::max(0, int(habitatWidth) - scaledWidth);
                int maxOffsetY = std::max(0, int(habitatHeight) - scaledHeight);
                std::hash<std::string> hasher;
                std::string key = std::to_string(i) + "_" + std::to_string(j);
                size_t hashVal = hasher(key);
                int offsetX = hashVal % (maxOffsetX + 1);
                int offsetY = (hashVal / 100) % (maxOffsetY + 1);
                animalSprite.setPosition(habitatX + offsetX, habitatY + offsetY);
                m_window.draw(animalSprite);
            }
        }
    }
    if (m_isBuildingHabitat)
    {
        m_buildHabitatButtonText.setString("Cancel Habitat");
        m_buildHabitatButton.setFillColor(sf::Color::Red);
        
        sf::Text statusText;
        statusText.setFont(m_font);
        statusText.setCharacterSize(16);
        statusText.setFillColor(sf::Color::Yellow);
        statusText.setString("Click to place " + m_selectedHabitatType + " habitat (or click Cancel)");
        statusText.setPosition(m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 20, 
                              m_buildHabitatButton.getPosition().y + 10);
        m_window.draw(statusText);
    }
    else if (m_showHabitatOptions)
    {
        m_buildHabitatButtonText.setString("Cancel");
        m_buildHabitatButton.setFillColor(sf::Color::Red);
    }
    else
    {
        m_buildHabitatButtonText.setString("Build Habitat");
        m_buildHabitatButton.setFillColor(sf::Color(100, 100, 200));
    }
    if (m_isAddingAnimal)
    {
        m_addAnimalButtonText.setString("Cancel ");
        m_addAnimalButton.setFillColor(sf::Color::Red);
    }
    else
    {
        m_addAnimalButtonText.setString("Add Animal");
        m_addAnimalButton.setFillColor(sf::Color(100, 200, 100));
    }
    
    if (m_isMovingHabitat)
    {
        m_moveHabitatButtonText.setString("Cancel Move");
        m_moveHabitatButton.setFillColor(sf::Color::Red);
        
        sf::Text moveStatusText;
        moveStatusText.setFont(m_font);
        moveStatusText.setCharacterSize(16);
        moveStatusText.setFillColor(sf::Color::Yellow);
        
        if (m_movingHabitatIndex == -1) {
            moveStatusText.setString("Select a habitat to move");
        } else {
            moveStatusText.setString("Click on a new location for the habitat");
            
            int hx, hy;
            std::tie(hx, hy, std::ignore) = m_habitatBuildings[m_movingHabitatIndex];
            
            sf::RectangleShape moveHighlight;
            moveHighlight.setSize(sf::Vector2f(3 * m_tileSize, 3 * m_tileSize));
            moveHighlight.setPosition(hx * m_tileSize, hy * m_tileSize);
            moveHighlight.setFillColor(sf::Color(255, 165, 0, 80));
            moveHighlight.setOutlineColor(sf::Color::Yellow);
            moveHighlight.setOutlineThickness(2);
            m_window.draw(moveHighlight);
            
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            int newX = mousePos.x / m_tileSize;
            int newY = mousePos.y / m_tileSize;
            
            newX = std::max(1, std::min(newX, static_cast<int>(m_gridWidth) - 4));
            newY = std::max(1, std::min(newY, static_cast<int>(m_gridHeight) - 4));
            
            bool isValidPosition = true;
            
            for (size_t i = 0; i < m_habitatBuildings.size(); i++)
            {
                if (static_cast<int>(i) == m_movingHabitatIndex) continue;
                
                int otherX, otherY;
                std::tie(otherX, otherY, std::ignore) = m_habitatBuildings[i];
                
                bool overlapsX = (newX < otherX + 3) && (newX + 3 > otherX);
                bool overlapsY = (newY < otherY + 3) && (newY + 3 > otherY);
                
                if (overlapsX && overlapsY)
                {
                    isValidPosition = false;
                    break;
                }
            }
            
            sf::RectangleShape newPositionPreview;
            newPositionPreview.setSize(sf::Vector2f(3 * m_tileSize, 3 * m_tileSize));
            newPositionPreview.setPosition(newX * m_tileSize, newY * m_tileSize);
            
            if (isValidPosition) {
                newPositionPreview.setFillColor(sf::Color(0, 255, 0, 80));
                newPositionPreview.setOutlineColor(sf::Color::Green);
            } else {
                newPositionPreview.setFillColor(sf::Color(255, 0, 0, 80));
                newPositionPreview.setOutlineColor(sf::Color::Red);
            }
            
            newPositionPreview.setOutlineThickness(2);
            m_window.draw(newPositionPreview);
        }
        
        moveStatusText.setPosition(m_moveHabitatButton.getPosition().x + m_moveHabitatButton.getSize().x + 20,
                                 m_moveHabitatButton.getPosition().y + 10);
        m_window.draw(moveStatusText);
    }
    else
    {
        m_moveHabitatButtonText.setString("Move Habitat");
        m_moveHabitatButton.setFillColor(sf::Color(200, 100, 200));
    }
    
    m_window.draw(m_buildHabitatButton);
    m_window.draw(m_buildHabitatButtonText);
    m_window.draw(m_addAnimalButton);
    m_window.draw(m_addAnimalButtonText);
    m_window.draw(m_moveHabitatButton);
    m_window.draw(m_moveHabitatButtonText);
    if (m_showHabitatOptions)
        for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
        {
            m_window.draw(m_habitatOptionButtons[i]);
            m_window.draw(m_habitatOptionTexts[i]);
        }
    if (m_showAnimalOptionsForAnimal)
        for (size_t i = 0; i < m_animalOptionButtons.size(); i++)
        {
            m_window.draw(m_animalOptionButtons[i]);
            m_window.draw(m_animalOptionTexts[i]);
        }

    sf::Text budgetText;
    budgetText.setFont(m_font);
    budgetText.setCharacterSize(20);
    budgetText.setFillColor(sf::Color::White);
    budgetText.setString("Budget: $" + std::to_string(static_cast<int>(m_zoo.getBudget())));
    budgetText.setPosition(m_windowWidth - 200, m_gridHeight * m_tileSize + 10);
    m_window.draw(budgetText);

    if (!m_statusMessage.getString().isEmpty()) {
        m_window.draw(m_statusMessage);
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

