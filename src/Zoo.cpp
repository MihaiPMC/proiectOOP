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
    m_budget -= habitat.getPrice();
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


bool Zoo::buildHabitatAt(const std::string& type, int gridX, int gridY, int gridWidth, int gridHeight) {
    if (!canBuildAt(gridX, gridY, gridWidth, gridHeight)) {
        return false;
    }
    
    Habitat newHabitat(type, {});
    newHabitat.setPosition(gridX, gridY);
    addHabitats(newHabitat);
    return true;
}

bool Zoo::canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const {
    Habitat temp("", {});
    temp.setPosition(gridX, gridY);
    
    if (!temp.isValidPosition(gridWidth, gridHeight)) {
        return false;
    }
    
    for (const auto& habitat : m_habitats) {
        if (temp.overlaps(habitat)) {
            return false;
        }
    }
    
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
    
    if (m_budget < 2000) {
        std::cout << "Not enough budget to add an animal!" << std::endl;
        return false;
    }
    
    auto newAnimal = Animal::createRandomAnimal(animalType);
    m_habitats[habitatIndex].addAnimal(newAnimal);
    m_budget -= 2000;
    
    return true;
}

