#include "../../include/animals/Zebra.hpp"

Zebra::Zebra(const std::string &name, const std::string &species, int age, float weight, float height,
             int stripeCount, float runningSpeed, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_stripeCount(stripeCount), m_runningSpeed(runningSpeed)
{
}

int Zebra::getStripeCount() const
{
    return m_stripeCount;
}

float Zebra::getRunningSpeed() const
{
    return m_runningSpeed;
}

void Zebra::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_stripeCount
              << " stripes is galloping across the savanna at speeds up to " << m_runningSpeed << " km/h." << std::endl;
}

float Zebra::interact(int visitorCount) const
{
    float enjoymentFactor = 1.4f;
    std::cout << "Visitors are delighted as " << getName() << " with its unique pattern of " << m_stripeCount
              << " stripes demonstrates its running ability at speeds of up to " << m_runningSpeed << " km/h!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Zebra::clone() const
{
    return std::make_shared<Zebra>(*this);
}
