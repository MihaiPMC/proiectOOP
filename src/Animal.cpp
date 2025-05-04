#include "../include/Animal.hpp"
#include <random>

Animal::Animal(const std::string &name, const std::string &species, int age, float weight, float height,
               float is_healthy, int price, float hunger)
    : m_name(name), m_species(species), m_age(age), m_weight(weight), m_height(height),
      m_isHealthy(is_healthy), m_price(price), m_foodLevel(hunger)
{
}

Animal::Animal(const Animal &other)
    : m_name(other.m_name), m_species(other.m_species), m_age(other.m_age), m_weight(other.m_weight),
      m_height(other.m_height), m_isHealthy(other.m_isHealthy), m_price(other.m_price), m_foodLevel(other.m_foodLevel)
{
}

Animal::Animal(Animal &&other) noexcept
    : m_name(std::move(other.m_name)), m_species(std::move(other.m_species)), m_age(other.m_age),
      m_weight(other.m_weight), m_height(other.m_height), m_isHealthy(other.m_isHealthy),
      m_price(other.m_price), m_foodLevel(other.m_foodLevel)
{
}

Animal &Animal::operator=(const Animal &other)
{
    if (this == &other)
        return *this;
    m_name = other.m_name;
    m_species = other.m_species;
    m_age = other.m_age;
    m_weight = other.m_weight;
    m_height = other.m_height;
    m_isHealthy = other.m_isHealthy;
    m_price = other.m_price;
    m_foodLevel = other.m_foodLevel;
    return *this;
}

Animal &Animal::operator=(Animal &&other) noexcept
{
    if (this == &other)
        return *this;
    m_name = std::move(other.m_name);
    m_species = std::move(other.m_species);
    m_age = other.m_age;
    m_weight = other.m_weight;
    m_height = other.m_height;
    m_isHealthy = other.m_isHealthy;
    m_price = other.m_price;
    m_foodLevel = other.m_foodLevel;
    return *this;
}

const std::string &Animal::getName() const
{
    return m_name;
}

void Animal::setName(const std::string &newName)
{
    m_name = newName;
}

const std::string &Animal::getSpecies() const
{
    return m_species;
}

void Animal::setSpecies(const std::string &newSpecies)
{
    m_species = newSpecies;
}

int Animal::getAge() const
{
    return m_age;
}

void Animal::setAge(int newAge)
{
    m_age = newAge;
}

float Animal::getWeight() const
{
    return m_weight;
}

void Animal::setWeight(float newWeight)
{
    m_weight = newWeight;
}

float Animal::getHeight() const
{
    return m_height;
}

void Animal::setHeight(float newHeight)
{
    m_height = newHeight;
}

float Animal::getIsHealthy() const
{
    return m_isHealthy;
}

void Animal::setIsHealthy(float is_healthy)
{
    m_isHealthy = is_healthy;
}

int Animal::getPrice() const
{
    return m_price;
}

void Animal::setPrice(int new_price)
{
    m_price = new_price;
}

float Animal::getHunger() const
{
    return m_foodLevel;
}

void Animal::setHunger(float newHunger)
{
    m_foodLevel = newHunger;
}

void Animal::updateHealth()
{
    if (m_foodLevel < 0.2f)
    {
        m_isHealthy -= 0.1f;
    }
    else
    {
        m_isHealthy += 0.1f;
    }
}

void Animal::updateHunger(float deltaTime)
{
    const float decayRate = 0.05f;
    m_foodLevel -= decayRate * deltaTime;
    if (m_foodLevel < 0.0f)
        m_foodLevel = 0.0f;
}

std::ostream &operator<<(std::ostream &os, const Animal &animal)
{
    os << "Animal: " << animal.m_name << "\n"
            << "  Species: " << animal.m_species << "\n"
            << "  Age: " << animal.m_age << " years\n"
            << "  Weight: " << animal.m_weight << " kg\n"
            << "  Height: " << animal.m_height << " cm\n"
            << "  Health Status: " << (animal.m_isHealthy * 100) << "%" << "\n"
            << "  Hunger Level: " << (animal.m_foodLevel * 100) << "%" << "\n"
            << "  Price: $" << animal.m_price;
    return os;
}

std::vector<std::string> Animal::s_animalNames = {
    "Luna", "Max", "Rocky", "Bella", "Charlie", "Lucy", "Leo", "Daisy", "Simba", "Nala",
    // ...existing names...
};

std::string Animal::getRandomName()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, s_animalNames.size() - 1);
    return s_animalNames[dist(gen)];
}

Animal Animal::createRandomAnimal(const std::string &species, int minAge, int maxAge)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distAge(minAge, maxAge);
    std::uniform_real_distribution<float> distWeight(10.0f, 200.0f);
    std::uniform_real_distribution<float> distHeight(20.0f, 150.0f);
    std::uniform_real_distribution<float> distHealth(0.7f, 1.0f);
    return Animal(
        getRandomName(),
        species,
        distAge(gen),
        distWeight(gen),
        distHeight(gen),
        distHealth(gen)
    );
}
