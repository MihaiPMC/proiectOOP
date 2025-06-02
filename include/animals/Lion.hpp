#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Lion : public Animal
{
private:
    float m_maneSize;
    float m_roarVolume;

public:
    Lion(const std::string &name, const std::string &species, int age, float weight, float height,
         float maneSize, float roarVolume, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getManeSize() const;
    float getRoarVolume() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
