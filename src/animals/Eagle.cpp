#include "../../include/animals/Eagle.hpp"

Eagle::Eagle(const std::string &name, const std::string &species, int age, float weight, float height,
             float wingSpan, float maxFlightAltitude, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_wingSpan(wingSpan), m_maxFlightAltitude(maxFlightAltitude)
{
}

float Eagle::getWingSpan() const
{
    return m_wingSpan;
}

float Eagle::getMaxFlightAltitude() const
{
    return m_maxFlightAltitude;
}

void Eagle::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with a wingspan of " << m_wingSpan
              << "m is soaring high above the mountain peaks." << std::endl;
}

float Eagle::interact(int visitorCount) const
{
    float enjoymentFactor = 1.8f;
    std::cout << "Visitors are in awe as " << getName() << " performs an impressive diving display from "
              << m_maxFlightAltitude << " meters altitude!" << std::endl;

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Eagle::clone() const
{
    return std::make_shared<Eagle>(*this);
}
