#include "../../include/animals/AnimalFactory.hpp"
#include "../../include/animals/Camel.hpp"
#include "../../include/animals/Scorpion.hpp"
#include "../../include/animals/Bear.hpp"
#include "../../include/animals/Fox.hpp"
#include "../../include/animals/Wolf.hpp"
#include "../../include/animals/Eagle.hpp"
#include "../../include/animals/Goat.hpp"
#include "../../include/animals/Yak.hpp"
#include "../../include/animals/Dolphin.hpp"
#include "../../include/animals/Octopus.hpp"
#include "../../include/animals/Seaturtle.hpp"
#include "../../include/animals/Elephant.hpp"
#include "../../include/animals/Lion.hpp"
#include "../../include/animals/Zebra.hpp"
#include <random>

AnimalFactory::AnimalFactory() {
    registerAnimalCreators();
}

AnimalFactory &AnimalFactory::getInstance() {
    static AnimalFactory instance;
    return instance;
}

void AnimalFactory::registerAnimalCreators() {
    // Desert animals
    m_creators["Camel"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                             float health, int price, float hunger) {
        // For camel, we're using the additional float param as hump count (as int)
        return std::make_shared<Camel>(name, species, age, weight, height, static_cast<int>(health * 2) + 1, health,
                                       price, hunger);
    };

    m_creators["Coyote"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                              float health, int price, float hunger) {
        std::vector<std::string> coatColors = {"tan", "gray", "reddish-brown"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distColor(0, coatColors.size() - 1);
        std::uniform_real_distribution<float> distHunting(0.4f, 0.9f);

        return std::make_shared<Coyote>(name, species, age, weight, height,
                                        distHunting(gen), coatColors[distColor(gen)], health, price, hunger);
    };

    m_creators["Scorpion"] = [](const std::string &name, const std::string &species, int age, float weight,
                                float height, float health, int price, float hunger) {
        // For scorpion, we're using the additional float param as venom potency
        return std::make_shared<Scorpion>(name, species, age, weight, height, health * 0.9f, health, price, hunger);
    };

    // Forest animals
    m_creators["Bear"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                            float health, int price, float hunger) {
        std::vector<std::string> furColors = {"brown", "black", "grizzly"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distColor(0, furColors.size() - 1);
        std::uniform_real_distribution<float> distHibernation(3.0f, 5.0f);

        return std::make_shared<Bear>(name, species, age, weight, height,
                                      furColors[distColor(gen)], distHibernation(gen), health, price, hunger);
    };

    m_creators["Fox"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                           float health, int price, float hunger) {
        std::vector<std::string> patterns = {"red", "silver", "cross"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distPattern(0, patterns.size() - 1);
        std::uniform_real_distribution<float> distStealth(0.5f, 0.9f);

        return std::make_shared<Fox>(name, species, age, weight, height,
                                     patterns[distPattern(gen)], distStealth(gen), health, price, hunger);
    };

    m_creators["Wolf"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                            float health, int price, float hunger) {
        std::vector<std::string> roles = {"alpha", "beta", "omega"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distRole(0, roles.size() - 1);
        std::uniform_int_distribution<> distPackSize(5, 12);

        return std::make_shared<Wolf>(name, species, age, weight, height,
                                      roles[distRole(gen)], distPackSize(gen), health, price, hunger);
    };

    // Mountain animals
    m_creators["Eagle"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                             float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distWingspan(1.5f, 2.5f);
        std::uniform_real_distribution<float> distAltitude(1000.0f, 3000.0f);

        return std::make_shared<Eagle>(name, species, age, weight, height,
                                       distWingspan(gen), distAltitude(gen), health, price, hunger);
    };

    m_creators["Goat"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                            float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distHorn(10.0f, 30.0f);
        std::uniform_int_distribution<> distClimber(0, 1);

        return std::make_shared<Goat>(name, species, age, weight, height,
                                      distHorn(gen), distClimber(gen) == 1, health, price, hunger);
    };

    m_creators["Yak"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                           float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distWool(5.0f, 15.0f);
        std::uniform_real_distribution<float> distCold(30.0f, 50.0f);

        return std::make_shared<Yak>(name, species, age, weight, height,
                                     distWool(gen), distCold(gen), health, price, hunger);
    };

    // Ocean animals
    m_creators["Dolphin"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                               float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distIntelligence(8.0f, 10.0f);
        std::uniform_real_distribution<float> distSpeed(30.0f, 50.0f);

        return std::make_shared<Dolphin>(name, species, age, weight, height,
                                         distIntelligence(gen), distSpeed(gen), health, price, hunger);
    };

    m_creators["Octopus"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                               float health, int price, float hunger) {
        std::vector<std::string> abilities = {"expert", "advanced", "basic"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distAbility(0, abilities.size() - 1);

        return std::make_shared<Octopus>(name, species, age, weight, height,
                                         8, abilities[distAbility(gen)], health, price, hunger);
    };

    m_creators["Seaturtle"] = [](const std::string &name, const std::string &species, int age, float weight,
                                 float height, float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distShell(7.0f, 10.0f);
        std::uniform_int_distribution<> distMigration(1000, 5000);

        return std::make_shared<Seaturtle>(name, species, age, weight, height,
                                           distShell(gen), distMigration(gen), health, price, hunger);
    };

    // Savanna animals
    m_creators["Elephant"] = [](const std::string &name, const std::string &species, int age, float weight,
                                float height, float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distTrunk(1.5f, 2.5f);
        std::uniform_real_distribution<float> distTusk(0.5f, 1.5f);

        return std::make_shared<Elephant>(name, species, age, weight, height,
                                          distTrunk(gen), distTusk(gen), health, price, hunger);
    };

    m_creators["Lion"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                            float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distMane(15.0f, 30.0f);
        std::uniform_real_distribution<float> distRoar(80.0f, 114.0f);

        return std::make_shared<Lion>(name, species, age, weight, height,
                                      distMane(gen), distRoar(gen), health, price, hunger);
    };

    m_creators["Zebra"] = [](const std::string &name, const std::string &species, int age, float weight, float height,
                             float health, int price, float hunger) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distStripes(40, 80);
        std::uniform_real_distribution<float> distSpeed(40.0f, 65.0f);

        return std::make_shared<Zebra>(name, species, age, weight, height,
                                       distStripes(gen), distSpeed(gen), health, price, hunger);
    };
}

std::shared_ptr<Animal> AnimalFactory::createAnimal(const std::string &species,
                                                    const std::string &name,
                                                    int age,
                                                    float weight,
                                                    float height,
                                                    float health,
                                                    int price,
                                                    float hunger) {
    auto it = m_creators.find(species);
    if (it != m_creators.end()) {
        return it->second(name, species, age, weight, height, health, price, hunger);
    }

    // Default fallback
    return nullptr;
}

bool AnimalFactory::supportsSpecies(const std::string &species) const {
    return m_creators.find(species) != m_creators.end();
}

std::vector<std::string> AnimalFactory::getSupportedSpecies() const {
    std::vector<std::string> species;
    for (const auto &creator: m_creators) {
        species.push_back(creator.first);
    }
    return species;
}
