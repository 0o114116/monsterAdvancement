#include <iostream>
#include <map>
#include "Yaml.hpp"

const std::map<std::string, int> INTELLIGENCE{
    {"non", 0}, {"ani", 1}, {"sem", 3}, {"low", 6}, {"ave", 9}, {"ver", 11},
    {"hig", 14}, {"exc", 16}, {"gen", 18}, {"sup", 20}, {"god", 22}
};

int convertHitPoints(const int hitDice)
{
    return floor(hitDice * 4.5);
}

int convertArmorClass(const int armorClass)
{
    const auto res = 19 - armorClass;
    
    if (res > 22)
        return 22;
    return res;
}

int convertSpeed(const int speed)
{
    return speed * 5;
}

int convertInt(const std::string& intScore)
{
    return INTELLIGENCE.at(intScore);
}

int main()
{
    Yaml::Node root;
    Yaml::Parse(root, "./monster.txt");

    int stats[9]{};

    const auto hitDice = root["hitDice"].As<int>();

    if (hitDice == -1)
        stats[0] = root["maxHitPoints"].As<int>();
    else
    {
        stats[0] = convertHitPoints(hitDice);
        stats[6] = 2 + hitDice / 2;
        stats[7] = 8 + hitDice / 2;
    }

    stats[1] = convertArmorClass(root["armorClass"].As<int>());
    stats[2] = convertSpeed(root["speed"][0].As<int>());
    stats[3] = convertSpeed(root["speed"][1].As<int>());
    stats[4] = convertSpeed(root["speed"][2].As<int>());
    stats[5] = convertSpeed(root["speed"][3].As<int>());
    stats[8] = convertInt(root["intelligence"].As<std::string>());

    std::cout << "HP: " << stats[0] << "\nAC: " << stats[1] << "\nSpeed: " << stats[2] << "ft. ";

    if (stats[3] > 0)
        std::cout << stats[3] << "ft. (swimming) ";
    if (stats[4] > 0)
        std::cout << stats[4] << "ft. (burrowing) ";
    if (stats[5] > 0)
        std::cout << stats[5] << "ft. (flying) ";

    std::cout << "\nAttack Roll Modifier: " << stats[6] << "\nSaving Throw DC: " << stats[7] << "\nINT: " << stats[8] << std::endl;
}

