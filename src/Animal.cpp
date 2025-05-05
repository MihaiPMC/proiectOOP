#include "../include/Animal.hpp"
#include <random>

Animal::Animal(const std::string &name, const std::string &species, int age, float weight, float height,
               float is_healthy, int price, float hunger)
    : m_name(name), m_species(species), m_age(age), m_weight(weight), m_height(height),
      m_isHealthy(is_healthy), m_price(price), m_foodLevel(hunger)
{
}

Animal::Animal(const Animal &other)
    : m_name(other.m_name), m_species(other.m_species), m_age(other.m_age), m_weight(other.m_weight),
      m_height(other.m_height), m_isHealthy(other.m_isHealthy), m_price(other.m_price), m_foodLevel(other.m_foodLevel)
{
}

Animal::Animal(Animal &&other) noexcept
    : m_name(std::move(other.m_name)), m_species(std::move(other.m_species)), m_age(other.m_age),
      m_weight(other.m_weight), m_height(other.m_height), m_isHealthy(other.m_isHealthy),
      m_price(other.m_price), m_foodLevel(other.m_foodLevel)
{
}

Animal &Animal::operator=(const Animal &other)
{
    if (this == &other)
        return *this;
    m_name = other.m_name;
    m_species = other.m_species;
    m_age = other.m_age;
    m_weight = other.m_weight;
    m_height = other.m_height;
    m_isHealthy = other.m_isHealthy;
    m_price = other.m_price;
    m_foodLevel = other.m_foodLevel;
    return *this;
}

Animal &Animal::operator=(Animal &&other) noexcept
{
    if (this == &other)
        return *this;
    m_name = std::move(other.m_name);
    m_species = std::move(other.m_species);
    m_age = other.m_age;
    m_weight = other.m_weight;
    m_height = other.m_height;
    m_isHealthy = other.m_isHealthy;
    m_price = other.m_price;
    m_foodLevel = other.m_foodLevel;
    return *this;
}

const std::string &Animal::getName() const
{
    return m_name;
}

void Animal::setName(const std::string &newName)
{
    m_name = newName;
}

const std::string &Animal::getSpecies() const
{
    return m_species;
}

void Animal::setSpecies(const std::string &newSpecies)
{
    m_species = newSpecies;
}

int Animal::getAge() const
{
    return m_age;
}

void Animal::setAge(int newAge)
{
    m_age = newAge;
}

float Animal::getWeight() const
{
    return m_weight;
}

void Animal::setWeight(float newWeight)
{
    m_weight = newWeight;
}

float Animal::getHeight() const
{
    return m_height;
}

void Animal::setHeight(float newHeight)
{
    m_height = newHeight;
}

float Animal::getIsHealthy() const
{
    return m_isHealthy;
}

void Animal::setIsHealthy(float is_healthy)
{
    m_isHealthy = is_healthy;
}

int Animal::getPrice() const
{
    return m_price;
}

void Animal::setPrice(int new_price)
{
    m_price = new_price;
}

float Animal::getHunger() const
{
    return m_foodLevel;
}

void Animal::setHunger(float newHunger)
{
    m_foodLevel = newHunger;
}

void Animal::updateHealth()
{
    if (m_foodLevel < 0.2f)
    {
        m_isHealthy -= 0.1f;
    }
    else
    {
        m_isHealthy += 0.1f;
    }
}

void Animal::updateHunger(float deltaTime)
{
    const float decayRate = 0.05f;
    m_foodLevel -= decayRate * deltaTime;
    if (m_foodLevel < 0.0f)
        m_foodLevel = 0.0f;
}

std::ostream &operator<<(std::ostream &os, const Animal &animal)
{
    os << "Animal: " << animal.m_name << "\n"
            << "  Species: " << animal.m_species << "\n"
            << "  Age: " << animal.m_age << " years\n"
            << "  Weight: " << animal.m_weight << " kg\n"
            << "  Height: " << animal.m_height << " cm\n"
            << "  Health Status: " << (animal.m_isHealthy * 100) << "%" << "\n"
            << "  Hunger Level: " << (animal.m_foodLevel * 100) << "%" << "\n"
            << "  Price: $" << animal.m_price;
    return os;
}

std::vector<std::string> Animal::s_animalNames = {
    "Luna", "Max", "Rocky", "Bella", "Charlie", "Lucy", "Leo", "Daisy", "Simba", "Nala",
        "Jack", "Molly", "Duke", "Sadie", "Teddy", "Ruby", "Oliver", "Rosie", "Milo", "Lola",
        "Buddy", "Coco", "Oscar", "Maggie", "Tank", "Penny", "Zeus", "Stella", "Rex", "Sophie",
        "Toby", "Zoey", "Riley", "Chloe", "Bandit", "Ellie", "Scout", "Piper", "Bruno", "Lily",
        "Abby", "Ace", "Ada", "Adam", "Addie", "Admiral", "Aero", "Aiden", "Ajax", "Alamo",
        "Alaska", "Alba", "Albert", "Alden", "Alec", "Alex", "Alexa", "Alexis", "Alfie", "Alice",
        "Allie", "Ally", "Amber", "Amelia", "Amigo", "Amos", "Amy", "Angel", "Angus", "Annie",
        "Apollo", "April", "Archie", "Ares", "Aria", "Ariel", "Arlo", "Arnie", "Arrow", "Artemis",
        "Asher", "Ashton", "Aspen", "Astro", "Athena", "Atlas", "Atticus", "Aubrey", "Austin", "Autumn",
        "Avalon", "Avery", "Axel", "Axle", "Babette", "Bailey", "Bali", "Balto", "Bambino", "Bambi",
        "Banjo", "Barney", "Baron", "Basil", "Baxter", "Beamer", "Bean", "Bear", "Beau", "Becky",
        "Bellatrix", "Belle", "Benji", "Benny", "Bentley", "Berry", "Bessie", "Betty", "Bianca", "Billy",
        "Bingo", "Bishop", "Biscuit", "Blaze", "Blitz", "Blizzard", "Blosom", "Blue", "Bo", "Bobby",
        "Bodie", "Bogey", "Bonnie", "Boomer", "Boots", "Boris", "Boss", "Boston", "Bowser", "Boxer",
        "Brady", "Bramble", "Brandy", "Bravo", "Breeze", "Breezy", "Brenna", "Brennan", "Brew", "Brian",
        "Bridget", "Briggs", "Brio", "Bronco", "Bronson", "Brooke", "Brooklyn", "Bruce", "Buck", "Buckeye",
        "Bucky", "Bud", "Buddy", "Buffy", "Bullet", "Bumble", "Bunny", "Buttercup", "Buzz", "Byron",
        "Cade", "Caesar", "Cairo", "Cali", "Callie", "Calvin", "Camden", "Camilla", "Candy", "Captain",
        "Cara", "Carla", "Carlo", "Carmen", "Carter", "Casey", "Cash", "Casper", "Cassie", "Cassius",
        "Castle", "Cayenne", "Cedar", "Cello", "Chance", "Chandler", "Chanel", "Chaos", "Chaplin", "Charger",
        "Charm", "Chase", "Chauncy", "Chaz", "Checkers", "Cheech", "Chelsea", "Cherokee", "Cherry", "Cherub",
        "Chester", "Chevy", "Chew", "Chewie", "Chewy", "Cheyenne", "Chip", "Chipper", "Chips", "Chloe",
        "Chocolate", "Chrissy", "Chubby", "Chuck", "Chucky", "Cinder", "Cinnamon", "Cisco", "Claire", "Clancy",
        "Clark", "Claude", "Clay", "Clemson", "Cleo", "Cleopatra", "Cliff", "Clifford", "Clive", "Cloe",
        "Clover", "Clyde", "Coal", "Cobalt", "Coco", "Cocoa", "Coconut", "Cody", "Coffee", "Cognac",
        "Colby", "Cole", "Comet", "Commando", "Connor", "Cookie", "Cooper", "Copper", "Coral", "Corby",
        "Cortez", "Cosmo", "Cotton", "Courage", "Cowboy", "Cozmo", "Crackers", "Cricket", "Crimson", "Crosby",
        "Crow", "Cruise", "Crunch", "Cruz", "Cubby", "Cujo", "Curry", "Curtis", "Cutie", "Cyrus",
        "Daffodil", "Dagger", "Daisy", "Dakota", "Dallas", "Damien", "Dana", "Dane", "Danger", "Dante",
        "Darby", "Darcy", "Darwin", "Dave", "Dawson", "Dax", "Dayzie", "Dazzle", "Dean", "Deejay",
        "Delta", "Denali", "Denver", "Deuce", "Dexter", "Diablo", "Diamond", "Diego", "Diesel", "Digger",
        "Dillon", "Dingo", "Dinky", "Dino", "Dixie", "Dobie", "Doc", "Dodger", "Domingo", "Domino",
        "Donner", "Dora", "Doreen", "Dorrie", "Dotty", "Doug", "Dozer", "Drake", "Dreamer", "Drover",
        "Drum", "Dryden", "Dudley", "Duffy", "Dugan", "Duke", "Dune", "Duster", "Dusty", "Dutch",
        "Dylan", "Eagle", "Easton", "Echo", "Eddie", "Eden", "Edge", "Edison", "Edward", "Egor",
        "Electra", "Eli", "Elijah", "Elliot", "Elmer", "Elsa", "Elvis", "Ember", "Emerson", "Emily",
        "Emma", "Emmy", "Enzo", "Ernie", "Eva", "Evan", "Everest", "Evie", "Excalibur", "Ezra",
        "Faith", "Falco", "Falcon", "Fancy", "Fang", "Felix", "Fergie", "Ferguson", "Ferris", "Fez",
        "Fidget", "Fido", "Fiji", "Finn", "Fiona", "Fitz", "Flake", "Flash", "Fleet", "Fletcher",
        "Flicka", "Fling", "Flip", "Flora", "Flores", "Floyd", "Fluffy", "Flynn", "Fontana", "Forest",
        "Forrest", "Foster", "Fox", "Foxtrot", "Frankenstein", "Frankie", "Freddie", "Freedom", "Friday", "Frodo",
        "Frosty", "Fuji", "Gabe", "Gabriel", "Gadget", "Gaia", "Galadriel", "Galaxy", "Gandalf", "Garfield",
        "Garth", "Gary", "Gavin", "Gemini", "Genie", "George", "Georgia", "Ghost", "Gia", "Gibson",
        "Gideon", "Gigi", "Ginger", "Ginny", "Giovanni", "Giselle", "Glacier", "Gladys", "Glitter", "Gloria",
        "Glover", "Goliath", "Gonzo", "Goober", "Goose", "Gordon", "Grace", "Gracie", "Grady", "Graham",
        "Granite", "Grant", "Grayson", "Greenie", "Griffin", "Grim", "Grizzly", "Gromit", "Grover", "Guinness",
        "Gunner", "Gus", "Gypsy", "Hades", "Hadley", "Haiku", "Halley", "Halsey", "Hamilton", "Hamlet",
        "Hammer", "Hank", "Hanna", "Hannah", "Hansel", "Happy", "Harley", "Harpo", "Harrison", "Harry",
        "Harvey", "Hawkeye", "Hayes", "Hazel", "Heath", "Heidi", "Henry", "Hero", "Hershey", "Hestia",
        "Hickory", "Hobbes", "Holly", "Homer", "Honey", "Hooch", "Hoover", "Hope", "Horatio", "Hornet",
        "Houston", "Hudson", "Huey", "Hugh", "Hugo", "Humphrey", "Hunter", "Hyde", "Ice", "Iggy",
        "Igloo", "Igor", "Ike", "India", "Indie", "Indigo", "Indy", "Infinity", "Iris", "Irving",
        "Isaac", "Isabel", "Isabella", "Isabelle", "Isaiah", "Isis", "Isla", "Ivan", "Ivory", "Ivy",
        "Izzy", "Jackie", "Jackson", "Jade", "Jagger", "Jake", "Jasmine", "Jasper", "Java", "Jax",
        "Jazz", "Jazzy", "Jedi", "Jelly", "Jenna", "Jenny", "Jericho", "Jersey", "Jesse", "Jessie",
        "Jester", "Jet", "Jethro", "Jett", "Jewel", "Jiffy", "Jimmy", "Jinx", "Jitterbug", "JoJo",
        "Joanie", "Joaquin", "Jock", "Jody", "Joey", "Johnny", "Jojo", "Joker", "Jolene", "Jolly",
        "Jones", "Jordan", "Jorge", "Josie", "Journey", "Joy", "Judge", "Judy", "Jules", "Julia",
        "Julian", "Juliet", "June", "Junior", "Jupiter", "Justice", "Justin", "Kacey", "Kaia", "Kaiser",
        "Kallie", "Kangaroo", "Kansas", "Karma", "Kasey", "Katie", "Katrina", "Katy", "Kawasaki", "Kay",
        "Kayla", "Kaylee", "Kaz", "Kazoo", "Keats", "Keesha", "Kellan", "Kelsey", "Kelvin", "Ken",
        "Kendall", "Kennedy", "Kenny", "Kenya", "Kerry", "Kettle", "Kevin", "Kick", "Kid", "Kiki",
        "Killian", "King", "Kingston", "Kipling", "Kira", "Kirby", "Kit", "Kiwi", "Klaus", "Kleo",
        "Knight", "Knuckles", "Kobe", "Kodiak", "Koko", "Kona", "Kong", "Kosmo", "Kota", "Kramer",
        "Kris", "Krystal", "Kurt", "Kylie", "Kyra", "Lacey", "Laddie", "Lady", "Laika", "Lakota",
        "Lana", "Lance", "Land", "Lane", "Langley", "Lara", "Lark", "Larry", "Laser", "Lassie",
        "Latte", "Lauren", "Layla", "Lazarus", "Lazy", "Lefty", "Legacy", "Leia", "Lemon", "Lenny",
        "Leon", "Leonard", "Leonardo", "Leroy", "Levi", "Lewis", "Lexi", "Libby", "Liberty", "Licorice",
        "Lightning", "Lila", "Lilac", "Lincoln", "Linda", "Linus", "Lionel", "Lisa", "Little", "Logan",
        "London", "Lotus", "Louie", "Louis", "Lovey", "Lucas", "Lucky", "Luke", "Lulu", "Lumiere",
        "Luna", "Lynx", "Lyric", "Mac", "Macaroni", "Mack", "Mackenzie", "Maddie", "Madison", "Madonna",
        "Magic", "Magnum", "Magnus", "Maisie", "Maize", "Major", "Malcolm", "Mali", "Malibu", "Mallory",
        "Mama", "Mandy", "Mango", "Marble", "Marco", "Marcus", "Mariah", "Maris", "Marley", "Marlin",
        "Marmaduke", "Mars", "Marshal", "Martha", "Martin", "Marty", "Marvel", "Mary", "Mason", "Mateo",
        "Matilda", "Matrix", "Mattie", "Maui", "Maverick", "Mavis", "Maximus", "Maxwell", "May", "Maya",
        "Mazda", "McCoy", "Meadow", "Meatball", "Megan", "Memphis", "Mercedes", "Mercury", "Merlin", "Merry",
        "Mesquite", "Mia", "Miami", "Mica", "Michael", "Mickey", "Midnight", "Mikey", "Milan", "Miles",
        "Miller", "Milton", "Mimi", "Minnie", "Mint", "Minty", "Missy", "Misty", "Mitch", "Mittens",
        "Mocha", "Mojave", "Molly", "Monaco", "Mona", "Mongoose", "Monroe", "Montana", "Monterey", "Montgomery",
        "Monty", "Mookie", "Moon", "Moose", "Morgan", "Morris", "Moses", "Mozart", "Muffin", "Murphy",
        "Murray", "Mustang", "Mylo", "Mystic", "Mystique", "Nadia", "Nancy", "Nanette", "Nanny", "Naomi",
        "Napoleon", "Nash", "Natalie", "Nathan", "Navajo", "Navy", "Nemo", "Nena", "Neptune", "Nero",
        "Ness", "Nestle", "Nevada", "Newt", "Newton", "Nibbles", "Nickel", "Nicky", "Nico", "Nike",
        "Nikita", "Nikki", "Niko", "Nina", "Ninja", "Nixon", "Noah", "Nobel", "Noel", "Noelle",
        "Nola", "Noodle", "Noodles", "Norman", "North", "Norton", "Norway", "Nova", "Nugget", "Nutmeg",
        "Oasis", "Obi", "Ocean", "Odessa", "Odette", "Odin", "Ohio", "Okra", "Olaf", "Olive",
        "Oliver", "Olivia", "Ollie", "Olympia", "Omar", "Omega", "Onyx", "Opal", "Opie", "Oreo",
        "Orlando", "Orleans", "Oscar", "Otis", "Otto", "Owen", "Ozark", "Ozzie", "Pablo", "Paco",
        "Paddington", "Paddy", "Page", "Paige", "Paisley", "Paloma", "Pancake", "Pandora", "Panic", "Panther",
        "Papa", "Paris", "Parker", "Pascal", "Patch", "Patches", "Patriot", "Pattie", "Patton", "Paulie",
        "Paws", "Paxton", "Paxil", "Payday", "Peaches", "Peanut", "Pearl", "Pebbles", "Pedro", "Peggy",
        "Pele", "Penelope", "Penny", "Pepe", "Pepper", "Percy", "Periwinkle", "Perkins", "Perry", "Petunia",
        "Phantom", "Pharaoh", "Phoenix", "Phyllis", "Picasso", "Pickles", "Pierce", "Pierre", "Piglet", "Pilot"
};

std::string Animal::getRandomName()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, s_animalNames.size() - 1);
    return s_animalNames[dist(gen)];
}

Animal Animal::createRandomAnimal(const std::string &species, int minAge, int maxAge)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distAge(minAge, maxAge);
    std::uniform_real_distribution<float> distWeight(10.0f, 200.0f);
    std::uniform_real_distribution<float> distHeight(20.0f, 150.0f);
    std::uniform_real_distribution<float> distHealth(0.7f, 1.0f);
    return Animal(
        getRandomName(),
        species,
        distAge(gen),
        distWeight(gen),
        distHeight(gen),
        distHealth(gen)
    );
}
