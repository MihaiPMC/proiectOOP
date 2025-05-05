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

void Zoo::feedAnimals(float foodAmountPerAnimal, float costPerAnimal)
{
    int totalAnimals = 0;
    float totalCost = 0.0f;
    for (const auto &habitat: m_habitats)
        totalAnimals += habitat.getAnimals().size();
    totalCost = totalAnimals * costPerAnimal;
    if (m_budget < totalCost)
    {
        std::cout << "Not enough budget to feed all animals!" << std::endl;
        return;
    }
    for (const auto &habitat: m_habitats)
    {
        for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
            animal.setHunger(std::min(1.0f, animal.getHunger() + foodAmountPerAnimal));
    }
    m_budget -= totalCost;
    std::cout << "Fed " << totalAnimals << " animals for a total cost of $" << totalCost << std::endl;
    std::cout << "Remaining budget: $" << m_budget << std::endl;
}

void Zoo::updateHunger(float deltaTime)
{
    for (const auto &habitat: m_habitats)
    {
        for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
            animal.updateHunger(deltaTime);
    }
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

Zoo Zoo::initializeZoo()
{
    std::cout << "Welcome to the Zoo Management System!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "What is the name of the zoo?" << std::endl;
    std::string zooName;
    std::cin.ignore();
    std::getline(std::cin, zooName);
    std::cout << "Zoo name: " << zooName << std::endl;
    Zoo myZoo(zooName, {}, 0, true);
    std::cout << "Zoo created!" << std::endl;
    std::cout << "Your budget is $" << myZoo.getBudget() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    return myZoo;
}

void Zoo::createInitialHabitats()
{
    std::cout << "Now let's add some habitats!" << std::endl;
    std::cout << "Habitat price is $10,000." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    int habitatsCount;
    do
    {
        std::cout << "How many habitats do you want to add? ";
        std::cin >> habitatsCount;
        if (habitatsCount <= 0)
            std::cout << "You need to add at least one habitat!" << std::endl;
        else if (habitatsCount > 5)
            std::cout << "You can only add up to 5 habitats at a time." << std::endl;
    } while (habitatsCount <= 0 || habitatsCount > 5);
    std::cout << "You have chosen to add " << habitatsCount << " habitats." << std::endl;
    for (int i = 0; i < habitatsCount; i++)
    {
        std::string habitatTypeName = Habitat::selectHabitatType();
        Habitat newHabitat("", {});
        newHabitat.setType(habitatTypeName);
        std::cout << "Habitat added: " << newHabitat.getType() << std::endl;
        std::cout << "You have $" << m_budget << " left." << std::endl;
        int animalCount;
        std::cout << "How many animals would you like to add to this " << habitatTypeName << " habitat? (0-5): ";
        std::cin >> animalCount;
        newHabitat.addRandomAnimals(animalCount, m_budget);
        addHabitats(newHabitat);
    }
}

void Zoo::addNewHabitat()
{
    std::cout << "Habitat price is $10,000." << std::endl;
    if (m_budget < 10000)
    {
        std::cout << "Not enough budget to add a habitat!" << std::endl;
        return;
    }
    std::string habitatTypeName = Habitat::selectHabitatType();
    Habitat newHabitat("", {});
    newHabitat.setType(habitatTypeName);
    addHabitats(newHabitat);
    std::cout << "Habitat added: " << habitatTypeName << std::endl;
    std::cout << "You have $" << m_budget << " left." << std::endl;
    std::cout << "Would you like to add animals to this new habitat? (1 for Yes, 0 for No): ";
    int addAnimals;
    std::cin >> addAnimals;
    if (addAnimals == 1)
    {
        std::cout << "How many animals would you like to add? (0-5): ";
        int animalCount;
        std::cin >> animalCount;
        auto &habitats = const_cast<std::vector<Habitat> &>(getHabitats());
        habitats.back().addRandomAnimals(animalCount, m_budget);
    }
}

void Zoo::addAnimalsToExistingHabitat()
{
    auto &habitats = const_cast<std::vector<Habitat> &>(getHabitats());
    if (habitats.empty())
    {
        std::cout << "No habitats available!" << std::endl;
        return;
    }
    std::cout << "Select a habitat to add animals to:" << std::endl;
    for (size_t h = 0; h < habitats.size(); h++)
    {
        std::cout << (h + 1) << ". " << habitats[h].getType()
                << " (Animals: " << habitats[h].getAnimals().size() << ")" << std::endl;
    }
    size_t habitatChoice;
    std::cin >> habitatChoice;
    if (habitatChoice < 1 || habitatChoice > habitats.size())
    {
        std::cout << "Invalid habitat choice!" << std::endl;
        return;
    }
    Habitat &selectedHabitat = habitats[habitatChoice - 1];
    std::cout << "How many animals would you like to add? (0-5): ";
    int animalCount;
    std::cin >> animalCount;
    selectedHabitat.addRandomAnimals(animalCount, m_budget);
}

void Zoo::handleDailyManagement()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Daily Management Options:" << std::endl;
    std::cout << "1. Feed animals" << std::endl;
    std::cout << "2. Add a new habitat" << std::endl;
    std::cout << "3. Add animals to existing habitat" << std::endl;
    std::cout << "4. Continue to next day" << std::endl;
    std::cout << "Enter your choice: ";
    int dailyChoice;
    std::cin >> dailyChoice;
    switch (dailyChoice)
    {
        case 1:
            feedAnimals();
            break;
        case 2:
            addNewHabitat();
            break;
        case 3:
            addAnimalsToExistingHabitat();
            break;
        case 4:
            std::cout << "Continuing to next day..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Continuing to next day..." << std::endl;
            break;
    }
}

void Zoo::processDayEnd(int dayNumber)
{
    int habitatCount = m_habitats.size();
    int totalAnimals = 0;
    for (const auto &habitat: m_habitats)
        totalAnimals += habitat.getAnimals().size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> variation(-5, 5);
    int baseVisitors = habitatCount * 10 + totalAnimals * 5;
    int visitors = std::max(0, baseVisitors + variation(gen));
    const int ticketPrice = 15;
    int revenue = visitors * ticketPrice;
    m_visitorCount = visitors;
    m_budget += revenue;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Day " << dayNumber << " Summary:" << std::endl;
    std::cout << visitors << " visitors came in, earning $" << revenue << std::endl;
    std::cout << "Current budget: $" << m_budget << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Zoo::displayZooStatus() const
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Your zoo is ready!" << std::endl;
    std::cout << *this << std::endl;
    std::cout << "Here are your habitats and animals:" << std::endl;
    for (const auto &habitat: m_habitats)
    {
        std::cout << habitat << std::endl;
        std::cout << "Animals in this habitat:" << std::endl;
        for (const auto &animal: habitat.getAnimals())
            std::cout << "  - " << animal.getName() << " the " << animal.getSpecies() << std::endl;
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

void Zoo::runSimulation(int days)
{
    std::cout << "You have chosen to simulate " << days << " days." << std::endl;
    for (int i = 0; i < days; i++)
    {
        std::cout << "Day " << (i + 1) << " of simulation." << std::endl;
        updateHunger(1.0f);
        for (auto &habitat: const_cast<std::vector<Habitat> &>(getHabitats()))
            habitat.updateCleanliness(1.0f);
        handleDailyManagement();
        processDayEnd(i + 1);
    }
    std::cout << "Simulation is over" << std::endl;
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

bool Zoo::addAnimalTo(int habitatIndex, const std::string& animalType) {
    if (habitatIndex < 0 || habitatIndex >= static_cast<int>(m_habitats.size())) {
        return false;
    }
    
    Animal newAnimal = Animal::createRandomAnimal(animalType);
    
    auto& habitats = const_cast<std::vector<Habitat>&>(getHabitats());
    habitats[habitatIndex].addAnimals(newAnimal);
    
    return true;
}
