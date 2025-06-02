#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Yak : public Animal
{
private:
    float m_woolThickness;
    float m_coldResistance;

public:
    Yak(const std::string &name, const std::string &species, int age, float weight, float height,
        float woolThickness, float coldResistance, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getWoolThickness() const;
    float getColdResistance() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
