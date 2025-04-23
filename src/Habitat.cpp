#include "../include/Habitat.hpp"

Habitat::Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity, float cleanlinessLevel,
                 float price)
    : type(type),
      animals(animals),
      capacity(capacity),
      cleanlinessLevel(cleanlinessLevel),
      price(price)
{
}

Habitat::Habitat(const Habitat &other)
    : type(other.type),
      animals(other.animals),
      capacity(other.capacity),
      cleanlinessLevel(other.cleanlinessLevel),
      price(other.price)
{
}

Habitat::Habitat(Habitat &&other) noexcept
    : type(std::move(other.type)),
      animals(std::move(other.animals)),
      capacity(other.capacity),
      cleanlinessLevel(other.cleanlinessLevel),
      price(other.price)
{
}

Habitat &Habitat::operator=(const Habitat &other)
{
    if (this == &other)
        return *this;
    type = other.type;
    animals = other.animals;
    capacity = other.capacity;
    cleanlinessLevel = other.cleanlinessLevel;
    price = other.price;
    return *this;
}

Habitat &Habitat::operator=(Habitat &&other) noexcept
{
    if (this == &other)
        return *this;
    type = std::move(other.type);
    animals = std::move(other.animals);
    capacity = other.capacity;
    cleanlinessLevel = other.cleanlinessLevel;
    price = other.price;
    return *this;
}

const std::string &Habitat::getType() const
{
    return type;
}

void Habitat::setType(const std::string &newType)
{
    this->type = newType;
}

const std::vector<Animal> &Habitat::getAnimals() const
{
    return animals;
}

void Habitat::addAnimals(const std::vector<Animal> &newAnimals)
{
    for (const auto &animal: newAnimals)
    {
        this->animals.push_back(animal);
    }
}

void Habitat::addAnimals(const Animal &animal)
{
    this->animals.push_back(animal);
}

int Habitat::getCapacity() const
{
    return capacity;
}

void Habitat::setCapacity(int newCapacity)
{
    this->capacity = newCapacity;
}

float Habitat::getCleanlinessLevel() const
{
    return cleanlinessLevel;
}

void Habitat::setCleanlinessLevel(float level)
{
    cleanlinessLevel = level;
}

float Habitat::getPrice() const
{
    return price;
}

void Habitat::setPrice(float new_price)
{
    price = new_price;
}

void Habitat::cleanHabitat()
{
    cleanlinessLevel = 1.0f;
}

void Habitat::updateCleanliness(float deltaTime)
{
    int totalAnimals = animals.size();
    if (totalAnimals > 0)
    {
        const float decayRate = 0.01f;
        cleanlinessLevel -= decayRate * totalAnimals * deltaTime;
        if (cleanlinessLevel < 0.0f)
        {
            cleanlinessLevel = 0.0f;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
{
    os << "Habitat: " << habitat.type << "\n"
       << "  Capacity: " << habitat.capacity << "\n"
       << "  Cleanliness: " << (habitat.cleanlinessLevel * 100) << "%" << "\n"
       << "  Price: $" << habitat.price << "\n"
       << "  Animals: " << habitat.animals.size();
    return os;
}

std::map<std::string, std::vector<std::string>> Habitat::habitatSpecies = {
    {"Forest", {"Bear", "Wolf", "Fox", "Deer", "Owl"}},
    {"Desert", {"Camel", "Scorpion", "Rattlesnake", "Coyote", "Lizard"}},
    {"Ocean", {"Dolphin", "Shark", "Octopus", "Penguin", "Sea Turtle"}},
    {"Savanna", {"Lion", "Elephant", "Zebra", "Giraffe", "Cheetah"}},
    {"Mountain", {"Eagle", "Mountain Lion", "Goat", "Yak", "Snow Leopard"}}
};

std::map<std::string, std::vector<std::string>> Habitat::getHabitatSpecies() {
    return habitatSpecies;
}

std::string Habitat::selectHabitatType() {
    int habitatType;
    do {
        std::cout << "What habitat do you want to add? 1. Forest 2. Desert 3. Ocean 4. Savanna 5. Mountain" << std::endl;
        std::cin >> habitatType;

        if (habitatType < 1 || habitatType > 5) {
            std::cout << "Invalid habitat type! Please choose again." << std::endl;
        }
    } while (habitatType < 1 || habitatType > 5);

    switch (habitatType) {
        case 1: return "Forest";
        case 2: return "Desert";
        case 3: return "Ocean";
        case 4: return "Savanna";
        case 5: return "Mountain";
        default: return "Forest";
    }
}

void Habitat::addRandomAnimals(int animalCount, float& budget) {
    if (animalCount < 0 || animalCount > 5) {
        std::cout << "Invalid number of animals! Using 0 instead." << std::endl;
        return;
    }

    std::cout << "Animal price is $1000." << std::endl;

    for (int j = 0; j < animalCount; j++) {
        if (budget < 1000) {
            std::cout << "Not enough budget to add more animals!" << std::endl;
            break;
        }

        std::cout << "Available species for " << type << " habitat:" << std::endl;
        const std::vector<std::string>& species = habitatSpecies[type];

        for (size_t k = 0; k < species.size(); k++) {
            std::cout << (k + 1) << ". " << species[k] << std::endl;
        }

        int speciesChoice;
        std::cout << "Choose a species (1-" << species.size() << "): ";
        std::cin >> speciesChoice;

        if (speciesChoice < 1 || speciesChoice > static_cast<int>(species.size())) {
            std::cout << "Invalid choice. Defaulting to first species." << std::endl;
            speciesChoice = 1;
        }

        Animal newAnimal = Animal::createRandomAnimal(species[speciesChoice - 1]);

        this->addAnimals(newAnimal);
        budget -= newAnimal.getPrice();

        std::cout << "Added " << newAnimal.getName() << " the " << newAnimal.getSpecies()
                  << " to " << type << " habitat!" << std::endl;
        std::cout << "Remaining budget: $" << budget << std::endl;
    }
}
