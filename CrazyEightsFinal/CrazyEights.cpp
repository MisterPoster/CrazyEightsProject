#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct PlayingCard
{
    private:
        int    value;
        string face;
        string suit;
    public:
        PlayingCard ();
        PlayingCard (int, string);
        string getSuit  () const { return suit; }; 
        string getFace  () const { return face; };
        int getValue () const { return value; };
        void operator= (PlayingCard);
        bool operator< (PlayingCard);
        void print ();
};

PlayingCard::PlayingCard (int value, string suit)
{
    this->value = ( value > 0 ? value : 0 );
    this->suit  = suit;
    
    switch (value)
    {
        case 1:
            face = "Ace";
            break;
        case 11:
            face = "Jack";
            break;
        case 12:
            face = "Queen";
            break;
        case 13:
            face = "King";
            break;
        default:
            break;
    }
}

void PlayingCard::operator= (const PlayingCard lhs)
{    
    
    this->value = lhs.value;
    this->suit  = lhs.suit;
    this->face  = lhs.face;
}

bool PlayingCard::operator< (const PlayingCard lhs)
{
    return (this->value < lhs.value);
}

void PlayingCard::print ()
{
    face == "" ? cout << "Card : " << value << " of " << suit << "s" << endl : cout << "Card : " << face << " of " << suit << "s" << endl;
}

int main(int argc, char** argv) 
{
    srand (time (0));
    
    string suits_to_have[] = {"Diamond", 
                              "Spade", 
                              "Heart", 
                              "Club"};
    
    string rules [] = {"1. You must play a card that either matches the suit or value or the current card.",
                       "2. Except for 8s, which can played anytime!",
                       "3. To win, you must remove ALL of your cards before your opponent while having FEWER points overall!",
                       "4. If you cannot play, you must take a card out of the remaining deck and pass along the turn"};
    
    PlayingCard* card;
  
    list <PlayingCard*> the_deck;
    queue <string> the_suits;
    set <string> the_rules;
    
    for (string s : suits_to_have)
    {
        the_suits.push (s);
    }
    
    for (string s : rules)
    {
        the_rules.insert (s);
    }
    
    while (!(the_suits.empty ()))
    {
        for (int i = 1; i <= 13; i++)
        {
            card = new PlayingCard (i, the_suits.front ());
            the_deck.push_back (card);
        }
        
        the_suits.pop ();
    }
    
    
    vector <PlayingCard*> v_deck (52);
    copy (the_deck.begin (), the_deck.end (), v_deck.begin ()); 
    
    random_shuffle (v_deck.begin (), v_deck.end ());
    copy (v_deck.begin (), v_deck.end (), the_deck.begin ());
    
    card = nullptr;
    
    cout << " ------ Welcome to Crazy Eights! ------" << endl;
    
    for (set<string>::iterator r = the_rules.begin (); r != the_rules.end (); r++)
    {
        cout << *r << endl;
    }
    
    list <PlayingCard*> player_hand;
    list <PlayingCard*> computer_hand;
    stack <PlayingCard*> played_cards;
    
    list <PlayingCard*>::iterator player = player_hand.begin ();
    list <PlayingCard*>::iterator computer = computer_hand.begin ();
    
    map <int, pair <int, int>> points_per_turn;
    
    int player_points = 0, 
        computer_points = 0, 
        i, 
        choice = 0,
        turns = 1;
    
    for (i = 0; i < 5; i++)
    {
        player_hand.push_back (the_deck.front ());
        the_deck.pop_front ();
    }
    
    for (i = 0; i < 5; i++)
    {
        computer_hand.push_back (the_deck.front ());
        the_deck.pop_front ();
    }
    
    do
    {
        cout << "Your Cards : " << endl;
        
        player_hand.sort ();
        
        i = 0;
        for (player = player_hand.begin (); player != player_hand.end (); player++)
        {
            card = *player;
            cout << i << ") ";
            card->print();
            i++;
        }

        played_cards.push (the_deck.front ());
        the_deck.pop_front ();
    
    
        cout << endl << "Current Card : " << endl;
        played_cards.top ()->print();

        cout << endl << "Choose which card to play (by selecting the appropriate number to your card: " << endl;
        cout << "If you are unable to play, please input 99" << endl;
        cin >> choice;

        PlayingCard* playerChoice;
        player = player_hand.begin ();

        if (choice != 99)
        {
            advance (player, choice);

            playerChoice = *player;
            
            if (playerChoice->getValue() == 8)
            {
                played_cards.push (playerChoice);
                player_points += 50;
                player_hand.remove (playerChoice);
            }
            else if ((playerChoice->getSuit() == played_cards.top ()->getSuit ()))
            {
                played_cards.push (playerChoice);
                player_points += playerChoice->getValue ();
                player_hand.remove (playerChoice);
            }
            else if ((playerChoice->getValue () == played_cards.top ()->getValue ()))
            {
                played_cards.push (playerChoice);
                player_points += playerChoice->getValue ();
                player_hand.remove (playerChoice);
            }
        }
        else
        {
            player_hand.push_back (the_deck.front ());
            the_deck.pop_front ();
        
            cout << "You have drawed a : " << endl;
            player_hand.back ()->print ();
        }

        cout << endl << " --- Computer Turn --- " << endl;

        cout << endl << "Current Card : " << endl;
        played_cards.top ()->print();

        int num_of_8 = 0, 
            num_of_suits = 0, 
            num_of_nums = 0,
            location = 0;

        for (computer = computer_hand.begin (); computer != computer_hand.end (); computer++)
        {
            card = *computer;

            if (card->getValue() == 8)
            {
                num_of_8++;
            }
            else if (card->getSuit () == played_cards.top ()->getSuit())
            {
                num_of_suits++;
            }
            else if (card->getValue() == played_cards.top ()->getValue())
            {
                num_of_nums++;
            }
        }

        PlayingCard* computerChoice;

        string curr_suit = played_cards.top ()->getSuit();
        int    curr_val  = played_cards.top ()->getValue();

        if (num_of_8 > 0)
        {
            computer = find_if (computer_hand.begin(), computer_hand.end (), [](PlayingCard* c) { return c->getValue () == 8; });
            computerChoice = *computer;
            cout << "Computer deals a ";
            computerChoice->print ();
            
            played_cards.push (computerChoice);
            player_hand.erase (computer);
            computer_points += 50;
        }
        else if (num_of_suits > 0)
        {
            computer = find_if (computer_hand.begin(), computer_hand.end (), [&curr_suit](PlayingCard* c) { return c->getSuit () == curr_suit; });
            computerChoice = *computer;
            cout << "Computer deals a ";
            computerChoice->print ();
            
            played_cards.push (computerChoice);
            computer_hand.erase (computer);
            computer_points += computerChoice->getValue ();
        }
        else if (num_of_nums > 0)
        {
            computer = find_if (computer_hand.begin(), computer_hand.end (), [&curr_val](PlayingCard* c) { return c->getValue () == curr_val; });
            computerChoice = *computer;
            cout << "Computer deals a ";
            computerChoice->print ();
            
            played_cards.push (computerChoice);
            computer_hand.erase (computer);
            computer_points += computerChoice->getValue ();
        }
        else
        {
            computer_hand.push_back (the_deck.front ());
            the_deck.pop_front ();
            
            cout << "Computer cannot play this round" << endl;
        }
        
        cout << endl << "Your points : "     << player_points;
        cout << endl << "Computer points : " << computer_points << endl;
        points_per_turn.insert (pair<int, pair<int, int>> (turns, make_pair (player_points, computer_points)));
        turns++;
        
        cout << endl << "Remaining cards : " << the_deck.size () << endl;
    } while (!(player_hand.empty ()) && !(computer_hand.empty ()) && (the_deck.size () > 3));
    
    if (player_points < computer_points)
    {
        cout << endl << "Player Victory!" << endl;
    }
    else if (computer_points > player_points)
    {
        cout << endl << "Computer Victory!" << endl;
    }
    else if (computer_points == player_points)
    {
        cout << endl << "Lucky both of You! A Tie!" << endl;
    }
    
    turns = 1;
    for (map <int, pair<int, int>>::iterator t = points_per_turn.begin (); t != points_per_turn.end (); t++)
    {
        cout << "Turn " << turns << ": " << endl;
        cout << "  Player points: " << points_per_turn.at(turns).first << endl;
        cout << "  Computer points: " << points_per_turn[turns].second << endl;
        turns++;
    }
    
    return 0;
}