#include "../include/Reptile.hpp"

Reptile::Reptile(const std::string &name, const std::string &species, int age, float weight, float height, 
                 std::string scalePattern, bool isColdBlooded, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger), 
      m_isColdBlooded(isColdBlooded), m_scalePattern(std::move(scalePattern))
{
}

bool Reptile::getIsColdBlooded() const {
    return m_isColdBlooded;
}

void Reptile::setIsColdBlooded(bool isColdBlooded) {
    m_isColdBlooded = isColdBlooded;
}

const std::string& Reptile::getScalePattern() const {
    return m_scalePattern;
}

void Reptile::setScalePattern(const std::string& pattern) {
    m_scalePattern = pattern;
}

void Reptile::performBehavior() const {
    std::cout << getName() << " the " << getSpecies() << " is basking in the sun." << std::endl;
}

float Reptile::interact(int visitorCount) const {
    float enjoymentFactor = 1.3f;
    std::cout << "Visitors are mesmerized by " << getName() << "'s " << m_scalePattern 
              << " scales as it slowly moves around!" << std::endl;

    if (m_isColdBlooded) {
        std::cout << "Being cold-blooded, " << getName() << " is more active in warm areas of the habitat." << std::endl;
    }

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Reptile::clone() const {
    return std::make_shared<Reptile>(*this);
}
