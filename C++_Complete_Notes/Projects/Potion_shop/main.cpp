#include <string>
#include <string_view>
#include <array>
#include <vector>
#include "Random.h"
#include <iostream>

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        maxType,
    };
    std::array<Type,maxType> typePotion {healing,mana,speed,invisibility};
    std::array costPotion {20,30,12,50};
    std::array<std::string_view, maxType> namePotion {"healing", "mana", "speed", "invisibility"};

    static_assert(maxType == costPotion.size() && maxType == namePotion.size());


}
// Class to store Player data:
class Player
{
    private:
    std::string m_name{};
    std::array<int,Potion::Type::maxType> m_inventory {};
    int m_gold {};
public:
    Player(std::string_view name)
        : m_name{name}
        , m_gold{Random::get(80,120)}
    {
    }
    // const std::string& getName() const { return m_name; }
    const auto getGold() const { return m_gold; };
    int inventory(Potion::Type type) const { return m_inventory[type]; }; 

    // Functionality to Buy Potions Declaration:
    bool buy(Potion::Type type);
};
// Defination:
bool Player::buy(Potion::Type type)
{
    if (m_gold < Potion::costPotion[type])
    {
        return false;
    }
    m_gold -= Potion::costPotion[type];
    ++m_inventory[type];
    return true;
}
// To convert an ASCII number character to an int (e.g. '5' to 5), you can use the following:
int charNumToInt(char c)
{
    return c - '0';
}
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
Potion::Type whichPotion()
{
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char input {};
    while (true)
    {
        std::cin >> input;
        if (!std::cin)
        {
            /* code */
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            continue;
        }
        // If there is extraneous input, treat as failure case
        if (!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            ignoreLine(); // ignore any extraneous input
            continue;
        }
        if (input == 'q')
        {
            /* code */
            return Potion::maxType;
        }
        int val {charNumToInt(input)};
        if (val >= 0 && val < Potion::maxType)
        {
            /* code */
            return static_cast<Potion::Type>(val);
        }
        // It wasn't a valid potion selection
        std::cout << "I didn't understand what you said.  Try again: ";
        ignoreLine();
    }
    
}
// Selection Menu:
void shop(Player& player)
{
    while(true)
    {
        std::cout << "\nHere is our selection for today:" << '\n';
        for(auto element : Potion::typePotion)
            std::cout << element << ") " << Potion::namePotion[element] << " costs " << Potion::costPotion[element] << "." << "\n";

        

        Potion::Type which { whichPotion() }; 
        // checking success state of potion:
        if (which == Potion::maxType)
        {
            /* code */
            return;
        }
        bool success { player.buy(which) };
        if (!success)
        {
            /* code */
            std::cout << "You can not afford that.\n" ;
            continue;
        }
        else
            std::cout << "\nYou purchased a potion of " << Potion::namePotion[which] << ". You have " << player.getGold() << " gold left." << '\n';   
    }
}
// Print Inventory:
void printInventory(Player& player)
{
    std::cout << "\n\n" << "Your inventory contains: " << "\n";

    for(auto element : Potion::typePotion)
    {
        if (player.inventory(element) > 0)
        {
            /* code */
            std::cout << player.inventory(element) << "x potion of " << Potion::namePotion[element] << '\n'; 
        }
    }
    std::cout << "You escaped with " << player.getGold() << " gold remaining.\n";
}


int main() {
    

    std::cout << '\n' << "Welcome to Roscoe's potion emporium!" << '\n';
    std::cout << "Enter Your name: ";

    std::string playerName{};
    std::getline(std::cin >> std::ws, playerName);

    Player player1 {playerName};

    std::cout << "Hello, " <<  playerName << ", You have " << player1.getGold() << " gold." << '\n';
    
    shop(player1);

    printInventory(player1);

    std::cout << '\n';

    std::cout << "Thanks for shopping at Roscoe's potion emporium!" << '\n';



    std::cout << "\n\n\n\n";
    return 0;
}