#include "../../include/animals/Coyote.hpp"

Coyote::Coyote(const std::string &name, const std::string &species, int age, float weight, float height,
               float huntingSkill, const std::string &coatColor, float isHealthy, int price, float hunger)
    : Animal(name, species, age, weight, height, isHealthy, price, hunger),
      m_huntingSkill(huntingSkill), m_coatColor(coatColor)
{
}

float Coyote::getHuntingSkill() const
{
    return m_huntingSkill;
}

const std::string &Coyote::getCoatColor() const
{
    return m_coatColor;
}

void Coyote::performBehavior() const
{
    std::cout << getName() << " the " << getSpecies() << " with " << m_coatColor
              << " coat is howling and showcasing its impressive hunting skills (" 
              << (m_huntingSkill * 100) << "% effectiveness)." << std::endl;
}

float Coyote::interact(int visitorCount) const
{
    float enjoymentFactor = 1.4f;

    if (m_huntingSkill > 0.7f) {
        std::cout << "Visitors are fascinated as " << getName() << " with its " << m_coatColor
                  << " coat demonstrates its exceptional hunting techniques!" << std::endl;
        enjoymentFactor += 0.3f;
    } else {
        std::cout << "Visitors observe " << getName() << " with its " << m_coatColor
                  << " coat as it patrols its territory in the desert habitat!" << std::endl;
    }

    return enjoymentFactor * visitorCount * getIsHealthy();
}

std::shared_ptr<Animal> Coyote::clone() const
{
    return std::make_shared<Coyote>(*this);
}
