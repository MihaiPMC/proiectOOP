#include "../include/Fish.hpp"

Fish::Fish(const std::string &name, const std::string &species, int age, float weight, float height, const std::string &finType, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), m_finType(finType)
{
}

const std::string &Fish::getFinType() const {
    return m_finType;
}

void Fish::setFinType(const std::string &finType) {
    m_finType = finType;
}

void Fish::performBehavior() const {
    std::cout << getName() << " the " << getSpecies() << " is swimming." << std::endl;
}

float Fish::interact(int visitorCount) const {
    float enjoymentFactor = 0.7f;
    std::cout << "Visitors watch " << getName() << " swim gracefully with its " << m_finType << " fins." << std::endl;
    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Fish::clone() const {
    return std::make_shared<Fish>(*this);
}
