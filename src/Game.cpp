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

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game()
    : m_window(),
      m_windowWidth(1800),
      m_windowHeight(1350),
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
      m_buildPathButton(),
      m_buildPathButtonText(),
      m_isBuildingPath(false),
      m_pathTexture(),
      m_pathTiles(),
      m_lastPathX(-1),
      m_lastPathY(-1),
      m_deleteButton(),
      m_deleteButtonText(),
      m_isDeletingObject(false),
      m_deletingObjectIndex(-1),
      m_zoo("Default Zoo", {}, 0, true),
      m_showingInventory(false),
      m_inventoryBackground(),
      m_inventoryTexts()
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

    Zoo::nameInput(m_window, m_font, m_zooName, m_nameEntered);
    Zoo::showTutorial(m_window, m_font);

    if (m_zooName.empty())
        m_zooName = "ZooTycoon";
    m_window.setTitle(m_zooName);

    m_zoo.setName(m_zooName);

    Zoo::loadTexture(m_grassTexture, "images/grass.png", "../images/grass.png", sf::Color::Green);
    Zoo::loadTexture(m_wallTexture, "images/wall.png", "../images/wall.png", sf::Color(139, 69, 19));
    {
        sf::Texture temp;
        Zoo::loadTexture(temp, "images/habitats/desertNormal.png", "../images/habitats/desertNormal.png",
                    sf::Color(210, 180, 140));
        m_habitatTextures["Desert"] = temp;
        Zoo::loadTexture(temp, "images/habitats/forestNormal.png", "../images/habitats/forestNormal.png", sf::Color::Green);
        m_habitatTextures["Forest"] = temp;
        Zoo::loadTexture(temp, "images/habitats/mountainNormal.png", "../images/habitats/mountainNormal.png",
                    sf::Color(169, 169, 169));
        m_habitatTextures["Mountain"] = temp;
        Zoo::loadTexture(temp, "images/habitats/oceanNormal.png", "../images/habitats/oceanNormal.png", sf::Color::Blue);
        m_habitatTextures["Ocean"] = temp;
        Zoo::loadTexture(temp, "images/habitats/savannaNormal.png", "../images/habitats/savannaNormal.png",
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
    // Ensure show inventory button is always positioned properly
    if (m_showInventoryButton.getSize().x > 0) {
        m_showInventoryButton.setPosition(m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 20, 
                                        gridAreaHeight + (UI_MARGIN - m_showInventoryButton.getSize().y) / 2);
    }
    m_buildHabitatButtonText.setFont(m_font);
    m_buildHabitatButtonText.setCharacterSize(20);
    m_buildHabitatButtonText.setFillColor(sf::Color::White);
    m_buildHabitatButtonText.setString("Build Habitat");
    m_buildHabitatButtonText.setPosition(m_buildHabitatButton.getPosition().x + 10,
                                         m_buildHabitatButton.getPosition().y + 5);
    m_addAnimalButton.setSize(sf::Vector2f(150, 40));
    m_addAnimalButton.setFillColor(sf::Color(100, 200, 100));
    m_addAnimalButton.setPosition(m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 10,
                                  m_buildHabitatButton.getPosition().y);
    m_addAnimalButtonText.setFont(m_font);
    m_addAnimalButtonText.setCharacterSize(20);
    m_addAnimalButtonText.setFillColor(sf::Color::White);
    m_addAnimalButtonText.setString("Add Animal");
    m_addAnimalButtonText.setPosition(m_addAnimalButton.getPosition().x + 10, m_addAnimalButton.getPosition().y + 5);

    m_moveHabitatButton.setSize(sf::Vector2f(150, 40));
    m_moveHabitatButton.setFillColor(sf::Color(200, 100, 200));
    m_moveHabitatButton.setPosition(m_addAnimalButton.getPosition().x + m_addAnimalButton.getSize().x + 10,
                                    m_buildHabitatButton.getPosition().y);
    m_moveHabitatButtonText.setFont(m_font);
    m_moveHabitatButtonText.setCharacterSize(20);
    m_moveHabitatButtonText.setFillColor(sf::Color::White);
    m_moveHabitatButtonText.setString("Move Habitat");
    m_moveHabitatButtonText.setPosition(m_moveHabitatButton.getPosition().x + 10,
                                        m_moveHabitatButton.getPosition().y + 5);

    m_buildPathButton.setSize(sf::Vector2f(150, 40));
    m_buildPathButton.setFillColor(sf::Color(153, 102, 51));
    m_buildPathButton.setPosition(m_moveHabitatButton.getPosition().x + m_moveHabitatButton.getSize().x + 10,
                                  m_buildHabitatButton.getPosition().y);
    m_buildPathButtonText.setFont(m_font);
    m_buildPathButtonText.setCharacterSize(20);
    m_buildPathButtonText.setFillColor(sf::Color::White);
    m_buildPathButtonText.setString("Build Path");
    m_buildPathButtonText.setPosition(m_buildPathButton.getPosition().x + 10,
                                      m_buildPathButton.getPosition().y + 5);

    m_deleteButton.setSize(sf::Vector2f(150, 40));
    m_deleteButton.setFillColor(sf::Color(200, 0, 0));
    m_deleteButton.setPosition(m_buildPathButton.getPosition().x + m_buildPathButton.getSize().x + 10,
                               m_buildHabitatButton.getPosition().y);
    m_deleteButtonText.setFont(m_font);
    m_deleteButtonText.setCharacterSize(20);
    m_deleteButtonText.setFillColor(sf::Color::White);
    m_deleteButtonText.setString("Delete");
    m_deleteButtonText.setPosition(m_deleteButton.getPosition().x + 10,
                                   m_deleteButton.getPosition().y + 5);
    m_isDeletingObject = false;
    m_deletingObjectIndex = -1;

    // Initialize show inventory button
    m_showInventoryButton.setSize(sf::Vector2f(150, 40));
    m_showInventoryButton.setFillColor(sf::Color(0, 100, 150));
    m_showInventoryButton.setOutlineColor(sf::Color::Black);
    m_showInventoryButton.setOutlineThickness(2);
    m_showInventoryButton.setPosition(m_deleteButton.getPosition().x + m_deleteButton.getSize().x + 10,
                                     m_buildHabitatButton.getPosition().y);

    // Initialize show inventory button text
    m_showInventoryButtonText.setFont(m_font);
    m_showInventoryButtonText.setString("Show Inventory");
    m_showInventoryButtonText.setCharacterSize(16);
    m_showInventoryButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = m_showInventoryButtonText.getLocalBounds();
    m_showInventoryButtonText.setPosition(
        m_showInventoryButton.getPosition().x + (m_showInventoryButton.getSize().x - textBounds.width) / 2,
        m_showInventoryButton.getPosition().y + (m_showInventoryButton.getSize().y - textBounds.height) / 2 - 5
    );

    m_inventoryBackground.setFillColor(sf::Color(0, 0, 0, 200));
    m_inventoryBackground.setOutlineColor(sf::Color::White);
    m_inventoryBackground.setOutlineThickness(2);

    loadTexture(m_pathTexture, "images/path.png", "../images/path.png", sf::Color(153, 102, 51));

    m_statusMessage.setFont(m_font);
    m_statusMessage.setCharacterSize(16);
    m_statusMessage.setFillColor(sf::Color::Yellow);
    std::vector<std::string> options = {"Desert", "Forest", "Mountain", "Ocean", "Savanna"};
    float btnWidth = 120, btnHeight = 40;
    float startX = m_buildHabitatButton.getPosition().x;
    float startY = m_buildHabitatButton.getPosition().y + m_buildHabitatButton.getSize().y + 10;
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

        sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        if (m_showInventoryButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            m_showingInventory = !m_showingInventory;
            if (m_showingInventory) {
                prepareInventoryDisplay();
                m_statusMessage.setString("Showing inventory");
                m_statusMessage.setFillColor(sf::Color::Green);
            } else {
                m_statusMessage.setString("");
            }
            return;
        }
        else if (event.type == sf::Event::Resized)
        {
            handleResize(event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
            if (m_isAddingAnimal && m_addAnimalButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                m_isAddingAnimal = false;
                m_selectedHabitatIndex = -1;
                m_selectedAnimalType = "";
                m_animalOptionButtons.clear();
                m_animalOptionTexts.clear();
                std::cout << "Animal addition canceled." << std::endl;
                continue;
            }
            else if (!m_isAddingAnimal && !m_isMovingHabitat && m_addAnimalButton.getGlobalBounds().contains(
                         mousePosition.x, mousePosition.y))
            {
                m_isAddingAnimal = true;
                m_selectedHabitatIndex = -1;
                m_showAnimalOptionsForAnimal = false;
                m_animalOptionButtons.clear();
                m_animalOptionTexts.clear();
            }
            else if (m_isMovingHabitat && m_moveHabitatButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                m_isMovingHabitat = false;
                m_movingHabitatIndex = -1;
                std::cout << "Habitat move canceled." << std::endl;
                continue;
            }
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && m_moveHabitatButton.
                     getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                m_isMovingHabitat = true;
                m_movingHabitatIndex = -1;
                std::cout << "Select a habitat to move." << std::endl;
            }
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && !m_isMovingHabitat && !
                     m_isBuildingPath && !m_isDeletingObject)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    m_showHabitatOptions = true;
                else if (m_buildPathButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_isBuildingPath = true;
                    std::cout << "Building paths. Click on grid cells to place paths." << std::endl;
                    m_statusMessage.setString("Click on grid cells to build paths");
                }
                else if (m_deleteButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_isDeletingObject = true;
                    m_deletingObjectIndex = -1;
                    std::cout << "Select a habitat to delete." << std::endl;
                    m_statusMessage.setString("Select a habitat to delete");
                }
            }
            else if (m_isBuildingPath)
            {
                if (m_buildPathButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_isBuildingPath = false;
                    m_lastPathX = -1;
                    m_lastPathY = -1;
                    std::cout << "Path building canceled." << std::endl;
                    m_statusMessage.setString("");
                }
            }
            else if (m_isDeletingObject)
            {
                if (m_deleteButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_isDeletingObject = false;
                    m_deletingObjectIndex = -1;
                    std::cout << "Delete operation canceled." << std::endl;
                    m_statusMessage.setString("");
                }
                else
                {
                    int gridX = mousePosition.x / m_tileSize;
                    int gridY = mousePosition.y / m_tileSize;

                    int habitatIndex = m_zoo.findHabitatAt(gridX, gridY);

                    if (habitatIndex != -1)
                    {
                        try
                        {
                            if (m_zoo.deleteHabitatAt(habitatIndex))
                            {
                                if (habitatIndex < static_cast<int>(m_habitatBuildings.size()))
                                {
                                    m_habitatBuildings.erase(m_habitatBuildings.begin() + habitatIndex);
                                    m_animalsInHabitat.erase(m_animalsInHabitat.begin() + habitatIndex);
                                }

                                std::cout << "Habitat deleted successfully." << std::endl;
                            }
                        }
                        catch (const std::exception& e)
                        {
                            std::cout << "Error deleting habitat: " << e.what() << std::endl;
                        }

                        m_isDeletingObject = false;
                        m_deletingObjectIndex = -1;
                        m_statusMessage.setString("");
                    }
                }
            }
            else if (m_showHabitatOptions)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_showHabitatOptions = false;
                    std::cout << "Habitat selection cancelled." << std::endl;
                }
                else
                {
                    for (size_t i = 0; i < m_habitatOptionButtons.size(); i++)
                    {
                        if (m_habitatOptionButtons[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
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
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    m_isBuildingHabitat = false;
                    m_selectedHabitatType = "";
                    std::cout << "Habitat construction canceled." << std::endl;
                }
                else
                {
                    int cellX = mousePosition.x / m_tileSize;
                    int cellY = mousePosition.y / m_tileSize;

                    try
                    {
                        if (m_zoo.buildHabitatAt(m_selectedHabitatType, cellX, cellY, m_gridWidth, m_gridHeight))
                        {
                            for (int hx = cellX; hx < cellX + 3; hx++)
                            {
                                for (int hy = cellY; hy < cellY + 3; hy++)
                                {
                                    auto pathIt = std::remove_if(m_pathTiles.begin(), m_pathTiles.end(),
                                                                 [hx, hy](const auto &path)
                                                                 {
                                                                     return std::get<0>(path) == hx && std::get<1>(path)
                                                                            == hy;
                                                                 });

                                    if (pathIt != m_pathTiles.end())
                                    {
                                        std::cout << "Removed path at (" << hx << "," << hy
                                                << ") for new habitat" << std::endl;
                                        m_pathTiles.erase(pathIt, m_pathTiles.end());
                                    }
                                }
                            }

                            std::string builtType = m_selectedHabitatType;
                            m_habitatBuildings.push_back(std::make_tuple(cellX, cellY, m_selectedHabitatType));
                            m_animalsInHabitat.push_back({});
                            m_selectedHabitatType = "";
                            m_isBuildingHabitat = false;
                            std::cout << "Successfully built " << builtType << " habitat at position ("
                                    << cellX << "," << cellY << ")" << std::endl;
                        }
                    } catch (const HabitatException &e)
                    {
                        std::cout << e.what() << std::endl;
                    }
                    catch (const BudgetException &e)
                    {
                        std::cout << e.what() << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                }
            }
            else if (m_isMovingHabitat)
            {
                if (m_movingHabitatIndex == -1)
                {
                    int gridX = mousePosition.x / m_tileSize;
                    int gridY = mousePosition.y / m_tileSize;

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
                    int newX = mousePosition.x / m_tileSize;
                    int newY = mousePosition.y / m_tileSize;

                    bool isValidPosition = true;

                    if (newX < 1 || newY < 1 || newX + 2 >= static_cast<int>(m_gridWidth) - 1 || newY + 2 >= static_cast
                        <int>(m_gridHeight) - 1)
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

                        for (int hx = newX; hx < newX + 3; hx++)
                        {
                            for (int hy = newY; hy < newY + 3; hy++)
                            {
                                auto pathIt = std::remove_if(m_pathTiles.begin(), m_pathTiles.end(),
                                                             [hx, hy](const auto &path)
                                                             {
                                                                 return std::get<0>(path) == hx && std::get<1>(path) ==
                                                                        hy;
                                                             });

    m_zoo.syncInventoryWithHabitats();

                                if (pathIt != m_pathTiles.end())
                                {
                                    std::cout << "Removed path at (" << hx << "," << hy
                                            << ") for moved habitat" << std::endl;
                                    m_pathTiles.erase(pathIt, m_pathTiles.end());
                                }
                            }
                        }

                        m_habitatBuildings[m_movingHabitatIndex] = std::make_tuple(newX, newY, type);

                        if (m_movingHabitatIndex >= 0 && static_cast<size_t>(m_movingHabitatIndex) < m_zoo.getHabitats()
                            .size())
                        {
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
                    int gridX = mousePosition.x / m_tileSize;
                    int gridY = mousePosition.y / m_tileSize;

                    int habitatIndex = m_zoo.findHabitatAt(gridX, gridY);

                    if (habitatIndex != -1)
                    {
                        m_selectedHabitatIndex = habitatIndex;

                        std::string type;
                        if (habitatIndex < static_cast<int>(m_habitatBuildings.size()))
                        {
                            std::tie(std::ignore, std::ignore, type) = m_habitatBuildings[habitatIndex];
                        }
                        else
                        {
                            type = m_zoo.getHabitats()[habitatIndex].getType();
                        }

                        std::vector<std::string> allowed = Habitat::getAllowedAnimals(type);

                        m_animalOptionButtons.clear();
                        m_animalOptionTexts.clear();

                        float optWidth = 120, optHeight = 40;
                        float optStartX = m_addAnimalButton.getPosition().x;
                        float optStartY = m_addAnimalButton.getPosition().y + m_addAnimalButton.getSize().y + 10;

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
                        if (m_animalOptionButtons[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        {
                            m_selectedAnimalType = m_animalOptionTexts[i].getString();

                            try
                            {
                                if (m_zoo.addAnimalTo(m_selectedHabitatIndex, m_selectedAnimalType))
                                {
                                    m_animalsInHabitat[m_selectedHabitatIndex].push_back(m_selectedAnimalType);
                                }
                            } catch (const HabitatException &e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const AnimalException &e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const BudgetException &e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                            catch (const std::exception &e)
                            {
                                std::cout << "Error: " << e.what() << std::endl;

                                    m_zoo.syncInventoryWithHabitats();
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
        m_addAnimalButton.setPosition(m_buildHabitatButton.getPosition().x + m_buildHabitatButton.getSize().x + 10,
                                      m_buildHabitatButton.getPosition().y);
        m_addAnimalButtonText.setPosition(m_addAnimalButton.getPosition().x + 10,
                                          m_addAnimalButton.getPosition().y + 5);
        m_moveHabitatButton.setPosition(m_addAnimalButton.getPosition().x + m_addAnimalButton.getSize().x + 10,
                                        m_buildHabitatButton.getPosition().y);
        m_moveHabitatButtonText.setPosition(m_moveHabitatButton.getPosition().x + 10,
                                            m_moveHabitatButton.getPosition().y + 5);
        m_buildPathButton.setPosition(m_moveHabitatButton.getPosition().x + m_moveHabitatButton.getSize().x + 10,
                                      m_buildHabitatButton.getPosition().y);
        m_buildPathButtonText.setPosition(m_buildPathButton.getPosition().x + 10,
                                          m_buildPathButton.getPosition().y + 5);
        m_deleteButton.setPosition(m_buildPathButton.getPosition().x + m_buildPathButton.getSize().x + 10,
                                  m_buildHabitatButton.getPosition().y);
        m_deleteButtonText.setPosition(m_deleteButton.getPosition().x + 10,
                                       m_deleteButton.getPosition().y + 5);

                                               // Reposition inventory button on resize - next to delete button
                                               m_showInventoryButton.setPosition(m_deleteButton.getPosition().x + m_deleteButton.getSize().x + 10,
                                                                              m_buildHabitatButton.getPosition().y);
                                               sf::FloatRect textBounds = m_showInventoryButtonText.getLocalBounds();
                                               m_showInventoryButtonText.setPosition(
                                                   m_showInventoryButton.getPosition().x + (m_showInventoryButton.getSize().x - textBounds.width) / 2,
                                                   m_showInventoryButton.getPosition().y + (m_showInventoryButton.getSize().y - textBounds.height) / 2 - 5
                                               );

        if (m_showingInventory)
            prepareInventoryDisplay();
        float btnWidth = 120, btnHeight = 40;
        float startX = m_buildHabitatButton.getPosition().x;
        float startY = m_buildHabitatButton.getPosition().y + m_buildHabitatButton.getSize().y + 10;
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
            float optStartX = m_addAnimalButton.getPosition().x;
            float optStartY = m_addAnimalButton.getPosition().y + m_addAnimalButton.getSize().y + 10;
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

    if (m_isMovingHabitat)
    {
        if (m_movingHabitatIndex == -1)
        {
            m_statusMessage.setString("Select a habitat to move");
        }
        else
        {
            int newX = mousePos.x / m_tileSize;
            int newY = mousePos.y / m_tileSize;

            m_statusMessage.setString("Moving habitat to: (" + std::to_string(newX) +
                                      "," + std::to_string(newY) + ") - Click to place");
        }
        m_statusMessage.setPosition(10, m_windowHeight - 30);
    }
    else if (m_isBuildingHabitat)
    {
        int cellX = mousePos.x / m_tileSize;
        int cellY = mousePos.y / m_tileSize;

        m_statusMessage.setString("Building: " + m_selectedHabitatType +
                                  " | Grid position: (" + std::to_string(cellX) +
                                  "," + std::to_string(cellY) + ")");
        m_statusMessage.setPosition(10, m_windowHeight - 30);
    }
    else if (m_isDeletingObject)
    {
        int cellX = mousePos.x / m_tileSize;
        int cellY = mousePos.y / m_tileSize;

        m_statusMessage.setString("Deleting | Grid position: (" + std::to_string(cellX) +
                                  "," + std::to_string(cellY) + ")");
        m_statusMessage.setPosition(10, m_windowHeight - 30);
    }
    else if (m_isBuildingPath)
    {
        int cellX = mousePos.x / m_tileSize;
        int cellY = mousePos.y / m_tileSize;

        m_statusMessage.setString("Building path | Grid position: (" + std::to_string(cellX) +
                                  "," + std::to_string(cellY) + ")");
        m_statusMessage.setPosition(10, m_windowHeight - 30);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (cellX >= 1 && cellY >= 1 && cellX < static_cast<int>(m_gridWidth) - 1 &&
                cellY < static_cast<int>(m_gridHeight) - 1)
            {
                if (cellX != m_lastPathX || cellY != m_lastPathY)
                {
                    bool canBuildPath = true;

                    for (const auto &habitat: m_habitatBuildings)
                    {
                        int hx = std::get<0>(habitat);
                        int hy = std::get<1>(habitat);

                        bool overlapsX = (cellX >= hx && cellX < hx + 3);
                        bool overlapsY = (cellY >= hy && cellY < hy + 3);

// Inventory button is now initialized in the constructor

                        if (overlapsX && overlapsY)
                        {
                            canBuildPath = false;
                            break;
                        }
                    }

                    for (const auto &path: m_pathTiles)
                    {
                        if (std::get<0>(path) == cellX && std::get<1>(path) == cellY)
                        {
                            canBuildPath = false;
                            break;
                        }
                    }

                    if (canBuildPath)
                    {
                        m_pathTiles.push_back(std::make_tuple(cellX, cellY));
                        m_lastPathX = cellX;
                        m_lastPathY = cellY;
                    }
                }
            }
        }
        else
        {
            m_lastPathX = -1;
            m_lastPathY = -1;
        }
    }
    else
    {
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

            if (m_isBuildingHabitat)
            {
                if (x >= 1 && y >= 1 && x + 2 < m_gridWidth - 1 && y + 2 < m_gridHeight - 1)
                {
                    bool isValid = true;

                    for (const auto &habitat: m_habitatBuildings)
                    {
                        int hx = std::get<0>(habitat);
                        int hy = std::get<1>(habitat);

                        bool overlapsX = (static_cast<int>(x) < hx + 3) && (static_cast<int>(x) + 3 > hx);
                        bool overlapsY = (static_cast<int>(y) < hy + 3) && (static_cast<int>(y) + 3 > hy);

                        if (overlapsX && overlapsY)
                        {
                            isValid = false;
                            break;
                        }
                    }

                    if (isValid)
                    {
                        sf::RectangleShape highlight;
                        highlight.setSize(sf::Vector2f(m_tileSize, m_tileSize));
                        highlight.setPosition(x * m_tileSize, y * m_tileSize);
                        highlight.setFillColor(sf::Color(0, 255, 0, 40));
                        m_window.draw(highlight);
                    }
                }
            }

            if (m_isBuildingPath)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                int cellX = mousePos.x / m_tileSize;
                int cellY = mousePos.y / m_tileSize;

                if (cellX >= 1 && cellY >= 1 && cellX < static_cast<int>(m_gridWidth) - 1 &&
                    cellY < static_cast<int>(m_gridHeight) - 1)
                {
                    bool canBuildPath = true;

                    for (const auto &habitat: m_habitatBuildings)
                    {
                        int hx = std::get<0>(habitat);
                        int hy = std::get<1>(habitat);

                        bool overlapsX = (cellX >= hx && cellX < hx + 3);
                        bool overlapsY = (cellY >= hy && cellY < hy + 3);

                        if (overlapsX && overlapsY)
                        {
                            canBuildPath = false;
                            std::cout << "Cannot build path - location is occupied by a habitat" << std::endl;
                            break;
                        }
                    }

                    for (const auto &path: m_pathTiles)
                    {
                        if (std::get<0>(path) == cellX && std::get<1>(path) == cellY)
                        {
                            canBuildPath = false;
                            break;
                        }
                    }

                    sf::RectangleShape pathHighlight;
                    pathHighlight.setSize(sf::Vector2f(m_tileSize, m_tileSize));
                    pathHighlight.setPosition(cellX * m_tileSize, cellY * m_tileSize);

                    if (canBuildPath)
                    {
                        pathHighlight.setFillColor(sf::Color(153, 102, 51, 80));
                        pathHighlight.setOutlineColor(sf::Color(102, 51, 0));
                    }
                    else
                    {
                        pathHighlight.setFillColor(sf::Color(255, 0, 0, 80));
                        pathHighlight.setOutlineColor(sf::Color(200, 0, 0));
                    }

                    pathHighlight.setOutlineThickness(2);
                    m_window.draw(pathHighlight);
                }
            }
        }
    }

    for (const auto &path: m_pathTiles)
    {
        int x = std::get<0>(path);
        int y = std::get<1>(path);

        sf::Sprite pathSprite;
        pathSprite.setTexture(m_pathTexture);
        pathSprite.setPosition(x * m_tileSize, y * m_tileSize);
        pathSprite.setScale(static_cast<float>(m_tileSize) / pathSprite.getTexture()->getSize().x,
                            static_cast<float>(m_tileSize) / pathSprite.getTexture()->getSize().y);
        m_window.draw(pathSprite);
    }

    m_zoo.renderHabitats(m_window, m_tileSize, m_habitatTextures, m_animalTextures);

    if (m_isMovingHabitat && m_movingHabitatIndex != -1) {
        m_zoo.highlightHabitatAt(m_window, m_tileSize, m_movingHabitatIndex, sf::Color(255, 165, 0));

        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        int newX = mousePos.x / m_tileSize;
        int newY = mousePos.y / m_tileSize;

        newX = std::max(1, std::min(newX, static_cast<int>(m_gridWidth) - 4));
        newY = std::max(1, std::min(newY, static_cast<int>(m_gridHeight) - 4));

        bool isValidPosition = true;
        for (size_t i = 0; i < m_habitatBuildings.size(); i++) {
            if (static_cast<int>(i) == m_movingHabitatIndex) continue;

            int otherX, otherY;
            std::tie(otherX, otherY, std::ignore) = m_habitatBuildings[i];

            bool overlapsX = (newX < otherX + 3) && (newX + 3 > otherX);
            bool overlapsY = (newY < otherY + 3) && (newY + 3 > otherY);

            if (overlapsX && overlapsY) {
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

                        m_zoo.syncInventoryWithHabitats();
        } else {
            newPositionPreview.setFillColor(sf::Color(255, 0, 0, 80));
            newPositionPreview.setOutlineColor(sf::Color::Red);
        }

        newPositionPreview.setOutlineThickness(2);
        m_window.draw(newPositionPreview);
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
        statusText.setPosition(10, m_buildHabitatButton.getPosition().y + m_buildHabitatButton.getSize().y + 60);
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

        if (m_movingHabitatIndex == -1)
        {
            moveStatusText.setString("Select a habitat to move");
        }
        else
        {
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

            if (isValidPosition)
            {
                newPositionPreview.setFillColor(sf::Color(0, 255, 0, 80));
                newPositionPreview.setOutlineColor(sf::Color::Green);
            }
            else
            {
                newPositionPreview.setFillColor(sf::Color(255, 0, 0, 80));
                newPositionPreview.setOutlineColor(sf::Color::Red);
            }

            newPositionPreview.setOutlineThickness(2);
            m_window.draw(newPositionPreview);
        }

        moveStatusText.setPosition(m_moveHabitatButton.getPosition().x,
                                   m_moveHabitatButton.getPosition().y + m_moveHabitatButton.getSize().y + 10);
        m_window.draw(moveStatusText);
    }
    else
    {
        m_moveHabitatButtonText.setString("Move Habitat");
        m_moveHabitatButton.setFillColor(sf::Color(200, 100, 200));
    }

    if (m_isBuildingPath)
    {
        m_buildPathButtonText.setString("Cancel Path");
        m_buildPathButton.setFillColor(sf::Color::Red);

        sf::Text pathStatusText;
        pathStatusText.setFont(m_font);
        pathStatusText.setCharacterSize(16);
        pathStatusText.setFillColor(sf::Color::Yellow);
        pathStatusText.setString("Click on grid cells to build paths");
        pathStatusText.setPosition(m_buildPathButton.getPosition().x,
                                   m_buildPathButton.getPosition().y + m_buildPathButton.getSize().y + 10);
        m_window.draw(pathStatusText);
    }
    else
    {
        m_buildPathButtonText.setString("Build Path");
        m_buildPathButton.setFillColor(sf::Color(153, 102, 51));
    }

    if (m_isDeletingObject)
    {
        m_deleteButtonText.setString("Cancel Delete");
        m_deleteButton.setFillColor(sf::Color::Red);

        sf::Text deleteStatusText;
        deleteStatusText.setFont(m_font);
        deleteStatusText.setCharacterSize(16);
        deleteStatusText.setFillColor(sf::Color::Yellow);
        deleteStatusText.setString("Select a habitat to delete");
        deleteStatusText.setPosition(m_deleteButton.getPosition().x,
                                   m_deleteButton.getPosition().y + m_deleteButton.getSize().y + 10);
        m_window.draw(deleteStatusText);
    }
    else
    {
        m_deleteButtonText.setString("Delete");
        m_deleteButton.setFillColor(sf::Color(200, 0, 0));
    }

    m_window.draw(m_buildHabitatButton);
    m_window.draw(m_buildHabitatButtonText);

    // Draw Show Inventory button
    m_window.draw(m_showInventoryButton);
    m_window.draw(m_showInventoryButtonText);

    // Update text position
    m_showInventoryButtonText.setPosition(
        m_showInventoryButton.getPosition().x + (m_showInventoryButton.getSize().x - m_showInventoryButtonText.getLocalBounds().width) / 2,
        m_showInventoryButton.getPosition().y + (m_showInventoryButton.getSize().y - m_showInventoryButtonText.getLocalBounds().height) / 2 - 5
    );
    m_window.draw(m_addAnimalButton);
    m_window.draw(m_addAnimalButtonText);
    m_window.draw(m_moveHabitatButton);
    m_window.draw(m_moveHabitatButtonText);
    m_window.draw(m_buildPathButton);
    m_window.draw(m_buildPathButtonText);
    m_window.draw(m_deleteButton);
    m_window.draw(m_deleteButtonText);
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

    if (m_showingInventory)
    {
        m_window.draw(m_inventoryBackground);
        for (const auto &text : m_inventoryTexts)
            m_window.draw(text);
    }

    sf::Text budgetText;
    budgetText.setFont(m_font);
    budgetText.setCharacterSize(20);
    budgetText.setFillColor(sf::Color::White);
    budgetText.setString("Budget: $" + std::to_string(static_cast<int>(m_zoo.getBudget())));
    budgetText.setPosition(m_showInventoryButton.getPosition().x + m_showInventoryButton.getSize().x + 20, 
                          m_gridHeight * m_tileSize + 10);
    m_window.draw(budgetText);

    if (!m_statusMessage.getString().isEmpty())
    {
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

bool Game::loadTexture(sf::Texture& texture, const std::string& primaryPath, const std::string& backupPath, sf::Color fallbackColor)
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

void Game::prepareInventoryDisplay()
{
    m_inventoryTexts.clear();
    m_zoo.syncInventoryWithHabitats();
    std::string summary = m_zoo.getInventorySummary();
    std::istringstream iss(summary);
    std::string line;
    float padding = 10.f;
    float yOffset = padding;
    float maxWidth = 0.f;
    while (std::getline(iss, line))
    {
        sf::Text text;
        text.setFont(m_font);
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);
        text.setString(line);
        m_inventoryTexts.push_back(text);
        float w = text.getLocalBounds().width;
        if (w > maxWidth)
            maxWidth = w;
    }

    float backgroundWidth = maxWidth + 2 * padding;
    float backgroundHeight = (m_inventoryTexts.size() * 18.f) + 2 * padding;
    m_inventoryBackground.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
    m_inventoryBackground.setPosition((m_windowWidth - backgroundWidth) / 2.f,
                                      (m_windowHeight - backgroundHeight) / 2.f);

    float currentY = m_inventoryBackground.getPosition().y + padding;
    for (auto &text : m_inventoryTexts)
    {
        text.setPosition(m_inventoryBackground.getPosition().x + padding, currentY);
        currentY += 18.f;
    }
}