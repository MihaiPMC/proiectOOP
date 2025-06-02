#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Octopus : public Animal
{
private:
    int m_tentacleCount;
    std::string m_camouflageAbility;

public:
    Octopus(const std::string &name, const std::string &species, int age, float weight, float height,
            int tentacleCount, const std::string &camouflageAbility, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    int getTentacleCount() const;
    const std::string &getCamouflageAbility() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
