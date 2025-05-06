#pragma once
#include "Animal.hpp"
#include <memory>
#include <iostream>

class Bird : public Animal {
private:
    float m_wingSpan;
public:
    Bird(const std::string &name, const std::string &species, int age, float weight, float height, float wingSpan, float isHealthy = 1.0f, int price = 1000, float hunger = 0.0f);
    float getWingSpan() const;
    void setWingSpan(float wingSpan);
    virtual void performBehavior() const override;
    virtual float interact(int visitorCount) const override;
    virtual std::shared_ptr<Animal> clone() const override;
};
