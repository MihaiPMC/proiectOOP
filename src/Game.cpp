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

/**
 * @brief Constructor for the Game class
 * 
 * Initializes all game components, including the window, textures, UI elements,
 * and the zoo object. Sets up the game state and prepares the grid for habitat placement.
 * This is the main entry point for the zoo tycoon game.
 */
Game::Game()
    : m_window(),                         // SFML window for rendering
      m_windowWidth(1800),                // Default window width
      m_windowHeight(1350),               // Default window height
      m_font(),                           // Font for text display
      m_zooName(),                        // Name of the zoo (entered by user)
      m_nameEntered(false),               // Flag for whether zoo name has been entered
      m_prompt(),                         // Text prompt for user input
      m_inputText(),                      // Text displaying user input
      m_gridWidth(40),                    // Width of the zoo grid in tiles
      m_gridHeight(25),                   // Height of the zoo grid in tiles
      m_tileSize(0),                      // Size of each grid tile in pixels (calculated later)
      m_grassTexture(),                   // Texture for grass tiles
      m_wallTexture(),                    // Texture for wall/perimeter tiles
      m_tiles(),                          // 2D grid of tile sprites
      m_isBuildingHabitat(false),         // Flag for habitat building mode
      m_showHabitatOptions(false),        // Flag for showing habitat type options
      m_selectedHabitatType(""),          // Currently selected habitat type
      m_habitatTextures(),                // Map of habitat textures by type
      m_buildHabitatButton(),             // Button for habitat building
      m_buildHabitatButtonText(),         // Text for habitat building button
      m_habitatOptionButtons(),           // Buttons for habitat type selection
      m_habitatOptionTexts(),             // Text labels for habitat type buttons
      m_habitatBuildings(),               // List of built habitats' positions and types
      m_addAnimalButton(),                // Button for adding animals
      m_addAnimalButtonText(),            // Text for add animal button
      m_isAddingAnimal(false),            // Flag for animal adding mode
      m_showAnimalOptionsForAnimal(false),// Flag for showing animal type options
      m_statusMessage(),                  // Status message display
      m_selectedHabitatIndex(-1),         // Index of the currently selected habitat
      m_selectedAnimalType(""),           // Currently selected animal type
      m_animalOptionButtons(),            // Buttons for animal type selection
      m_animalOptionTexts(),              // Text labels for animal type buttons
      m_animalTextures(),                 // Map of animal textures by type
      m_animalsInHabitat(),               // List of animals in each habitat
      m_moveHabitatButton(),              // Button for moving habitats
      m_moveHabitatButtonText(),          // Text for move habitat button
      m_isMovingHabitat(false),           // Flag for habitat moving mode
      m_movingHabitatIndex(-1),           // Index of the habitat being moved
      m_originalHabitatX(0),              // Original X position of habitat being moved
      m_originalHabitatY(0),              // Original Y position of habitat being moved
      m_buildPathButton(),                // Button for building paths
      m_buildPathButtonText(),            // Text for build path button
      m_isBuildingPath(false),            // Flag for path building mode
      m_pathTexture(),                    // Texture for path tiles
      m_pathTiles(),                      // List of path positions
      m_lastPathX(-1),                    // Last X position where a path was placed
      m_lastPathY(-1),                    // Last Y position where a path was placed
      m_zoo("Default Zoo", {}, 0, true)   // Zoo object with default settings
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
    
    // Use the moved methods from Zoo class
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


/**
 * @brief Process all events from the SFML window
 * 
 * This method handles all user interactions including mouse clicks, window events,
 * and UI interactions. It manages the game state based on user actions, such as
 * building habitats, placing animals, and navigating the UI.
 */
void Game::processEvents()
{
    // Process all pending events
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Handle window close event
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            return;
        }
        // Handle window resize event
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
            else if (!m_isAddingAnimal && !m_isMovingHabitat && m_addAnimalButton.getGlobalBounds().contains(
                         mousePos.x, mousePos.y))
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
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && m_moveHabitatButton.
                     getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                m_isMovingHabitat = true;
                m_movingHabitatIndex = -1;
                std::cout << "Select a habitat to move." << std::endl;
            }
            else if (!m_isAddingAnimal && !m_isBuildingHabitat && !m_showHabitatOptions && !m_isMovingHabitat && !
                     m_isBuildingPath)
            {
                if (m_buildHabitatButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    m_showHabitatOptions = true;
                else if (m_buildPathButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    m_isBuildingPath = true;
                    std::cout << "Building paths. Click on grid cells to place paths." << std::endl;
                    m_statusMessage.setString("Click on grid cells to build paths");
                }
            }
            else if (m_isBuildingPath)
            {
                if (m_buildPathButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    m_isBuildingPath = false;
                    m_lastPathX = -1;
                    m_lastPathY = -1;
                    std::cout << "Path building canceled." << std::endl;
                    m_statusMessage.setString("");
                }
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
                    int gridX = mousePos.x / m_tileSize;
                    int gridY = mousePos.y / m_tileSize;

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
                        if (m_animalOptionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
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

/**
 * @brief Handle window resize events
 * 
 * This method updates the game's internal dimensions and scales all UI elements
 * appropriately when the window is resized. It ensures that the grid and UI
 * components maintain proper proportions and positions.
 * 
 * @param width New window width in pixels
 * @param height New window height in pixels
 */
void Game::handleResize(unsigned int width, unsigned int height)
{
    // Update internal dimensions
    m_windowWidth = width;
    m_windowHeight = height;
    
    // Update the view to match the new window size
    sf::FloatRect visibleArea(0, 0, width, height);
    m_window.setView(sf::View(visibleArea));
    
    // Calculate new tile size based on available space
    // Leave room for UI elements at the bottom
    int newTileSize = std::min(int(width) / int(m_gridWidth), (int(height) - UI_MARGIN) / int(m_gridHeight));
    
    // Only update positions if the tile size has changed
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

/**
 * @brief Update game state for the current frame
 * 
 * This method updates the game state based on the current mouse position
 * and game mode (building habitat, placing animal, moving habitat, etc.).
 * It updates status messages and handles path building logic.
 */
void Game::update()
{
    // Get current mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    // Handle habitat moving mode
    if (m_isMovingHabitat)
    {
        // If no habitat is selected yet, prompt the user to select one
        if (m_movingHabitatIndex == -1)
        {
            m_statusMessage.setString("Select a habitat to move");
        }
        // If a habitat is selected, show the current potential placement position
        else
        {
            // Calculate grid coordinates from mouse position
            int newX = mousePos.x / m_tileSize;
            int newY = mousePos.y / m_tileSize;

            // Update status message with current coordinates
            m_statusMessage.setString("Moving habitat to: (" + std::to_string(newX) +
                                      "," + std::to_string(newY) + ") - Click to place");
        }
        // Position the status message
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

/**
 * @brief Render all game elements to the window
 * 
 * This method is responsible for drawing all game elements to the SFML window.
 * It renders the grid, paths, habitats, animals, UI elements, and status messages.
 * The rendering order ensures proper layering of elements.
 */
void Game::render()
{
    // Clear the window with a dark gray background
    m_window.clear(sf::Color(50, 50, 50));
    
    // Draw the basic grid tiles (grass and walls)
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

    // Use the Zoo class to render habitats and animals
    m_zoo.renderHabitats(m_window, m_tileSize, m_habitatTextures, m_animalTextures);
    
    // If moving a habitat, highlight it
    if (m_isMovingHabitat && m_movingHabitatIndex != -1) {
        m_zoo.highlightHabitatAt(m_window, m_tileSize, m_movingHabitatIndex, sf::Color(255, 165, 0));
        
        // Show the new position preview
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

    m_window.draw(m_buildHabitatButton);
    m_window.draw(m_buildHabitatButtonText);
    m_window.draw(m_addAnimalButton);
    m_window.draw(m_addAnimalButtonText);
    m_window.draw(m_moveHabitatButton);
    m_window.draw(m_moveHabitatButtonText);
    m_window.draw(m_buildPathButton);
    m_window.draw(m_buildPathButtonText);
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

    if (!m_statusMessage.getString().isEmpty())
    {
        m_window.draw(m_statusMessage);
    }

    m_window.display();
}

/**
 * @brief Main game loop
 * 
 * This method contains the main game loop that processes events,
 * updates game state, and renders the game continuously until
 * the window is closed.
 */
void Game::run()
{
    // Main game loop - continues until the window is closed
    while (m_window.isOpen())
    {
        processEvents();  // Handle user input and events
        update();         // Update game state
        render();         // Draw everything to the screen
    }
}

/**
 * @brief Loads a texture from file with fallback options
 * 
 * This utility method attempts to load a texture from the primary file path,
 * then from a backup path if the primary fails. If both fail, it creates a
 * solid-colored fallback texture.
 * 
 * @param texture Reference to the texture to be loaded
 * @param primaryPath Primary file path to try first
 * @param backupPath Backup file path to try if primary fails
 * @param fallbackColor Color to use for fallback texture if both paths fail
 * @return true if loading from either path succeeded, false if fallback was used
 */
bool Game::loadTexture(sf::Texture& texture, const std::string& primaryPath, const std::string& backupPath, sf::Color fallbackColor)
{
    // Try loading from the primary path first
    if (texture.loadFromFile(primaryPath))
    {
        std::cout << "Loaded texture from " << primaryPath << std::endl;
        return true;
    }
    
    // If primary path fails, try the backup path
    if (texture.loadFromFile(backupPath))
    {
        std::cout << "Loaded texture from " << backupPath << std::endl;
        return true;
    }
    
    // If both paths fail, create a solid color fallback texture
    sf::Image fallbackImage;
    fallbackImage.create(64, 64, fallbackColor);  // Create a 64x64 image with the fallback color
    texture.loadFromImage(fallbackImage);
    std::cout << "Using fallback texture" << std::endl;
    return false;
}
