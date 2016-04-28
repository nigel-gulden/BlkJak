
#include "Deck.h"





Deck::Deck() : m_currentCard(0)
{
	//allocates new array of cards
    m_deck = new CardC[52];

	//creates each card in the suit
	for (int suit = 0; suit < 4; suit++ )
	{
		//creates each rank in suit
		for (int rank = 0; rank < 13; rank++)
		{
			//allocates new card


			//fills data into card
            m_deck[suit * 13 + rank].SetSuit(suit);
            m_deck[suit * 13 + rank].SetRank(rank);
		}
	}
}


Deck::~Deck()
{


	//deletes array
	delete[] m_deck;

	m_deck = nullptr;
}



void Deck::Shuffle()
{
	//creates new temp
    CardC  temp;

	//resets current card
	m_currentCard = 0;

	//initializes number to 0
	int number(0);

		//shuffles the deck
		for (int cur = 0; cur < 52; cur++)
		{
			//gets random number
			number = this->rand.GetRandom(52);

			//puts current card in temp
			temp = m_deck[cur];

			//swaps current card with rand card
			m_deck[cur] = m_deck[number];

			//puts temp card in rand soit
			m_deck[number] = temp;
		}
}



void Deck::ResetCurrent()
{
	//resets card count
	m_currentCard = 0;
}



CardC Deck::Deal()
{
    CardC temp; //(*m_deck[m_currentCard]);

	//returns current card
	if (m_currentCard < 52)
	{
        temp = m_deck[m_currentCard++];
	}

	else
	{


		ResetCurrent();
		
		Shuffle();
        temp = m_deck[m_currentCard];
	}

	return temp;
}

