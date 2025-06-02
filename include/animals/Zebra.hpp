#pragma once
#include "../Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Zebra : public Animal
{
private:
    int m_stripeCount;
    float m_runningSpeed;

public:
    Zebra(const std::string &name, const std::string &species, int age, float weight, float height,
          int stripeCount, float runningSpeed, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);

    int getStripeCount() const;
    float getRunningSpeed() const;

    virtual void performBehavior() const override;

    virtual float interact(int visitorCount) const override;

    virtual std::shared_ptr<Animal> clone() const override;
};
