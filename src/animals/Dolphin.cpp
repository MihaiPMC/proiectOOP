#include "../../include/animals/Dolphin.hpp"

Dolphin::Dolphin(const std::string &name, const std::string &species, int age, float weight, float height,
               float intelligenceLevel, float maxSwimSpeed, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_intelligenceLevel(intelligenceLevel), m_maxSwimSpeed(maxSwimSpeed)
{
}

float Dolphin::getIntelligenceLevel() const
{
    return m_intelligenceLevel;
}

float Dolphin::getMaxSwimSpeed() const
{
    return m_maxSwimSpeed;
}

void Dolphin::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with intelligence level " << m_intelligenceLevel
              << " is performing acrobatic jumps and swimming at speeds up to " << m_maxSwimSpeed << " km/h." << std::endl;
}

float Dolphin::interact(int visitorCount) const
{
    float enjoymentFactor = 2.0f;
    std::cout << "Visitors are thrilled as " << getName() << " performs incredible tricks and interacts with "
              << "trainers, showcasing its remarkable intelligence of " << m_intelligenceLevel << "!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Dolphin::clone() const
{
    return std::make_shared<Dolphin>(*this);
}
