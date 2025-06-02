#include "../../include/animals/Yak.hpp"

Yak::Yak(const std::string &name, const std::string &species, int age, float weight, float height,
         float woolThickness, float coldResistance, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_woolThickness(woolThickness), m_coldResistance(coldResistance)
{
}

float Yak::getWoolThickness() const
{
    return m_woolThickness;
}

float Yak::getColdResistance() const
{
    return m_coldResistance;
}

void Yak::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_woolThickness
              << "cm thick wool is grazing on high altitude vegetation." << std::endl;
}

float Yak::interact(int visitorCount) const
{
    float enjoymentFactor = 1.3f;
    std::cout << "Visitors are impressed by " << getName() << "'s impressive size and "
              << m_woolThickness << "cm thick wool that allows it to survive in temperatures as low as "
              << -m_coldResistance << "°C!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Yak::clone() const
{
    return std::make_shared<Yak>(*this);
}
