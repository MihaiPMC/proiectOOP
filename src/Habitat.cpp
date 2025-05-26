#include "../include/Habitat.hpp"
#include "../include/exception/HabitatException.hpp"
#include "../include/exception/AnimalException.hpp"
#include <map>
#include <vector>

// Define static member variable
std::map<std::string, std::vector<std::string>> Habitat::s_habitatSpecies = {
    {"Desert", {"camel", "coyote", "scorpion"}},
    {"Forest", {"bear", "fox", "wolf"}},
    {"Mountain", {"eagle", "goat", "yak"}},
    {"Ocean", {"dolphin", "octopus", "seaturtle"}},
    {"Savanna", {"elephant", "lion", "zebra"}}
};

Habitat::Habitat(const std::string &type, const std::vector<std::shared_ptr<Animal>> &animals, int capacity, float cleanlinessLevel, float price)
    : m_type(type), m_animals(animals), m_capacity(capacity), m_cleanlinessLevel(cleanlinessLevel), m_price(price), m_gridX(-1), m_gridY(-1)
{
}

Habitat::Habitat(const Habitat &other)
    : m_type(other.m_type), m_animals(other.m_animals), m_capacity(other.m_capacity),
      m_cleanlinessLevel(other.m_cleanlinessLevel), m_price(other.m_price),
      m_gridX(other.m_gridX), m_gridY(other.m_gridY)
{
}

Habitat::Habitat(Habitat &&other) noexcept
    : m_type(std::move(other.m_type)), m_animals(std::move(other.m_animals)),
      m_capacity(other.m_capacity), m_cleanlinessLevel(other.m_cleanlinessLevel), m_price(other.m_price),
      m_gridX(other.m_gridX), m_gridY(other.m_gridY)
{
}

Habitat &Habitat::operator=(const Habitat &other)
{
    if (this == &other)
        return *this;
    m_type = other.m_type;
    m_animals = other.m_animals;
    m_capacity = other.m_capacity;
    m_cleanlinessLevel = other.m_cleanlinessLevel;
    m_price = other.m_price;
    m_gridX = other.m_gridX;
    m_gridY = other.m_gridY;
    return *this;
}

Habitat &Habitat::operator=(Habitat &&other) noexcept
{
    if (this == &other)
        return *this;
    m_type = std::move(other.m_type);
    m_animals = std::move(other.m_animals);
    m_capacity = other.m_capacity;
    m_cleanlinessLevel = other.m_cleanlinessLevel;
    m_price = other.m_price;
    m_gridX = other.m_gridX;
    m_gridY = other.m_gridY;
    return *this;
}

const std::string &Habitat::getType() const
{
    return m_type;
}

void Habitat::setType(const std::string &newType)
{
    m_type = newType;
}

const std::vector<std::shared_ptr<Animal>> &Habitat::getAnimals() const
{
    return m_animals;
}

void Habitat::addAnimals(const std::vector<std::shared_ptr<Animal>> &newAnimals)
{
    for (const auto &animal: newAnimals)
    {
        m_animals.push_back(animal);
    }
}

bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (size_t i = 0; i < str1.size(); i++) {
        if (std::tolower(str1[i]) != std::tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

void Habitat::addAnimal(const std::shared_ptr<Animal> &animal)
{
    if (static_cast<int>(m_animals.size()) >= m_capacity) {
        throw HabitatException("Habitat has reached its capacity of " + std::to_string(m_capacity) + " animals");
    }

    bool allowed = false;
    const auto& compatibleSpecies = s_habitatSpecies[m_type];
    for (const auto& species : compatibleSpecies) {
        if (caseInsensitiveCompare(animal->getSpecies(), species)) {
            allowed = true;
            break;
        }
    }
    
    if (!allowed) {
        throw AnimalException(animal->getSpecies() + " cannot live in a " + m_type + " habitat");
    }
    
    m_animals.push_back(animal);
}

int Habitat::getCapacity() const
{
    return m_capacity;
}

void Habitat::setCapacity(int newCapacity)
{
    m_capacity = newCapacity;
}

float Habitat::getCleanlinessLevel() const
{
    return m_cleanlinessLevel;
}

void Habitat::setCleanlinessLevel(float level)
{
    m_cleanlinessLevel = level;
}

float Habitat::getPrice() const
{
    return m_price;
}

void Habitat::setPrice(float new_price)
{
    m_price = new_price;
}

void Habitat::cleanHabitat()
{
    m_cleanlinessLevel = 1.0f;
}

void Habitat::updateCleanliness(float deltaTime)
{
    int totalAnimals = m_animals.size();
    if (totalAnimals > 0)
    {
        const float decayRate = 0.01f;
        m_cleanlinessLevel -= decayRate * totalAnimals * deltaTime;
        if (m_cleanlinessLevel < 0.0f)
            m_cleanlinessLevel = 0.0f;
    }
}

void Habitat::demonstrateSpecificBehavior(const std::shared_ptr<Animal>& animal) const {
    if (auto fish = std::dynamic_pointer_cast<Fish>(animal)) {
        std::cout << "This is a fish with fin type: " << fish->getFinType() << std::endl;
        fish->performBehavior();
    }
    else if (auto bird = std::dynamic_pointer_cast<Bird>(animal)) {
        std::cout << "This is a bird with wingspan: " << bird->getWingSpan() << " meters" << std::endl;
        bird->performBehavior();
    }
    else if (auto mammal = std::dynamic_pointer_cast<Mammal>(animal)) {
        std::cout << "This is a mammal with fur color: " << mammal->getFurColor() << std::endl;
        mammal->performBehavior();
    }
            else if (auto reptile = std::dynamic_pointer_cast<Reptile>(animal)) {
        std::cout << "This is a reptile with " << reptile->getScalePattern() << " scale pattern" << std::endl;
        std::cout << "Cold-blooded: " << (reptile->getIsColdBlooded() ? "Yes" : "No") << std::endl;
        reptile->performBehavior();
            }
    else {
        std::cout << "Unknown animal type!" << std::endl;
    }
}

void Habitat::showSpecificBehaviors() const {
    std::cout << "\nDemonstrating specific behaviors for animals in " << m_type << " habitat:" << std::endl;
    if (m_animals.empty()) {
        std::cout << "No animals in this habitat!" << std::endl;
        return;
    }
    
    for (const auto& animal : m_animals) {
        demonstrateSpecificBehavior(animal);
        std::cout << "------------------------" << std::endl;
    }
}

        float Habitat::calculateVisitorSatisfaction(int visitorCount) const {
            if (m_animals.empty()) {
        return 0.0f;
            }
            
            float totalSatisfaction = 0.0f;

            for (const auto& animal : m_animals) {
        totalSatisfaction += animal->interactWithVisitors(visitorCount / static_cast<int>(m_animals.size()));
            }

            float cleanlinessMultiplier = 0.5f + (m_cleanlinessLevel * 0.5f);
            
            return totalSatisfaction * cleanlinessMultiplier;
        }

        void Habitat::animalsInteractWithVisitors(int visitorCount) const {
            std::cout << "\nVisitors are interacting with animals in the " << m_type << " habitat:" << std::endl;
            
            if (m_animals.empty()) {
        std::cout << "There are no animals in this habitat for visitors to interact with." << std::endl;
        return;
            }
            
            int visitorsPerAnimal = visitorCount / static_cast<int>(m_animals.size());
            
            for (const auto& animal : m_animals) {
        float enjoyment = animal->interactWithVisitors(visitorsPerAnimal);
        std::cout << "Visitor satisfaction from interaction: " << enjoyment << std::endl;
        std::cout << "------------------------" << std::endl;
            }
            
            float totalSatisfaction = calculateVisitorSatisfaction(visitorCount);
            std::cout << "Total visitor satisfaction for " << m_type << " habitat: " << totalSatisfaction << std::endl;
        }
        
        bool Habitat::canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const {
            if (gridX < 1 || gridY < 1 || (gridX + 3) > (gridWidth - 1) || (gridY + 3) > (gridHeight - 1)) {
                return false;
            }
            return true;
        }
        
        void Habitat::renderHabitat(sf::RenderWindow& window, int tileSize, const sf::Texture& habitatTexture) const {
            if (m_gridX == -1 || m_gridY == -1)
                return;
                
            sf::Sprite habitatSprite;
            habitatSprite.setTexture(habitatTexture);
            sf::Vector2u texSize = habitatTexture.getSize();
            float scaleX = (3 * tileSize) / float(texSize.x);
            float scaleY = (3 * tileSize) / float(texSize.y);
            habitatSprite.setScale(scaleX, scaleY);
            habitatSprite.setPosition(m_gridX * tileSize, m_gridY * tileSize);
            window.draw(habitatSprite);
        }
        
        void Habitat::renderAnimals(sf::RenderWindow& window, int tileSize, const std::map<std::string, sf::Texture>& animalTextures) const {
            if (m_gridX == -1 || m_gridY == -1 || m_animals.empty())
                return;
                
            float habitatX = m_gridX * tileSize;
            float habitatY = m_gridY * tileSize;
            float habitatWidth = 3 * tileSize;
            float habitatHeight = 3 * tileSize;
            
            for (size_t j = 0; j < m_animals.size(); j++) {
                const auto& animal = m_animals[j];
                auto it = animalTextures.find(animal->getSpecies());
                if (it != animalTextures.end()) {
                    sf::Sprite animalSprite;
                    animalSprite.setTexture(it->second);
                    sf::Vector2u texSize = it->second.getSize();
                    float factor = 0.03f;
                    animalSprite.setScale(factor, factor);
                    int scaledWidth = int(texSize.x * factor);
                    int scaledHeight = int(texSize.y * factor);
                    int maxOffsetX = std::max(0, int(habitatWidth) - scaledWidth);
                    int maxOffsetY = std::max(0, int(habitatHeight) - scaledHeight);
                    std::hash<std::string> hasher;
                    std::string key = std::to_string(m_gridX) + "_" + std::to_string(m_gridY) + "_" + std::to_string(j);
                    size_t hashVal = hasher(key);
                    int offsetX = hashVal % (maxOffsetX + 1);
                    int offsetY = (hashVal / 100) % (maxOffsetY + 1);
                    animalSprite.setPosition(habitatX + offsetX, habitatY + offsetY);
                    window.draw(animalSprite);
                }
            }
        }
        
        void Habitat::highlightHabitat(sf::RenderWindow& window, int tileSize, const sf::Color& color, float outlineThickness) const {
            if (m_gridX == -1 || m_gridY == -1)
                return;
                
            sf::RectangleShape highlight;
            highlight.setSize(sf::Vector2f(3 * tileSize, 3 * tileSize));
            highlight.setPosition(m_gridX * tileSize, m_gridY * tileSize);
            highlight.setFillColor(sf::Color(color.r, color.g, color.b, 80));
            highlight.setOutlineColor(color);
            highlight.setOutlineThickness(outlineThickness);
            window.draw(highlight);
        }

std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
{
    os << "Habitat: " << habitat.m_type << "\n"
       << "  Capacity: " << habitat.m_capacity << "\n"
       << "  Cleanliness: " << (habitat.m_cleanlinessLevel * 100) << "%" << "\n"
       << "  Price: $" << habitat.m_price << "\n"
       << "  Animals: " << habitat.m_animals.size();
    return os;
}



void Habitat::setPosition(int x, int y)
{
    m_gridX = x;
    m_gridY = y;
}

int Habitat::getGridX() const
{
    return m_gridX;
}

int Habitat::getGridY() const
{
    return m_gridY;
}

bool Habitat::overlaps(const Habitat &other) const
{
    if (m_gridX == -1 || other.m_gridX == -1)
        return false;
    return !(m_gridX + 3 <= other.m_gridX || other.m_gridX + 3 <= m_gridX || m_gridY + 3 <= other.m_gridY || other.m_gridY + 3 <= m_gridY);
}

bool Habitat::isValidPosition(int gridWidth, int gridHeight) const
{
    return m_gridX >= 1 && m_gridY >= 1 && (m_gridX + 3) <= (gridWidth - 1) && (m_gridY + 3) <= (gridHeight - 1);
}

std::vector<std::string> Habitat::getAllowedAnimals(const std::string &habitatType)
{
    if (habitatType == "Forest")
        return {"bear", "fox", "wolf"};
    else if (habitatType == "Desert")
        return {"camel", "coyote", "scorpion"};
    else if (habitatType == "Mountain")
        return {"eagle", "goat", "yak"};
    else if (habitatType == "Ocean")
        return {"dolphin", "octopus", "seaturtle"};
    else if (habitatType == "Savanna")
        return {"elephant", "lion", "zebra"};
    return {};
}
