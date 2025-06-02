#include "../../include/animals/Fox.hpp"

Fox::Fox(const std::string &name, const std::string &species, int age, float weight, float height,
         const std::string &furPattern, float stealthLevel, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), 
      m_furPattern(furPattern), m_stealthLevel(stealthLevel)
{
}

const std::string &Fox::getFurPattern() const
{
    return m_furPattern;
}

float Fox::getStealthLevel() const
{
    return m_stealthLevel;
}

void Fox::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_furPattern << " pattern is stealthily hunting mice."
              << std::endl;
}

float Fox::interact(int visitorCount) const
{
    float enjoymentFactor = 1.4f;
    std::cout << "Visitors are charmed by " << getName() << " with its beautiful " << m_furPattern
              << " fur as it playfully runs around its enclosure!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Fox::clone() const
{
    return std::make_shared<Fox>(*this);
}
