#include "../../include/animals/Elephant.hpp"

Elephant::Elephant(const std::string &name, const std::string &species, int age, float weight, float height,
                 float trunkLength, float tuskLength, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_trunkLength(trunkLength), m_tuskLength(tuskLength)
{
}

float Elephant::getTrunkLength() const
{
    return m_trunkLength;
}

float Elephant::getTuskLength() const
{
    return m_tuskLength;
}

void Elephant::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with a " << m_trunkLength
              << "m trunk is bathing in mud and spraying water." << std::endl;
}

float Elephant::interact(int visitorCount) const
{
    float enjoymentFactor = 1.9f;
    std::cout << "Visitors are amazed as " << getName() << " demonstrates its incredible strength and dexterity "
              << "using its " << m_trunkLength << "m trunk to pick up objects and spray water!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Elephant::clone() const
{
    return std::make_shared<Elephant>(*this);
}
