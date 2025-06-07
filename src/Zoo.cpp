#include "../include/Zoo.hpp"
#include "../include/exception/BudgetException.hpp"
#include "../include/exception/HabitatException.hpp"
#include "../include/exception/AnimalException.hpp"
#include <algorithm>
#include <random>
#include <sstream>

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

void Zoo::syncInventoryWithHabitats() {
    m_allAnimalsInventory.clear();

    for (const auto& habitat : m_habitats) {
        const auto& animals = habitat.getAnimals();
        for (const auto& animal : animals) {
            m_allAnimalsInventory.addItem(animal);
        }
    }

    m_habitatInventory.clear();
    for (const auto& habitat : m_habitats) {
        auto habitatPtr = std::make_shared<Habitat>(habitat);
        m_habitatInventory.addItem(habitatPtr);
    }
}

void Zoo::displayAllInventories() const {
    m_allAnimalsInventory.displayInventory();
    m_habitatInventory.displayInventory();
}

std::string Zoo::getInventorySummary() const {
    std::ostringstream oss;
    oss << "=== " << m_allAnimalsInventory.getName() << " (" << m_allAnimalsInventory.getCount()
        << "/" << m_allAnimalsInventory.getCapacity() << ") ===\n";
    size_t idx = 1;
    for (const auto &animal : m_allAnimalsInventory.getItems()) {
        if (animal) {
            oss << idx++ << ". " << *animal << "\n";
        }
    }
    oss << "\n=== " << m_habitatInventory.getName() << " (" << m_habitatInventory.getCount()
        << "/" << m_habitatInventory.getCapacity() << ") ===\n";
    idx = 1;
    for (const auto &hab : m_habitatInventory.getItems()) {
        if (hab) {
            oss << idx++ << ". " << *hab << "\n";
        }
    }
    return oss.str();
}

bool Zoo::spendMoney(float amount)
{
    if (m_budget >= amount)
    {
        m_budget -= amount;
        return true;
    }
    throw BudgetException("Not enough funds to spend $" + std::to_string(amount) +
                          ". Current budget: $" + std::to_string(m_budget));
}

bool Zoo::canBuildAt(int gridX, int gridY, int gridWidth, int gridHeight) const
{
    if (gridX < 1 || gridY < 1 || (gridX + 3) > (gridWidth - 1) || (gridY + 3) > (gridHeight - 1))
    {
        std::cout << "Cannot build at (" << gridX << "," << gridY << "): Outside of buildable area" << std::endl;
        return false;
    }

    for (const auto &habitat: m_habitats)
    {
        if (habitat.getGridX() != -1)
        {
            int hx = habitat.getGridX();
            int hy = habitat.getGridY();


            bool overlapsX = (gridX < hx + 3) && (gridX + 3 > hx);
            bool overlapsY = (gridY < hy + 3) && (gridY + 3 > hy);

            if (overlapsX && overlapsY)
            {
                std::cout << "Cannot build at (" << gridX << "," << gridY
                        << "): Overlaps with habitat at (" << hx << "," << hy << ")" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Position (" << gridX << "," << gridY << ") is valid for habitat placement" << std::endl;
    return true;
}

bool Zoo::buildHabitatAt(const std::string &type, int gridX, int gridY, int gridWidth, int gridHeight)
{
    std::cout << "Attempting to build " << type << " habitat at position (" << gridX << "," << gridY << ")" <<
            std::endl;

    if (!canBuildAt(gridX, gridY, gridWidth, gridHeight))
    {
        throw HabitatException("Cannot place habitat at position (" + std::to_string(gridX) +
                               "," + std::to_string(gridY) + ") - invalid location");
    }

    Habitat newHabitat(type, {});
    float habitatPrice = newHabitat.getPrice();

    try
    {
        spendMoney(habitatPrice);
        newHabitat.setPosition(gridX, gridY);
        m_habitats.push_back(newHabitat);

        std::cout << "Habitat " << type << " built successfully at position (" << gridX << "," << gridY << ")" <<
                std::endl;
        return true;
    } catch (const BudgetException &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

int Zoo::findHabitatAt(int gridX, int gridY) const
{
    for (size_t i = 0; i < m_habitats.size(); i++)
    {
        const Habitat &habitat = m_habitats[i];
        int hx = habitat.getGridX();
        int hy = habitat.getGridY();

        if (gridX >= hx && gridX < hx + 3 &&
            gridY >= hy && gridY < hy + 3)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Zoo::moveHabitat(size_t habitatIndex, int newX, int newY)
{
    if (habitatIndex < m_habitats.size())
    {
        m_habitats[habitatIndex].setPosition(newX, newY);
    }
}

bool Zoo::addAnimalTo(int habitatIndex, const std::string &animalType)
{
    if (habitatIndex < 0 || habitatIndex >= static_cast<int>(m_habitats.size()))
    {
        throw HabitatException("Invalid habitat index: " + std::to_string(habitatIndex));
    }

    auto newAnimal = Animal::createRandomAnimal(animalType);
    if (!newAnimal)
    {
        throw AnimalException("Failed to create animal of type: " + animalType);
    }

    float animalPrice = newAnimal->getPrice();

    try
    {
        spendMoney(animalPrice);

        try
        {
            m_habitats[habitatIndex].addAnimal(newAnimal);
            std::cout << "Added " << newAnimal->getName() << " the " << animalType
                    << " to " << m_habitats[habitatIndex].getType() << " habitat!" << std::endl;
            return true;
        } catch (const AnimalException &)
        {
            m_budget += animalPrice;
            throw;
        }
    } catch (const BudgetException &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool Zoo::deleteHabitatAt(int habitatIndex)
{
    if (habitatIndex < 0 || habitatIndex >= static_cast<int>(m_habitats.size()))
    {
        throw HabitatException("Invalid habitat index: " + std::to_string(habitatIndex));
    }

    float refundAmount = calculateRefund(m_habitats[habitatIndex].getPrice());

    std::string habitatType = m_habitats[habitatIndex].getType();

    m_habitats.erase(m_habitats.begin() + habitatIndex);

    m_budget += refundAmount;

    std::cout << "Deleted " << habitatType << " habitat and received $" << refundAmount << " refund." << std::endl;
    return true;
}

float Zoo::calculateRefund(float originalPrice) const
{
    return originalPrice * 0.5f;
}

bool Zoo::loadTexture(sf::Texture &texture, const std::string &primaryPath, const std::string &backupPath,
                       sf::Color fallbackColor)
{
    if (texture.loadFromFile(primaryPath))
    {
        std::cout << "Loaded texture from " << primaryPath << std::endl;
        return true;
    }
    if (texture.loadFromFile(backupPath))
    {
        std::cout << "Loaded texture from " << backupPath << std::endl;
        return true;
    }
    sf::Image fallbackImage;
    fallbackImage.create(64, 64, fallbackColor);
    texture.loadFromImage(fallbackImage);
    std::cout << "Using fallback texture" << std::endl;
    return false;
}

void Zoo::nameInput(sf::RenderWindow& window, sf::Font& font, std::string& zooName, bool& nameEntered)
{
    sf::Text prompt;
    sf::Text inputText;

    prompt.setFont(font);
    prompt.setCharacterSize(30);
    prompt.setFillColor(sf::Color::White);
    prompt.setString("Hello. Welcome to Zoo Tycoon. Please enter your zoo name:");

    inputText.setFont(font);
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::Yellow);

    while (window.isOpen() && !nameEntered)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (!zooName.empty())
                        zooName.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != 13)
                    zooName += static_cast<char>(event.text.unicode);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (!zooName.empty())
                    nameEntered = true;
            }
        }
        inputText.setString(zooName);
        prompt.setPosition(window.getSize().x / 2.f - prompt.getLocalBounds().width / 2.f, window.getSize().y / 3.f);
        inputText.setPosition(window.getSize().x / 2.f - inputText.getLocalBounds().width / 2.f, window.getSize().y / 2.f);
        window.clear(sf::Color(50, 50, 50));
        window.draw(prompt);
        window.draw(inputText);
        window.display();
    }
}

void Zoo::showTutorial(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text tutorial;
    tutorial.setFont(font);
    tutorial.setCharacterSize(24);
    tutorial.setFillColor(sf::Color::White);
    tutorial.setString(
        "Tutorial:\nClick 'Build Habitat' to construct a habitat,\nthen click 'Add Animal' to add animals.\nPress any key to continue.");
    tutorial.setPosition(window.getSize().x / 2.f - tutorial.getLocalBounds().width / 2.f, window.getSize().y / 3.f);

    bool tutorialDone = false;
    while (window.isOpen() && !tutorialDone)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                tutorialDone = true;
            }
        }
        window.clear(sf::Color(50, 50, 50));
        window.draw(tutorial);
        window.display();
    }
}

void Zoo::renderHabitats(sf::RenderWindow& window, int tileSize, const std::map<std::string, sf::Texture>& habitatTextures,
                         const std::map<std::string, sf::Texture>& animalTextures) const
{
    for (const auto& habitat : m_habitats) {
        if (habitat.getGridX() != -1) {
            auto it = habitatTextures.find(habitat.getType());
            if (it != habitatTextures.end()) {
                habitat.renderHabitat(window, tileSize, it->second);
                habitat.renderAnimals(window, tileSize, animalTextures);
            }
        }
    }
}

void Zoo::printAnimalDetails() const {
    std::cout << "\nPrinting all animal details using template function:" << std::endl;
    m_allAnimalsInventory.forEachItem([](const std::shared_ptr<Animal>& animal) {
        if (animal) {
            std::cout << "Animal: " << animal->getName() 
                      << ", Height: " << animal->getHeight() 
                      << ", Price: $" << animal->getPrice() << std::endl;
        }
    });
}

void Zoo::printHabitatDetails() const {
    std::cout << "\nPrinting large habitats using template function:" << std::endl;
    auto largeHabitats = m_habitatInventory.filterItems([](const std::shared_ptr<Habitat>& habitat) {
        return habitat && habitat->getCapacity() > 3;
    });

    for (const auto& habitat : largeHabitats) {
        std::cout << "Habitat Type: " << habitat->getType()
                  << ", Capacity: " << habitat->getCapacity()
                  << ", Cleanliness: " << habitat->getCleanlinessLevel() << std::endl;
    }
}

void Zoo::highlightHabitatAt(sf::RenderWindow& window, int tileSize, int index, const sf::Color& color) const
{
    if (index >= 0 && index < static_cast<int>(m_habitats.size())) {
        m_habitats[index].highlightHabitat(window, tileSize, color, 2.0f);
    }
}