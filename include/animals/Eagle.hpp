#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Eagle : public Animal
{
private:
    float m_wingSpan;
    float m_maxFlightAltitude;

public:
    Eagle(const std::string &name, const std::string &species, int age, float weight, float height,
          float wingSpan, float maxFlightAltitude, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    float getWingSpan() const;
    float getMaxFlightAltitude() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
