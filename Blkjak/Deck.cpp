
#include "Deck.h"

/**************************************************************
*	Purpose:  Constructs the Deck object
*
*	Entry:  none
*
*	 Exit:  allocates new deck of 52 cards, then for each 
*		suit, and each rank in the suit, allocates new Card
*		and initializes it
****************************************************************/



Deck::Deck() : m_currentCard(0)
{
	//allocates new array of cards
	m_deck = new Card *[52];

	//creates each card in the suit
	for (int suit = 0; suit < 4; suit++ )
	{
		//creates each rank in suit
		for (int rank = 0; rank < 13; rank++)
		{
			//allocates new card
			m_deck[suit * 13 + rank] = new Card;

			//fills data into card
			m_deck[suit * 13 + rank]->SetSuit(static_cast<Suit>(suit + 1));
			m_deck[suit * 13 + rank]->SetRank(static_cast<Rank>(rank + 1));
		}
	}
}

/**************************************************************
*	Purpose:  Deconstructs the Deck object
*
*	Entry:  none
*
*	 Exit:  deallocates  for each suit, and each rank in the 
*		suit, then deallocates the Deck and sets it to null
****************************************************************/

Deck::~Deck()
{
	//iterates through each suit
	for (int suit = 0; suit < 4; suit++)
	{
		//iterates through each rank
		for (int rank = 0; rank < 13; rank++)
		{
			//deletes each card
			delete m_deck[suit * 13 + rank];
		}
	}
	//deletes array
	delete[] m_deck;

	m_deck = nullptr;
}

/**************************************************************
*	Purpose:  shuffles the Deck object
*
*	Entry:  none
*
*	 Exit:  iterates through each Card and swaps it with a 
*		randomly generated card number. Uses temp to temporarily
*		store card to swap with
****************************************************************/

void Deck::Shuffle()
{
	//creates new temp
	Card * temp = nullptr;

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

/**************************************************************
*	Purpose:  Resets m_currentCard
*
*	Entry:  none
*
*	 Exit:  Sets m_currentCard to 0
****************************************************************/

void Deck::ResetCurrent()
{
	//resets card count
	m_currentCard = 0;
}

/**************************************************************
*	Purpose:  Returns card at m_currentCard
*
*	Entry:  none
*
*	 Exit:  returns the card pointed to by m_deck[m_currentCard]
****************************************************************/

Card Deck::Deal()
{
	Card temp; //(*m_deck[m_currentCard]);

	//returns current card
	if (m_currentCard < 52)
	{
		temp = *m_deck[m_currentCard++];
	}

	else
	{
		cout << "Out of cards, shuffling deck\n\n";

		ResetCurrent();
		
		Shuffle();
		temp = *m_deck[m_currentCard];
	}

	return temp;
}

