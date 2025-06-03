#ifndef ZOO_H
#define ZOO_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"
#include "Habitat.hpp"
#include "exception/ZooExceptions.hpp"
#include "AnimalInventory.hpp"

class Zoo
{
private:
    std::string m_name;
    std::vector<Habitat> m_habitats;
    int m_visitorCount;
    bool m_isOpen;
    float m_budget;

    AnimalInventory<Animal> m_allAnimalsInventory{"All Animals", 200};
    AnimalInventory<Habitat> m_habitatInventory{"Habitats", 50};

public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open,
        float budget = 100000);

    ~Zoo() = default;

    Zoo(const Zoo &other);

    Zoo(Zoo &&other) noexcept;

    Zoo &operator=(const Zoo &other);

    Zoo &operator=(Zoo &&other) noexcept;

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &newName);

    [[nodiscard]] const std::vector<Habitat> &getHabitats() const;

    void addHabitats(const Habitat &habitat);

    void addHabitats(const std::vector<Habitat> &newHabitats);

    void moveHabitat(size_t habitatIndex, int newX, int newY);

    [[nodiscard]] int getVisitorCount() const;//.

    void setVisitorCount(int visitor_count);

    [[nodiscard]] bool getIsOpen() const;

    void setIsOpen(bool is_open);

    [[nodiscard]] float getBudget() const;

    void setBudget(float newBudget);

    bool spendMoney(float amount);

    bool buildHabitatAt(const std::string &type, int gridX, int gridY, int gridWidth, int gridHeight);

    bool canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const;

    int findHabitatAt(int gridX, int gridY) const;

    bool addAnimalTo(int habitatIndex, const std::string &animalType);
    
    bool deleteHabitatAt(int habitatIndex);

    float calculateRefund(float originalPrice) const;

    static bool loadTexture(sf::Texture &texture, const std::string &primaryPath, const std::string &backupPath,
                          sf::Color fallbackColor);
    
    static void nameInput(sf::RenderWindow& window, sf::Font& font, std::string& zooName, bool& nameEntered);
    
    static void showTutorial(sf::RenderWindow& window, sf::Font& font);
    
    void renderHabitats(sf::RenderWindow& window, int tileSize, 
                        const std::map<std::string, sf::Texture>& habitatTextures,
                        const std::map<std::string, sf::Texture>& animalTextures) const;
    
    void highlightHabitatAt(sf::RenderWindow& window, int tileSize, int index, const sf::Color& color) const;

    friend std::ostream &operator<<(std::ostream &os, const Zoo &zoo);

    AnimalInventory<Animal>& getAllAnimalsInventory() { return m_allAnimalsInventory; }
    AnimalInventory<Habitat>& getHabitatInventory() { return m_habitatInventory; }

    void syncInventoryWithHabitats();
    void displayAllInventories() const;

    // Methods using template functions
    float calculateAverageAnimalHealth() const;
    int calculateTotalAnimalValue() const;
    float calculateAverageHabitatCleanliness() const;
    int calculateTotalHabitatCapacity() const;

    void displayHealthyAnimals(float minHealthThreshold = 0.7f) const;
    void displayExpensiveAnimals(int minPrice = 1000) const;

    void printAnimalDetails() const;
    void printHabitatDetails() const;
};

#endif //ZOO_H
