#include "../include/Mammal.hpp"

Mammal::Mammal(const std::string &name, const std::string &species, int age, float weight, float height, const std::string &furColor, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), m_furColor(furColor)
{
}

const std::string &Mammal::getFurColor() const {
    return m_furColor;
}

void Mammal::setFurColor(const std::string &color) {
    m_furColor = color;
}

void Mammal::performBehavior() const {
    std::cout << getName() << " the " << getSpecies() << " is roaming on land." << std::endl;
}

std::shared_ptr<Animal> Mammal::clone() const {
    return std::make_shared<Mammal>(*this);
}
