#include "../../include/animals/Lion.hpp"

Lion::Lion(const std::string &name, const std::string &species, int age, float weight, float height,
           float maneSize, float roarVolume, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_maneSize(maneSize), m_roarVolume(roarVolume)
{
}

float Lion::getManeSize() const
{
    return m_maneSize;
}

float Lion::getRoarVolume() const
{
    return m_roarVolume;
}

void Lion::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with a mane of size " << m_maneSize
              << " is roaring at " << m_roarVolume << " decibels, asserting dominance over the savanna." << std::endl;
}

float Lion::interact(int visitorCount) const
{
    float enjoymentFactor = 2.0f;
    std::cout << "Visitors are thrilled as " << getName() << ", with its impressive " << m_maneSize
              << "cm mane, lets out a powerful roar measuring " << m_roarVolume << " decibels!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Lion::clone() const
{
    return std::make_shared<Lion>(*this);
}
