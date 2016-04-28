
#include "Blackjack.h"


Blackjack::Blackjack() : QObject()
{
	mDeck.Shuffle();
	mDeck.Shuffle();
}

CardC* Blackjack::getPlayerCardAt(int index)
{
    return mPlayer.getCardAt(index);
}

CardC* Blackjack::getDealerCardAt(int index)
{
    return mDealer.getCardAt(index);
}

int Blackjack::getPlayerCardCount()
{
    return mPlayer.GetmCount();
}

int Blackjack::getDealerCardCount()
{
    return mDealer.GetmCount();
}

void Blackjack::setBankroll(int bankroll)
{
    playerBank = bankroll;
}

int Blackjack::getBankroll()
{
    return playerBank;
}

void Blackjack::setPot(int pot)
{
    mPot = pot;
}

int Blackjack::getPot()
{
    return mPot;
}



void Blackjack::dealIn()
{
   HitPlayer();
   HitPlayer();
   mDealer.Hit(mDeck.Deal());
   mDealer.Hit(mDeck.Deal());
}

bool Blackjack::Wager(int wager)
{


    bool valid = true;



    //if wager is in range
    if (wager <= playerBank && wager > 0 && playerBank <= 0)
    {
        //sets pot to wager
        mPot = wager;



        //subtracts wager from bank
        playerBank = playerBank - wager;
    }
    //if bet is out of bounds
    else
    {
        valid = false;
    }

    //returns if player has money or not
    return valid;
}



void Blackjack::HitPlayer()
{
    mPlayer.Hit(mDeck.Deal());
}



void Blackjack::DoubleDown()
{
	//doubles pot
	mPot = mPot + mPot;

	//subtracts pot from player's bankroll
	playerBank = playerBank - mPot;

	//hits player with card
	mPlayer.Hit(mDeck.Deal());

}



void Blackjack::Win21()
{
	//winnings are 3:2 of  pot's total
    int winnings = (mPot) *3 /2;

	playerBank = playerBank + winnings;

}


bool Blackjack::DealerHand()
{
	//case for if dealer busts
	bool bust = false;

	//case for if dealer wants to hit
    bool hit = false;

	//asks dealer if they want to hit
    if(mDealer.FindCardTotal()<17)
    {
        hit = true;
    }

	//if dealer wants to hit
	while (bust == false && hit == true)
	{
		//deals card
		mDealer.Hit(mDeck.Deal());

		//if hand is larger than 21, dealer busts
        if (mDealer.FindCardTotal() > 20)
		{
			bust = true;
		}
		//if dealer doesn't bust, ask if dealer wants to hit
		if (bust == false)
		{
            if(mDealer.FindCardTotal()<16)
            {
                hit = true;
            }
		}
	}
	//returns if dealer busted or not
	return bust;
}

int Blackjack::getPlayerTotal()
{
    return mPlayer.FindCardTotal();
}

int Blackjack::getDealerTotal()
{
    return mDealer.FindCardTotal();
}


void Blackjack::Win()
{
	//calculates winnings
    int winnings = (mPot * 2);


	//adds winnings to playerBank
	playerBank = playerBank + winnings;
}



void Blackjack::Tie()
{
	//finds money in pot
    int winnings = mPot;

	//adds pot to bankroll
	playerBank = playerBank + winnings;
}

bool Blackjack::CheckBust()
{
    bool bust = false;
    if(mPlayer.FindCardTotal()>21)
    {
            bust = true;
    }
    return bust;
}

bool Blackjack::Check21()
{
    return mPlayer.FindCardTotal() == 21;
}
