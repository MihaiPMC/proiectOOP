#include "../include/Habitat.hpp"
#include "../include/HabitatException.hpp"
#include "../include/AnimalException.hpp"

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

std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
{
    os << "Habitat: " << habitat.m_type << "\n"
       << "  Capacity: " << habitat.m_capacity << "\n"
       << "  Cleanliness: " << (habitat.m_cleanlinessLevel * 100) << "%" << "\n"
       << "  Price: $" << habitat.m_price << "\n"
       << "  Animals: " << habitat.m_animals.size();
    return os;
}

std::map<std::string, std::vector<std::string>> Habitat::s_habitatSpecies = {
    {"Forest", {"Bear", "Wolf", "Fox", "Deer", "Owl", "bear", "wolf", "fox", "deer", "owl"}},
    {"Desert", {"Camel", "Scorpion", "Rattlesnake", "Coyote", "Lizard", "camel", "scorpion", "rattlesnake", "coyote", "lizard"}},
    {"Ocean", {"Dolphin", "Shark", "Octopus", "Penguin", "Sea Turtle", "dolphin", "shark", "octopus", "penguin", "sea turtle", "seaturtle"}},
    {"Savanna", {"Lion", "Elephant", "Zebra", "Giraffe", "Cheetah", "lion", "elephant", "zebra", "giraffe", "cheetah"}},
    {"Mountain", {"Eagle", "Mountain Lion", "Goat", "Yak", "Snow Leopard", "eagle", "mountain lion", "goat", "yak", "snow leopard"}}
};

std::map<std::string, std::vector<std::string>> Habitat::getHabitatSpecies()
{
    return s_habitatSpecies;
}

std::string Habitat::selectHabitatType()
{
    int habitatType;
    do
    {
        std::cout << "What habitat do you want to add? 1. Forest 2. Desert 3. Ocean 4. Savanna 5. Mountain" << std::endl;
        std::cin >> habitatType;
        if (habitatType < 1 || habitatType > 5)
            std::cout << "Invalid habitat type! Please choose again." << std::endl;
    } while (habitatType < 1 || habitatType > 5);
    switch (habitatType)
    {
        case 1: return "Forest";
        case 2: return "Desert";
        case 3: return "Ocean";
        case 4: return "Savanna";
        case 5: return "Mountain";
        default: return "Forest";
    }
}

void Habitat::addRandomAnimals(int count, float &budget)
{
    if (count < 0 || count > 5)
    {
        std::cout << "Invalid number of animals! Using 0 instead." << std::endl;
        return;
    }
    std::cout << "Animal price is $1000." << std::endl;
    for (int j = 0; j < count; j++)
    {
        if (budget < 1000)
        {
            std::cout << "Not enough budget to add more animals!" << std::endl;
            break;
        }
        std::cout << "Available species for " << m_type << " habitat:" << std::endl;
        const std::vector<std::string> &species = s_habitatSpecies[m_type];
        for (size_t k = 0; k < species.size(); k++)
        {
            std::cout << (k + 1) << ". " << species[k] << std::endl;
        }
        int speciesChoice;
        std::cout << "Choose a species (1-" << species.size() << "): ";
        std::cin >> speciesChoice;
        if (speciesChoice < 1 || speciesChoice > static_cast<int>(species.size()))
        {
            std::cout << "Invalid choice. Defaulting to first species." << std::endl;
            speciesChoice = 1;
        }
        auto newAnimal = Animal::createRandomAnimal(species[speciesChoice - 1]);
        addAnimal(newAnimal);
        budget -= newAnimal->getPrice();
        std::cout << "Added " << newAnimal->getName() << " the " << newAnimal->getSpecies()
                  << " to " << m_type << " habitat!" << std::endl;
        std::cout << "Remaining budget: $" << budget << std::endl;
    }
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
