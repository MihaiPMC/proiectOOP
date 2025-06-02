#include "../../include/animals/Bear.hpp"

Bear::Bear(const std::string &name, const std::string &species, int age, float weight, float height,
           const std::string &furColor, float hibernationMonths, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), 
      m_furColor(furColor), m_hibernationMonths(hibernationMonths)
{
}

const std::string &Bear::getFurColor() const
{
    return m_furColor;
}

float Bear::getHibernationMonths() const
{
    return m_hibernationMonths;
}

void Bear::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_furColor << " fur is foraging for berries."
              << std::endl;
}

float Bear::interact(int visitorCount) const
{
    float enjoymentFactor = 1.7f;
    std::cout << "Visitors watch in awe as " << getName() << " the bear with " << m_furColor
              << " fur demonstrates its fishing skills!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Bear::clone() const
{
    return std::make_shared<Bear>(*this);
}
