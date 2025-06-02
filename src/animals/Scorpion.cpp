#include "../../include/animals/Scorpion.hpp"

Scorpion::Scorpion(const std::string &name, const std::string &species, int age, float weight, float height,
                   float venomPotency, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), m_venomPotency(venomPotency)
{
}

float Scorpion::getVenomPotency() const
{
    return m_venomPotency;
}

void Scorpion::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " is hiding under rocks and hunting insects."
              << std::endl;
}

float Scorpion::interact(int visitorCount) const
{
    float enjoymentFactor = 1.2f;
    std::cout << "Visitors carefully observe " << getName() << " with venom potency of " << m_venomPotency
              << " from behind secure glass!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Scorpion::clone() const
{
    return std::make_shared<Scorpion>(*this);
}
