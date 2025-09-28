#include <string>
#include <string_view>
#include <array>
#include <iostream>

using namespace std;

struct Card
{
        
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        maxRank
    };
    enum Suits
    {
        suits_clubs,
        suits_diamonds,
        suits_hearts,
        suits_spades,

        maxSuits
    };

    constexpr static std::array<Rank,maxRank> allRank { 
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king
    };
    constexpr static std::array<Suits,maxSuits> allSuits {
        suits_clubs,
        suits_diamonds,
        suits_hearts,
        suits_spades
    };

    Rank rankCard {};
    Suits suitCard {};



    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static std::array<char,maxRank> rank { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
        static std::array<char,maxSuits> suit {'C','D','H','S'};

        out << rank[card.rankCard] << suit[card.suitCard];
        return out;
    }
    int val()
    {
        std::array rankVal {11,2,3,4,5,6,7,8,9,10,10,10,10};
        return rankVal[rankCard];
    }
};

int main() {

    Card c1 {Card::rank_5, Card::suits_hearts};
    std::cout << c1;
    
    std::cout << '\n';

    for(auto suit : Card::allSuits)
    {
        for(auto rank : Card::allRank)
        {
            std::cout << Card {rank,suit} << " ";
        }
    }




    return 0;
}