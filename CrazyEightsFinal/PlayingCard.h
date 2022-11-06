#ifndef PLAYINGCARDS_H
#define PLAYINGCARDS_H

#include <cstdlib>
#include <cstddef>

using namespace std;

class PlayingCard
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

#endif /* PLAYINGCARDS_H */