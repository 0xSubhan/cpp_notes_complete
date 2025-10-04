#include <string>
#include <string_view>
#include <array>
#include <utility> // Required for std::pair
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
    int val() const
    {
        static constexpr std::array<int,maxRank> rankVal {11,2,3,4,5,6,7,8,9,10,10,10,10};
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
    // Handling the case where ace is 1 which was previously 11: || Ace Counter -->
    int aceCount {0};

};
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score < Settings::dealerLimit)
    {
        Card card { deck.dealCard() };
        dealer.score += card.val();
        // Dealer : Handling Ace Logic for 1 point conversion from 11:
        if (card.val() == 11)
        {
            dealer.aceCount++;
        }
        while (dealer.score > Settings::dealerLimit && dealer.aceCount > 0)
        {
            dealer.score -= 10;
            dealer.aceCount--;
        }
        //
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
        // Player : Handling Ace Logic for 1 point conversion from 11:
        if (card.val() == 11)
        {
            player.aceCount++;
        }
        while (player.score > Settings::bustLimit && player.aceCount > 0)
        {
            player.score -= 10;
            player.aceCount--;
        }
        //
        std::cout << "You were dealt " << card << ".\t" << "You now have: " << player.score << '\n';
    }
    if (player.score > Settings::bustLimit)
    {
        std::cout  << "Player Went Bust.\n";
        return true;
    }
    return false;
    
    
} 
enum Result
{
    Tie,
    Win, // Player Won
    Lose, // Dealer Won
};
Result playBlackJack()
{
    Deck deck{};
    deck.shuffle();
    // Dealer Turns:
    Player dealer {};
    // you will need to show the dealer’s initial card
    Card initialCard_Dealer { deck.dealCard() };
    dealer.score = { initialCard_Dealer.val() };
    std::cout << "The Dealer is showing " << initialCard_Dealer << " (" << dealer.score << ")" <<"\n"; 
    //
    // Player Turns:
    Player player {};
    // you will need to show the player's initial card both in this case:

    std::pair<Card,Card> initialCard_Player {deck.dealCard(),deck.dealCard()};
    player.score = { initialCard_Player.first.val() + initialCard_Player.second.val() };
    std::cout << "You are showing : " << initialCard_Player.first << " " << initialCard_Player.second << " (" << player.score << ")" << "\n"; 

    //
    // Player Logic here:
    if (playerturn(deck,player))
    {
        return Result::Lose; // If player went bust, then return false which will mean that player lost and dealer won!
    }
    // Dealer Logic here:   
    if (dealerTurn(deck,dealer))
        return Result::Win; // for player , because if dealer went bust then player won!
    // Tie Logic Here:
    if (player.score == dealer.score)
    {
        return Result::Tie;
    }
    //    
    // Deciding If we won or not:
    return ( player.score > dealer.score ? Result::Win : Result::Lose );
}


int main() {
    // Black Jack Game: 
    Result resultOfGame {playBlackJack()};
    if( resultOfGame == Result::Win )
    {
        std::cout << "You win\n";  
    }
    else if( resultOfGame == Result::Lose ) 
    {
        std::cout << "You Lose!\n";
    }
    else
    {
        std::cout << "Tie!\n";
    }


    return 0;
}