#pragma once
#include "../Animal.hpp"
#include "Coyote.hpp"
#include <memory>
#include <string>
#include <map>
#include <functional>

class AnimalFactory {
private:
    using CreatorFunction = std::function<std::shared_ptr<Animal>(const std::string&, const std::string&, int, float, float, float, int, float)>;
    std::map<std::string, CreatorFunction> m_creators;

    AnimalFactory();

    void registerAnimalCreators();

public:
    static AnimalFactory& getInstance();

    AnimalFactory(const AnimalFactory&) = delete;
    AnimalFactory& operator=(const AnimalFactory&) = delete;
    AnimalFactory(AnimalFactory&&) = delete;
    AnimalFactory& operator=(AnimalFactory&&) = delete;

    std::shared_ptr<Animal> createAnimal(const std::string& species,
                                        const std::string& name,
                                        int age,
                                        float weight,
                                        float height,
                                        float health = 1.0f,
                                        int price = 1000,
                                        float hunger = 0.0f);

    bool supportsSpecies(const std::string& species) const;

    std::vector<std::string> getSupportedSpecies() const;
};
