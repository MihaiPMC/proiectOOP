#include "../../include/animals/Octopus.hpp"

Octopus::Octopus(const std::string &name, const std::string &species, int age, float weight, float height,
               int tentacleCount, const std::string &camouflageAbility, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_tentacleCount(tentacleCount), m_camouflageAbility(camouflageAbility)
{
}

int Octopus::getTentacleCount() const
{
    return m_tentacleCount;
}

const std::string &Octopus::getCamouflageAbility() const
{
    return m_camouflageAbility;
}

void Octopus::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_tentacleCount
              << " tentacles is demonstrating its " << m_camouflageAbility << " camouflage abilities." << std::endl;
}

float Octopus::interact(int visitorCount) const
{
    float enjoymentFactor = 1.9f;
    std::cout << "Visitors are mesmerized as " << getName() << " uses its " << m_tentacleCount << " tentacles "
              << "to solve puzzles and demonstrates its " << m_camouflageAbility << " camouflage abilities!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Octopus::clone() const
{
    return std::make_shared<Octopus>(*this);
}
