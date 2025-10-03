#include <string>
#include <string_view>
#include <array>
#include <cassert>
#include <algorithm> // for std::shuffle
#include "Random.h"  // for Random::mt
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
class Deck
{
private:
    std::array<Card,52> m_cards {};
     std::size_t m_nextCardIndex {0};
public:
    Deck()
    {
        std::size_t count {0};
        for(auto suit : Card::allSuits)
        {
            for(auto rank : Card::allRank)
            {
                m_cards[count++] = Card{rank,suit} ;
            }
        }
    }
    Card dealCard()
    {
        assert( m_nextCardIndex != 52 && "Deck Has Gone Through All Cards!" );
        return m_cards[m_nextCardIndex++];
    }
    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = {0};
    }

};
// Implementing Black-Jack:
namespace Settings
{
    const int bustLimit {21};
    const int dealerLimit {17};
}
struct Player
{
    int score {0};
};
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score < Settings::dealerLimit)
    {
        Card card { deck.dealCard() };
        dealer.score += card.val();
        std::cout << "The Dealer Flips a " << card << ".\t" << "They now have: " << dealer.score << '\n';  
    }
    if (dealer.score > Settings::dealerLimit)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }
    return false;
}
bool playerWantHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";
        char choice {}; std::cin >> choice;

        switch (choice)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
    
}
bool playerturn(Deck& deck, Player& player)
{

    while ( player.score < Settings::bustLimit && playerWantHit() )
    {
        Card card { deck.dealCard() };
        player.score += card.val();
        std::cout << "You were dealt " << card << ".\t" << "You now have: " << player.score << '\n';
    }
    if (player.score > Settings::bustLimit)
    {
        std::cout  << "Player Went Bust.\n";
        return true;
    }
    return false;
    
    
} 
bool playBlackJack()
{
    Deck deck{};
    deck.shuffle();
    // Dealer Turns:
    Player dealer {};
    dealer.score = { deck.dealCard().val() };
    std::cout << "The Dealer is showing: " << dealer.score << "\n"; 
    // Player Turns:
    Player player {};
    player.score = { deck.dealCard().val() + deck.dealCard().val() };
    std::cout << "The Player is showing: " << player.score << "\n"; 
    // Player Logic here:
    if (playerturn(deck,player))
    {
        return false; // If player went bust, then return false which will mean that player lost and dealer won!
    }
    
    // Dealer Logic here:   
    if (dealerTurn(deck,dealer))
        return true; // for player , because if dealer went bust then player won!
    
    // Deciding If we won or not:
    return ( player.score > dealer.score );
}


int main() {
    // Black Jack Game: 
    if( playBlackJack())
    {
        std::cout << "You win\n";  
    }
    else
    {
        std::cout << "You Lose!\n";
    }


    return 0;
}