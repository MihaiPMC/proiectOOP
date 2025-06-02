#include "../../include/animals/Seaturtle.hpp"

Seaturtle::Seaturtle(const std::string &name, const std::string &species, int age, float weight, float height,
                   float shellHardness, int migratingDistance, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_shellHardness(shellHardness), m_migratingDistance(migratingDistance)
{
}

float Seaturtle::getShellHardness() const
{
    return m_shellHardness;
}

int Seaturtle::getMigratingDistance() const
{
    return m_migratingDistance;
}

void Seaturtle::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with shell hardness rated at " << m_shellHardness
              << " is gracefully swimming through the ocean habitat." << std::endl;
}

float Seaturtle::interact(int visitorCount) const
{
    float enjoymentFactor = 1.5f;
    std::cout << "Visitors are fascinated by " << getName() << "'s elegant swimming and learning about "
              << "its incredible migrations of up to " << m_migratingDistance << " kilometers!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Seaturtle::clone() const
{
    return std::make_shared<Seaturtle>(*this);
}
