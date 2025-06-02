#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Dolphin : public Animal
{
private:
    float m_intelligenceLevel;
    float m_maxSwimSpeed;

public:
    Dolphin(const std::string &name, const std::string &species, int age, float weight, float height,
            float intelligenceLevel, float maxSwimSpeed, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getIntelligenceLevel() const;
    float getMaxSwimSpeed() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
