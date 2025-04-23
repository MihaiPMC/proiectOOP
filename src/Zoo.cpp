#include "../include/Zoo.hpp"
#include <algorithm>
#include <random>

Zoo::Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float budget)
    : name(name),
      habitats(habitats),
      visitorCount(visitor_count),
      isOpen(is_open),
      budget(budget)
{
}

Zoo::Zoo(const Zoo &other)
    : name(other.name),
      habitats(other.habitats),
      visitorCount(other.visitorCount),
      isOpen(other.isOpen),
      budget(other.budget)
{
}

Zoo::Zoo(Zoo &&other) noexcept
    : name(std::move(other.name)),
      habitats(std::move(other.habitats)),
      visitorCount(other.visitorCount),
      isOpen(other.isOpen),
      budget(other.budget)
{
}

Zoo &Zoo::operator=(const Zoo &other)
{
    if (this == &other)
        return *this;
    name = other.name;
    habitats = other.habitats;
    visitorCount = other.visitorCount;
    isOpen = other.isOpen;
    budget = other.budget;
    return *this;
}

Zoo &Zoo::operator=(Zoo &&other) noexcept
{
    if (this == &other)
        return *this;
    name = std::move(other.name);
    habitats = std::move(other.habitats);
    visitorCount = other.visitorCount;
    isOpen = other.isOpen;
    budget = other.budget;
    return *this;
}

const std::string &Zoo::getName() const
{
    return name;
}

void Zoo::setName(const std::string &newName)
{
    this->name = newName;
}

const std::vector<Habitat> &Zoo::getHabitats() const
{
    return habitats;
}

void Zoo::addHabitats(const std::vector<Habitat> &newHabitats)
{
    for (const auto &habitat: newHabitats)
    {
        this->habitats.push_back(habitat);
    }
}

void Zoo::addHabitats(const Habitat &habitat)
{
    this->habitats.push_back(habitat);
    this->budget -= habitat.getPrice();
}

int Zoo::getVisitorCount() const
{
    return visitorCount;
}

void Zoo::setVisitorCount(int visitor_count)
{
    visitorCount = visitor_count;
}

bool Zoo::getIsOpen() const
{
    return isOpen;
}

void Zoo::setIsOpen(bool is_open)
{
    isOpen = is_open;
}

float Zoo::getBudget() const
{
    return budget;
}

void Zoo::setBudget(float newBudget)
{
    this->budget = newBudget;
}

void Zoo::feedAnimals(float foodAmountPerAnimal, float costPerAnimal)
{
    int totalAnimals = 0;
    float totalCost = 0.0f;

    for (const auto& habitat : habitats)
    {
        totalAnimals += habitat.getAnimals().size();
    }

    totalCost = totalAnimals * costPerAnimal;

    if (budget < totalCost)
    {
        std::cout << "Not enough budget to feed all animals!" << std::endl;
        return;
    }

    for (const auto& habitat : habitats)
    {
        for (auto& animal : const_cast<std::vector<Animal>&>(habitat.getAnimals()))
        {
            animal.setHunger(std::min(1.0f, animal.getHunger() + foodAmountPerAnimal));
        }
    }

    budget -= totalCost;

    std::cout << "Fed " << totalAnimals << " animals for a total cost of $" << totalCost << std::endl;
    std::cout << "Remaining budget: $" << budget << std::endl;
}

void Zoo::updateHunger(float deltaTime)
{
    for (const auto &habitat: habitats)
    {
        for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
        {
            animal.updateHunger(deltaTime);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Zoo &zoo)
{
    os << "Zoo: " << zoo.name << "\n"
       << "  Habitats: " << zoo.habitats.size() << "\n"
       << "  Visitor Count: " << zoo.visitorCount << "\n"
       << "  Status: " << (zoo.isOpen ? "Open" : "Closed") << "\n"
       << "  Budget: $" << zoo.budget;
    return os;
}

Zoo Zoo::initializeZoo() {
    std::cout << "Welcome to the Zoo Management System!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "What is the name of the zoo?" << std::endl;
    std::string zooName;
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, zooName);
    std::cout << "Zoo name: " << zooName << std::endl;

    Zoo myZoo(zooName, {}, 0, true);
    std::cout << "Zoo created!" << std::endl;
    std::cout << "Your budget is $" << myZoo.getBudget() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return myZoo;
}

void Zoo::createInitialHabitats() {
    std::cout << "Now let's add some habitats!" << std::endl;
    std::cout << "Habitat price is $10,000." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    int habitatsCount;
    do {
        std::cout << "How many habitats do you want to add? ";
        std::cin >> habitatsCount;

        if (habitatsCount <= 0) {
            std::cout << "You need to add at least one habitat!" << std::endl;
        } else if (habitatsCount > 5) {
            std::cout << "You can only add up to 5 habitats at a time." << std::endl;
        }
    } while (habitatsCount <= 0 || habitatsCount > 5);

    std::cout << "You have chosen to add " << habitatsCount << " habitats." << std::endl;

    for (int i = 0; i < habitatsCount; i++) {
        std::string habitatTypeName = Habitat::selectHabitatType();
        Habitat newHabitat("", {});
        newHabitat.setType(habitatTypeName);

        std::cout << "Habitat added: " << newHabitat.getType() << std::endl;
        std::cout << "You have $" << this->budget << " left." << std::endl;

        int animalCount;
        std::cout << "How many animals would you like to add to this " << habitatTypeName << " habitat? (0-5): ";
        std::cin >> animalCount;

        newHabitat.addRandomAnimals(animalCount, this->budget);
        this->addHabitats(newHabitat);
    }
}

void Zoo::addNewHabitat() {
    std::cout << "Habitat price is $10,000." << std::endl;
    if (this->budget < 10000) {
        std::cout << "Not enough budget to add a habitat!" << std::endl;
        return;
    }

    std::string habitatTypeName = Habitat::selectHabitatType();

    Habitat newHabitat("", {});
    newHabitat.setType(habitatTypeName);
    this->addHabitats(newHabitat);

    std::cout << "Habitat added: " << habitatTypeName << std::endl;
    std::cout << "You have $" << this->budget << " left." << std::endl;

    std::cout << "Would you like to add animals to this new habitat? (1 for Yes, 0 for No): ";
    int addAnimals;
    std::cin >> addAnimals;

    if (addAnimals == 1) {
        std::cout << "How many animals would you like to add? (0-5): ";
        int animalCount;
        std::cin >> animalCount;

        auto& habitats = const_cast<std::vector<Habitat>&>(this->getHabitats());
        habitats.back().addRandomAnimals(animalCount, this->budget);
    }
}

void Zoo::addAnimalsToExistingHabitat() {
    auto& habitats = const_cast<std::vector<Habitat>&>(this->getHabitats());
    if (habitats.empty()) {
        std::cout << "No habitats available!" << std::endl;
        return;
    }

    std::cout << "Select a habitat to add animals to:" << std::endl;
    for (size_t h = 0; h < habitats.size(); h++) {
        std::cout << (h + 1) << ". " << habitats[h].getType()
                  << " (Animals: " << habitats[h].getAnimals().size() << ")" << std::endl;
    }

    size_t habitatChoice;
    std::cin >> habitatChoice;

    if (habitatChoice < 1 || habitatChoice > habitats.size()) {
        std::cout << "Invalid habitat choice!" << std::endl;
        return;
    }

    Habitat& selectedHabitat = habitats[habitatChoice - 1];

    std::cout << "How many animals would you like to add? (0-5): ";
    int animalCount;
    std::cin >> animalCount;

    selectedHabitat.addRandomAnimals(animalCount, this->budget);
}

void Zoo::handleDailyManagement() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Daily Management Options:" << std::endl;
    std::cout << "1. Feed animals" << std::endl;
    std::cout << "2. Add a new habitat" << std::endl;
    std::cout << "3. Add animals to existing habitat" << std::endl;
    std::cout << "4. Continue to next day" << std::endl;
    std::cout << "Enter your choice: ";

    int dailyChoice;
    std::cin >> dailyChoice;

    switch (dailyChoice) {
        case 1:
            this->feedAnimals();
            break;
        case 2:
            this->addNewHabitat();
            break;
        case 3:
            this->addAnimalsToExistingHabitat();
            break;
        case 4:
            std::cout << "Continuing to next day..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Continuing to next day..." << std::endl;
            break;
    }
}

void Zoo::processDayEnd(int dayNumber) {
    int habitatCount = this->habitats.size();
    int totalAnimals = 0;
    for (const auto &habitat : this->habitats) {
        totalAnimals += habitat.getAnimals().size();
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> variation(-5, 5);

    int baseVisitors = habitatCount * 10 + totalAnimals * 5;
    int visitors = std::max(0, baseVisitors + variation(gen));
    const int ticketPrice = 15;
    int revenue = visitors * ticketPrice;

    this->visitorCount = visitors;
    this->budget += revenue;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Day " << dayNumber << " Summary:" << std::endl;
    std::cout << visitors << " visitors came in, earning $" << revenue << std::endl;
    std::cout << "Current budget: $" << this->budget << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Zoo::displayZooStatus() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Your zoo is ready!" << std::endl;
    std::cout << *this << std::endl;

    std::cout << "Here are your habitats and animals:" << std::endl;
    for (const auto& habitat : this->habitats) {
        std::cout << habitat << std::endl;
        std::cout << "Animals in this habitat:" << std::endl;
        for (const auto& animal : habitat.getAnimals()) {
            std::cout << "  - " << animal.getName() << " the " << animal.getSpecies() << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
}

void Zoo::runSimulation(int days) {
    std::cout << "You have chosen to simulate " << days << " days." << std::endl;

    for (int i = 0; i < days; i++) {
        std::cout << "Day " << (i + 1) << " of simulation." << std::endl;
        this->updateHunger(1.0f);

        for (auto& habitat : const_cast<std::vector<Habitat>&>(this->getHabitats())) {
            habitat.updateCleanliness(1.0f);
        }

        this->handleDailyManagement();
        this->processDayEnd(i + 1);
    }

    std::cout << "Simulation is over" << std::endl;
}

