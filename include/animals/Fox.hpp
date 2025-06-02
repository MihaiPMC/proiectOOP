#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Fox : public Animal
{
private:
    std::string m_furPattern;
    float m_stealthLevel;

public:
    Fox(const std::string &name, const std::string &species, int age, float weight, float height,
        const std::string &furPattern, float stealthLevel, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    const std::string &getFurPattern() const;
    float getStealthLevel() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
