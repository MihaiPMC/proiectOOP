#pragma once
#include "Animal.hpp"
#include <string>
#include <memory>
#include <iostream>

class Reptile : public Animal {
private:
    bool m_isColdBlooded;
    std::string m_scalePattern;
public:
    Reptile(const std::string &name, const std::string &species, int age, float weight, float height, 
           std::string scalePattern, bool isColdBlooded = true, float isHealthy = 1.0f, int price = 1200, float hunger = 0.0f);
    [[nodiscard]] bool getIsColdBlooded() const;
    void setIsColdBlooded(bool isColdBlooded);
    [[nodiscard]] const std::string& getScalePattern() const;
    void setScalePattern(const std::string& pattern);
    virtual void performBehavior() const override;
    virtual float interact(int visitorCount) const override;
    virtual std::shared_ptr<Animal> clone() const override;
};
