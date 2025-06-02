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

    // Private constructor for singleton pattern
    AnimalFactory();

    // Register all animal creation functions
    void registerAnimalCreators();

public:
    // Singleton pattern
    static AnimalFactory& getInstance();

    // Delete copy and move constructors/assignments
    AnimalFactory(const AnimalFactory&) = delete;
    AnimalFactory& operator=(const AnimalFactory&) = delete;
    AnimalFactory(AnimalFactory&&) = delete;
    AnimalFactory& operator=(AnimalFactory&&) = delete;

    // Create an animal based on species
    std::shared_ptr<Animal> createAnimal(const std::string& species,
                                        const std::string& name,
                                        int age,
                                        float weight,
                                        float height,
                                        float health = 1.0f,
                                        int price = 1000,
                                        float hunger = 0.0f);

    // Check if a species is supported
    bool supportsSpecies(const std::string& species) const;

    // Get all supported species
    std::vector<std::string> getSupportedSpecies() const;
};
