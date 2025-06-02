#include "../../include/animals/Goat.hpp"

Goat::Goat(const std::string &name, const std::string &species, int age, float weight, float height,
           float hornLength, bool isClimber, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_hornLength(hornLength), m_isClimber(isClimber)
{
}

float Goat::getHornLength() const
{
    return m_hornLength;
}

bool Goat::getIsClimber() const
{
    return m_isClimber;
}

void Goat::performBehavior() const
{
    if (m_isClimber) {
        std::cout << getName() << " the " << getSpecies() << " with " << m_hornLength
                  << "cm horns is expertly climbing steep mountain slopes." << std::endl;
    } else {
        std::cout << getName() << " the " << getSpecies() << " with " << m_hornLength
                  << "cm horns is grazing on mountain vegetation." << std::endl;
    }
}

float Goat::interact(int visitorCount) const
{
    float enjoymentFactor = 1.2f;
    if (m_isClimber) {
        std::cout << "Visitors marvel as " << getName() << " demonstrates incredible climbing abilities "
                  << "on seemingly impossible terrain!" << std::endl;
        enjoymentFactor += 0.3f;
    } else {
        std::cout << "Visitors enjoy feeding " << getName() << " and petting its soft fur!" << std::endl;
    }

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Goat::clone() const
{
    return std::make_shared<Goat>(*this);
}
