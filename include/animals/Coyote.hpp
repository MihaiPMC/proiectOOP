#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Coyote : public Animal
{
private:
    float m_huntingSkill;
    std::string m_coatColor;

public:
    Coyote(const std::string &name, const std::string &species, int age, float weight, float height,
          float huntingSkill, const std::string &coatColor, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getHuntingSkill() const;
    const std::string &getCoatColor() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
