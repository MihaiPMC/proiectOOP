#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

class Game
{
public:
    Game();
    void run();

private:
    bool loadTexture(sf::Texture &texture, const std::string &primaryPath, const std::string &backupPath, sf::Color fallbackColor);
    void processEvents();
    void update();
    void render();
    void handleResize(unsigned int width, unsigned int height);
    void nameInput();

    sf::RenderWindow m_window;
    unsigned int m_windowWidth, m_windowHeight;
    sf::Font m_font;
    std::string m_zooName;
    bool m_nameEntered;
    sf::Text m_prompt;
    sf::Text m_inputText;
    unsigned int m_gridWidth, m_gridHeight;
    int m_tileSize;
    sf::Texture m_grassTexture, m_wallTexture;
    std::vector<std::vector<sf::Sprite>> m_tiles;
    bool m_isBuildingHabitat;
    bool m_showHabitatOptions;
    std::string m_selectedHabitatType;
    std::map<std::string, sf::Texture> m_habitatTextures;
    sf::RectangleShape m_buildHabitatButton;
    sf::Text m_buildHabitatButtonText;
    std::vector<sf::RectangleShape> m_habitatOptionButtons;
    std::vector<sf::Text> m_habitatOptionTexts;
    std::vector<std::tuple<int, int, std::string>> m_habitatBuildings;
};