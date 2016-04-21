/************************************************************************
* Class: Blackjack
*
* Constructors:
*	Blackjack(int bankroll)
*		instantiates game and gives playerBankroll bankroll, shuffles
*		the deck twice, and displays message
*
* Mutators:		none
*
* Methods
*	void PlayTheGame()
*		Acts as the directory for the program, has the basic rules algorithm
*	void DisplayHands()
*		Displays both the dealer and player's hand, as well as the pot.
*	bool Continue()
*		Default input function, asks user yes or no.
*	void Win21()
*		Specific win instance for blackjack.
*	void Win()
*		Win instance for every other case.
*	void Tie()
*		Instance that player ties with house
*	bool DealerHand()
*		Logic for dealer's hand, determines when to hit or stay.
*	bool PlayerHand(bool & twentyOne)
*		Acts as the player's turn. Asks for doubledown, or moves on
*	bool HitPlayer()
*		lets the player hit cards until bust or 21 or asks to stay
*	bool DoubleDown()
*		Logic for the case of a doubledown
*	bool Wager()
*		Asks for wager, displays bankroll, doesn't allow player to bet
*		too much
*
* Members:		
*	Player mPlayer
*		Is the player
*	Dealer mDealer
*		Is the dealer
*	Deck mDeck
*		Is the deck
*	Bankroll playerBank
*		holds how much money the player has
*	Bankroll mPot
*		holds how much money the player wagered
*************************************************************************/
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <conio.h>

#include <Windows.h>
#include <MMSystem.h>

#pragma comment(lib,"winmm.lib")

#include "Deck.h"
#include "Dealer.h"
#include "Player.h"
#include "Bankroll.h"

class Blackjack
{
public:
	Blackjack(int bankroll);
	void PlayTheGame();
	void DisplayHands();
	bool Continue();
	void Win21();
	void Win();
	void Tie();
	bool DealerHand();
	bool PlayerHand(bool & twentyOne);
	bool HitPlayer();
	bool DoubleDown();
	bool Wager();

private:
	Player mPlayer;
	Dealer mDealer;
	Deck mDeck;
	Bankroll playerBank;
	Bankroll mPot;
};

#endif