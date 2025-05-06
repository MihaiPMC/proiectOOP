#include "../include/Zoo.hpp"
#include <algorithm>
#include <random>

Zoo::Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float budget)
    : m_name(name), m_habitats(habitats), m_visitorCount(visitor_count), m_isOpen(is_open), m_budget(budget)
{
}

Zoo::Zoo(const Zoo &other)
    : m_name(other.m_name), m_habitats(other.m_habitats), m_visitorCount(other.m_visitorCount),
      m_isOpen(other.m_isOpen), m_budget(other.m_budget)
{
}

Zoo::Zoo(Zoo &&other) noexcept
    : m_name(std::move(other.m_name)), m_habitats(std::move(other.m_habitats)), m_visitorCount(other.m_visitorCount),
      m_isOpen(other.m_isOpen), m_budget(other.m_budget)
{
}

Zoo &Zoo::operator=(const Zoo &other)
{
    if (this == &other)
        return *this;
    m_name = other.m_name;
    m_habitats = other.m_habitats;
    m_visitorCount = other.m_visitorCount;
    m_isOpen = other.m_isOpen;
    m_budget = other.m_budget;
    return *this;
}

Zoo &Zoo::operator=(Zoo &&other) noexcept
{
    if (this == &other)
        return *this;
    m_name = std::move(other.m_name);
    m_habitats = std::move(other.m_habitats);
    m_visitorCount = other.m_visitorCount;
    m_isOpen = other.m_isOpen;
    m_budget = other.m_budget;
    return *this;
}

const std::string &Zoo::getName() const
{
    return m_name;
}

void Zoo::setName(const std::string &newName)
{
    m_name = newName;
}

const std::vector<Habitat> &Zoo::getHabitats() const
{
    return m_habitats;
}

void Zoo::addHabitats(const std::vector<Habitat> &newHabitats)
{
    for (const auto &habitat: newHabitats)
        m_habitats.push_back(habitat);
}

void Zoo::addHabitats(const Habitat &habitat)
{
    m_habitats.push_back(habitat);
    spendMoney(habitat.getPrice());
}

int Zoo::getVisitorCount() const
{
    return m_visitorCount;
}

void Zoo::setVisitorCount(int visitor_count)
{
    m_visitorCount = visitor_count;
}

bool Zoo::getIsOpen() const
{
    return m_isOpen;
}

void Zoo::setIsOpen(bool is_open)
{
    m_isOpen = is_open;
}

float Zoo::getBudget() const
{
    return m_budget;
}

void Zoo::setBudget(float newBudget)
{
    m_budget = newBudget;
}

std::ostream &operator<<(std::ostream &os, const Zoo &zoo)
{
    os << "Zoo: " << zoo.m_name << "\n"
            << "  Habitats: " << zoo.m_habitats.size() << "\n"
            << "  Visitor Count: " << zoo.m_visitorCount << "\n"
            << "  Status: " << (zoo.m_isOpen ? "Open" : "Closed") << "\n"
            << "  Budget: $" << zoo.m_budget;
    return os;
}

bool Zoo::spendMoney(float amount)
{
    if (m_budget >= amount) {
        m_budget -= amount;
        return true;
    }
    return false;
}

bool Zoo::canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const
{
    if (gridX <= 0 || gridY <= 0 || (gridX + 3) >= (gridWidth - 1) || (gridY + 3) >= (gridHeight - 1)) {
        return false;
    }

    for (const auto &habitat : m_habitats) {
        if (habitat.getGridX() != -1) {
            if (!(gridX + 3 <= habitat.getGridX() || habitat.getGridX() + 3 <= gridX ||
                  gridY + 3 <= habitat.getGridY() || habitat.getGridY() + 3 <= gridY)) {
                return false;
            }
        }
    }

    return true;
}

bool Zoo::buildHabitatAt(const std::string& type, int gridX, int gridY, int gridWidth, int gridHeight) {
    if (!canBuildAt(gridX, gridY, gridWidth, gridHeight)) {
        return false;
    }
    
    Habitat newHabitat(type, {});
    float habitatPrice = newHabitat.getPrice();

    if (!spendMoney(habitatPrice)) {
        std::cout << "Not enough budget to build a habitat!" << std::endl;
        return false;
    }
    
    newHabitat.setPosition(gridX, gridY);
    m_habitats.push_back(newHabitat);
    
    std::cout << "Habitat " << type << " built successfully at position (" << gridX << "," << gridY << ")" << std::endl;
    return true;
}

int Zoo::findHabitatAt(int gridX, int gridY) const {
    for (size_t i = 0; i < m_habitats.size(); i++) {
        const Habitat& habitat = m_habitats[i];
        int hx = habitat.getGridX();
        int hy = habitat.getGridY();
        
        if (gridX >= hx && gridX < hx + 3 &&
            gridY >= hy && gridY < hy + 3) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Zoo::addAnimalTo(int habitatIndex, const std::string& animalType)
{
    if (habitatIndex < 0 || habitatIndex >= static_cast<int>(m_habitats.size())) {
        return false;
    }
    
    auto newAnimal = Animal::createRandomAnimal(animalType);
    float animalPrice = newAnimal->getPrice();

    if (!spendMoney(animalPrice)) {
        std::cout << "Not enough budget to add an animal!" << std::endl;
        return false;
    }
    
    m_habitats[habitatIndex].addAnimal(newAnimal);

    std::cout << "Added " << newAnimal->getName() << " the " << animalType
              << " to " << m_habitats[habitatIndex].getType() << " habitat!" << std::endl;
    return true;
}
