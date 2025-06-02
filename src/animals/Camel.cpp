#include "../../include/animals/Camel.hpp"

Camel::Camel(const std::string &name, const std::string &species, int age, float weight, float height,
               int humpsCount, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), m_humpsCount(humpsCount)
{
}

int Camel::getHumpsCount() const
{
    return m_humpsCount;
}

void Camel::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " is trekking through the desert with its " 
              << m_humpsCount << " humps." << std::endl;
}

float Camel::interact(int visitorCount) const
{
    float enjoymentFactor = 1.3f;
    std::cout << "Visitors are amazed as " << getName() << " with " << m_humpsCount
              << " humps allows them to take rides across the desert habitat!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Camel::clone() const
{
    return std::make_shared<Camel>(*this);
}
