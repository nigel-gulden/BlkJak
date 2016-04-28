/************************************************************************
* Class: Card
*
* Constructors:
*	Card(Rank rank = ACE, Suit suit = SPADE)
*		constructs a new card with passed in Rank and Suit, otherwise
*		initialized to ACE of SPADES
*
* Mutators:
*	void SetRank(Rank rank);
*		Initializes m_rank to rank
*	void SetSuit(Suit suit);
*		Initializes m_suit to suit
*	Rank GetRank();
*		Returns the value in m_rank
*	Suit GetSuit();
*		Returns the value in m_suit
*************************************************************************/

#ifndef CARD_H
#define CARD_H
#include <QObject>


//enumerated data types for rank and suit


class CardC : public QObject
{

    Q_OBJECT
    Q_PROPERTY(int m_rank READ GetRank WRITE SetRank)
    Q_PROPERTY(int m_suit READ GetSuit WRITE SetSuit)

public:

    CardC(int rank = 0, int suit = 0) : m_rank(rank), m_suit(suit){}

    CardC(const CardC & card);
        void operator= (const CardC & rhs);

public slots:
    void Copy(CardC card);
    void SetRank(int rank);
    void SetSuit(int suit);
    int GetRank();
    int GetSuit();



private:
    int m_rank;
    int m_suit;
};
Q_DECLARE_METATYPE(CardC)
#endif

//done
