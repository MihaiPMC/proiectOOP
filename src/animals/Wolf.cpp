#include "../../include/animals/Wolf.hpp"

Wolf::Wolf(const std::string &name, const std::string &species, int age, float weight, float height,
           const std::string &packRole, int packSize, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), 
      m_packRole(packRole), m_packSize(packSize)
{
}

const std::string &Wolf::getPackRole() const
{
    return m_packRole;
}

int Wolf::getPackSize() const
{
    return m_packSize;
}

void Wolf::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << ", the " << m_packRole << " of a pack of " << m_packSize
              << " wolves, is howling to communicate with the pack." << std::endl;
}

float Wolf::interact(int visitorCount) const
{
    float enjoymentFactor = 1.6f;
    std::cout << "Visitors are fascinated as " << getName() << ", the " << m_packRole
              << " wolf, leads its pack in a coordinated hunting display!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Wolf::clone() const
{
    return std::make_shared<Wolf>(*this);
}
