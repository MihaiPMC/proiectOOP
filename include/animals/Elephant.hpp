#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Elephant : public Animal
{
private:
    float m_trunkLength;
    float m_tuskLength;

public:
    Elephant(const std::string &name, const std::string &species, int age, float weight, float height,
             float trunkLength, float tuskLength, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getTrunkLength() const;
    float getTuskLength() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
