#pragma once
#include <string>
#include "Animal.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "exception/ZooExceptions.hpp"
#include "animals/Fish.hpp"
#include "animals/Bird.hpp"
#include "animals/Mammal.hpp"
#include "animals/Reptile.hpp"

/**
 * @class Habitat
 * @brief Represents a habitat in the zoo where animals live
 * 
 * The Habitat class manages a specific environment for a group of animals.
 * Each habitat has a type (Desert, Forest, etc.), a collection of animals,
 * and properties like capacity and cleanliness level. Habitats are placed
 * on a grid in the zoo layout.
 */
class Habitat {
private:
    std::string m_type;                              // Type of habitat (Desert, Forest, Mountain, Ocean, Savanna)
    std::vector<std::shared_ptr<Animal>> m_animals;  // Animals living in the habitat
    int m_capacity;                                  // Maximum number of animals the habitat can hold
    float m_cleanlinessLevel;                        // Cleanliness level from 0.0 (dirty) to 1.0 (clean)
    float m_price;                                   // Cost to build the habitat
    static std::map<std::string, std::vector<std::string>> s_habitatSpecies;  // Map of habitat types to allowed animal species
    int m_gridX;                                     // X position on the zoo grid
    int m_gridY;                                     // Y position on the zoo grid
public:
    /**
     * @brief Constructor for creating a new habitat
     * @param type The type of habitat (Desert, Forest, etc.)
     * @param animals Initial collection of animals for the habitat
     * @param capacity Maximum number of animals the habitat can contain
     * @param cleanlinessLevel Initial cleanliness level (0.0 to 1.0)
     * @param price Cost to build the habitat
     */
    Habitat(const std::string &type, const std::vector<std::shared_ptr<Animal>> &animals, int capacity = 5, float cleanlinessLevel = 1.0f, float price = 10000.0f);
    
    /**
     * @brief Default destructor
     */
    ~Habitat() = default;
    
    /**
     * @brief Copy constructor
     * @param other The habitat to copy from
     */
    Habitat(const Habitat &other);
    
    /**
     * @brief Move constructor
     * @param other The habitat to move from
     */
    Habitat(Habitat &&other) noexcept;
    
    /**
     * @brief Copy assignment operator
     * @param other The habitat to copy from
     * @return Reference to this habitat after assignment
     */
    Habitat &operator=(const Habitat &other);
    
    /**
     * @brief Move assignment operator
     * @param other The habitat to move from
     * @return Reference to this habitat after assignment
     */
    Habitat &operator=(Habitat &&other) noexcept;
    
    /**
     * @brief Get the habitat type
     * @return The habitat type (Desert, Forest, etc.)
     */
    [[nodiscard]] const std::string &getType() const;
    
    /**
     * @brief Set the habitat type
     * @param newType The new habitat type
     */
    void setType(const std::string &newType);
    
    /**
     * @brief Get the animals in the habitat
     * @return Vector of animal pointers
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>> &getAnimals() const;
    
    /**
     * @brief Add multiple animals to the habitat
     * @param newAnimals Vector of animal pointers to add
     */
    void addAnimals(const std::vector<std::shared_ptr<Animal>> &newAnimals);
    
    /**
     * @brief Get the maximum capacity of the habitat
     * @return Maximum number of animals
     */
    [[nodiscard]] int getCapacity() const;
    
    /**
     * @brief Set the maximum capacity of the habitat
     * @param newCapacity New maximum capacity
     */
    void setCapacity(int newCapacity);
    
    /**
     * @brief Get the cleanliness level
     * @return Cleanliness level from 0.0 (dirty) to 1.0 (clean)
     */
    [[nodiscard]] float getCleanlinessLevel() const;
    
    /**
     * @brief Set the cleanliness level
     * @param level New cleanliness level
     */
    void setCleanlinessLevel(float level);
    
    /**
     * @brief Get the price of the habitat
     * @return Price in game currency
     */
    [[nodiscard]] float getPrice() const;
    
    /**
     * @brief Set the price of the habitat
     * @param new_price New price in game currency
     */
    void setPrice(float new_price);
    
    /**
     * @brief Clean the habitat, resetting cleanliness to 1.0
     */
    void cleanHabitat();
    
    /**
     * @brief Update cleanliness level over time
     * @param deltaTime Time elapsed since last update
     */
    void updateCleanliness(float deltaTime);
    
    /**
     * @brief Add a single animal to the habitat
     * @param animal Pointer to the animal to add
     * @throws AnimalException if habitat is at capacity or animal type is incompatible
     */
    void addAnimal(const std::shared_ptr<Animal> &animal);
    
    /**
     * @brief Set the position of the habitat on the zoo grid
     * @param x X-coordinate on the grid
     * @param y Y-coordinate on the grid
     */
    void setPosition(int x, int y);
    
    /**
     * @brief Get the X-coordinate on the zoo grid
     * @return X-coordinate
     */
    int getGridX() const;
    
    /**
     * @brief Get the Y-coordinate on the zoo grid
     * @return Y-coordinate
     */
    int getGridY() const;
    
    /**
     * @brief Check if this habitat overlaps with another
     * @param other The other habitat to check against
     * @return true if habitats overlap, false otherwise
     */
    bool overlaps(const Habitat &other) const;
    
    /**
     * @brief Check if the habitat position is valid within grid boundaries
     * @param gridWidth Width of the zoo grid
     * @param gridHeight Height of the zoo grid
     * @return true if position is valid, false otherwise
     */
    bool isValidPosition(int gridWidth, int gridHeight) const;
    
    /**
     * @brief Check if a habitat can be built at a specific grid position
     * @param gridX X-coordinate on the grid
     * @param gridY Y-coordinate on the grid
     * @param gridWidth Width of the zoo grid
     * @param gridHeight Height of the zoo grid
     * @return true if habitat can be built, false otherwise
     */
    bool canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const;
    
    /**
     * @brief Make all animals in the habitat show their behaviors
     */
    void showSpecificBehaviors() const;
    
    /**
     * @brief Make animals interact with visitors
     * @param visitorCount Number of visitors interacting
     */
    void animalsInteractWithVisitors(int visitorCount) const;
    
    /**
     * @brief Get list of animal species allowed in a habitat type
     * @param habitatType The type of habitat to check
     * @return Vector of allowed animal species names
     */
    static std::vector<std::string> getAllowedAnimals(const std::string& habitatType);
    
    /**
     * @brief Make a specific animal demonstrate its behavior
     * @param animal Pointer to the animal
     */
    void demonstrateSpecificBehavior(const std::shared_ptr<Animal>& animal) const;
    
    /**
     * @brief Calculate how satisfied visitors are with this habitat
     * @param visitorCount Number of visitors
     * @return Satisfaction level from 0.0 to 1.0
     */
    float calculateVisitorSatisfaction(int visitorCount) const;
    
    // Rendering methods
    /**
     * @brief Render the habitat on the screen
     * @param window SFML render window to draw on
     * @param tileSize Size of each tile in pixels
     * @param habitatTexture Texture to use for the habitat
     */
    void renderHabitat(sf::RenderWindow& window, int tileSize, const sf::Texture& habitatTexture) const;
    
    /**
     * @brief Render the animals in the habitat
     * @param window SFML render window to draw on
     * @param tileSize Size of each tile in pixels
     * @param animalTextures Map of animal textures keyed by species name
     */
    void renderAnimals(sf::RenderWindow& window, int tileSize, const std::map<std::string, sf::Texture>& animalTextures) const;
    
    /**
     * @brief Highlight the habitat with a colored outline
     * @param window SFML render window to draw on
     * @param tileSize Size of each tile in pixels
     * @param color Color to use for the highlight
     * @param outlineThickness Thickness of the highlight outline
     */
    void highlightHabitat(sf::RenderWindow& window, int tileSize, const sf::Color& color, float outlineThickness = 2.0f) const;

    /**
     * @brief Output stream operator for displaying habitat information
     * @param os Output stream
     * @param habitat Habitat to display
     * @return Modified output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Habitat &habitat);
};
