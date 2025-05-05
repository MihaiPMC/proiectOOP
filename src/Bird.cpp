#include "../include/Bird.hpp"

Bird::Bird(const std::string &name, const std::string &species, int age, float weight, float height, float wingSpan, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), m_wingSpan(wingSpan)
{
}

float Bird::getWingSpan() const {
    return m_wingSpan;
}

void Bird::setWingSpan(float wingSpan) {
    m_wingSpan = wingSpan;
}

void Bird::performBehavior() const {
    std::cout << getName() << " the " << getSpecies() << " is flying." << std::endl;
}

std::shared_ptr<Animal> Bird::clone() const {
    return std::make_shared<Bird>(*this);
}

