
#include "Blackjack.h"

/************************************************************************
*	Purpose:	one arg constructor
*
*	Entry:		int bankroll is the amount Player can use in their 
*				bankroll
*
*	Exit:		Displays message containing amount in bankroll, 
*				shuffles the deck twice, and sets playerBank to bankroll
************************************************************************/

Blackjack::Blackjack(int bankroll)
{
	//entry message


	//sets playerBank to bankroll
	playerBank = bankroll;

	//shuffles the deck
	mDeck.Shuffle();
	mDeck.Shuffle();

	//warning message

}

/************************************************************************
*	Purpose:	Acts as the directory for the program, has the basic 
*				rules algorithm
*
*	Entry:		none
*
*	Exit:		Asks player if they want to play, then while player 
*				doesn't want to end, deals cards, and sets twentyOne 
*				case to false, calls Wager and returns boolean 
*				stillGotMoney, and if true, calls Playerhand and returns
*				bust case. If bust is false and twentyOne is false, then
*				calls Dealerhand, and returns dealerBust. Displays 
*				dealer's hands and if dealer didn't bust, checks if player
*				had higher hand, and if so, calls Win, or else if they 
*				tied, calls Tie, or else the player loses, and if the 
*				dealer did bust, calls win, and if the player busts, 
*				informs player of loss, and if the player gets 21, calls
*				Win21. Then, the hands are cleared, and if the player ran
*				out of money, game ends, or if the player selects to
*				end, the game ends.
************************************************************************/

void Blackjack::PlayTheGame()
{
	//used to see if player wishes to end game
	bool end = false;

	//used to see if player busts
	bool bust = false;

	//used to see if player wins with blackjack
	bool twentyOne = false;

	//used to see if dealer busts
	bool dealerBust = false;
	
	//used to see if player still has money
	bool stillGotMoney = true;

	cout << "Are you ready to play? y=yes, n=no: ";
	
	//calls Continue to see if player wishes to play
	end = Continue();

	while (end == false)
	{
		//resets blackjack case to false
		twentyOne = false;
		
		//deals cards
		mPlayer.Hit(mDeck.Deal());
		mPlayer.Hit(mDeck.Deal());
		mDealer.Hit(mDeck.Deal());
		mDealer.Hit(mDeck.Deal());

		//asks player for wager, and returns if the player has more
		stillGotMoney = Wager();

		//if the player has money
		if (stillGotMoney == true)
		{
			//calls to player's turn, and returns if they busted
			bust = PlayerHand(twentyOne);

			//if they didn't bust or get blackjack
			if (bust == false && twentyOne == false)
			{
				//calls dealer's turn, and returns if the dealer busted
				dealerBust = DealerHand();
				
				//displays hands
				DisplayHands();
				cout << "Dealer's hand is\n";

				//displays dealer's cards, face up
				mDealer.Player::DisplayHand();
				cout << "\n";

				//if dealer didn't bust
				if (dealerBust == false)
				{
					//if player has more than Dealer
					if (mPlayer.FindTotal() > mDealer.FindTotal())
					{
						//player wins
						Win();
					}
					//if the player and dealer tied
					else if (mPlayer.FindTotal() == mDealer.FindTotal())
					{
						//player ties
						Tie();
					}
					//if player loses
					else
					{
						//inform of loss
						cout << "Player loses\n\n";
					}
				}
				//if dealer busts
				else
				{
					//player wins
					Win();
				}
			}
			//if player busts
			else if (bust == true )
			{
				//inform of loss
				cout << "Player loses\n\n";
			}
			//if player gets blackjack
			else if (twentyOne == true)
			{
				//player wins blackjack case
				Win21();
			}
			//empties hands
			mPlayer.ClearHand();
			mDealer.ClearHand();
		}
		//if player runs out of money
		else
		{
			//surprise sound
			PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME);
			cout << "You're outta cash!\n\n";

			//ends the game
			end = true;
		}
		//if bankroll is more than 0
		if (playerBank.GetmTotal() > 0)
		{
			//ask player if he wants to play again
			cout << "Do you want to play again?: ";
			end = Continue();
		}
	}
}

/************************************************************************
*	Purpose:	Acts as the player's turn. Asks for doubledown, or moves on
*
*	Entry:		twentyOne, by reference
*
*	Exit:		Displays hands, then if player's total isn't 21, asks
*				user if he wants to double down, and if he does, then 
*				check if player has enough money, and if he does, call
*				DoubleDown, and return if bust. If player can't double
*				down, informs user and calls HitPlayer and returns if 
*				bust. If the player doesn't want to double down, then
*				calls Hitplayer, and returns if bust. Or if blackjack
*				sets twentyOne to true, returns bust status.
*				
************************************************************************/

bool Blackjack::PlayerHand(bool & twentyOne)
{
	//checks if player wants to continue
	bool end = false;
	
	//bust case
	bool bust = false;
	
	//displays hands
	DisplayHands();

	//if player doesn't have blackjack
	if (mPlayer.FindTotal() != 21)
	{
		cout << "Do you wish to double down?: ";

		//yes is false
		end = Continue();

		//if player wants to continue
		if (end == false)
		{
			//if money is more than pot
			if (mPot.GetmTotal() < playerBank.GetmTotal())
			{
				//calls DoubleDown, returns bust case
				bust = DoubleDown();
			}
			//if player doesn't have enough money
			else
			{
				cout << "Error, your bet's too large to double down\n\n";

				//calls Hitplayer, returns bust case
				bust = HitPlayer();
			}
		}

		//if the player doesn't want to double down
		else
		{
			//calls Hitplayer, returns bust case
			bust = HitPlayer();
		}

	}
	//if blackjack
	else
	{
		//sets twentyOne to true
		twentyOne = true;
	}
	//returns if user busted or not
	return bust;
}

/************************************************************************
*	Purpose:	Asks for wager, displays bankroll, doesn't allow player
*				to bet too much.
*
*	Entry:		none
*
*	Exit:		if player has money, displays bankroll and asks for wager
*				then while check is false, reads in wager, and if wager
*				is in range, sets pot to wager, sets check to true, and 
*				subtracts wager from playerBank. If wager is out of 
*				bounds, informs user. if player has no money, sets
*				haveMoney to false. Then returns if the player has 
*				money or not.
*
************************************************************************/

bool Blackjack::Wager()
{
	//case if player has money or not
	bool haveMoney = true;

	//player's wager
	int wager = 0;
	
	//check to see if wager is within limits
	bool check = false;
	
	//if player has money
	if (playerBank.GetmTotal() != 0)
	{
		//displays bankroll, and asks for wager
		cout << "Your bankroll is currently " << playerBank.GetmTotal() << '\n';
		cout << "\nWhat's your wager?: ";

		//while check is false
		while (check == false)
		{
			//reads in wager.
			cin >> wager;

			//if wager is in range
			if (wager <= playerBank.GetmTotal() && wager > 0)
			{
				//sets pot to wager
				mPot = wager;

				//sets check to true
				check = true;

				//subtracts wager from bank
				playerBank = playerBank - wager;
			}
			//if bet is out of bounds
			else
			{
				//inform user
				cout << "Bet out of bounds, enter again: ";
			}
		}
	}
	//if no money is left
	else
	{
		//sets haveMoney to false;
		haveMoney = false;
	}

	//returns if player has money or not
	return haveMoney;
}

/************************************************************************
*	Purpose:	Displays both the dealer and player's hand, as well as
*				the pot.
*
*	Entry:		none
*
*	Exit:		Displays hands and pot to screen
*
************************************************************************/

void Blackjack::DisplayHands()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "Dealer: ";
	mDealer.DisplayHand();
	cout << "\n\n\n";
	cout << "\t\tThe Pot: ";
	cout << mPot.GetmTotal();
	cout << "\n\n\nPlayer: ";
	mPlayer.DisplayHand();
	cout << "\n\n\n\n\n";
}

/************************************************************************
*	Purpose:	Default input function, asks user yes or no.
*
*	Entry:		none
*
*	Exit:		While the check is false, reads in play, and if y
*				sets check to true, and if n, sets end to true and
*				sets check to true, or else informs user of improper
*				entry.
*
************************************************************************/

bool Blackjack::Continue()
{
	//check for correct value entered
	bool check = false;
	
	//read in char
	char play = 0;

	//returns if player wants to end or not
	bool end = false;

	//y gives false
	while (check == false)
	{
		//reads in play
		play = _getch();

		switch (play)
		{
		//if y
		case 'y':
			//check is true
			check = true;
			break;

		//if n
		case 'n':
			//check is true
			end = true;

			//end is true
			check = true;

			break;

		//if neither
		default:
			cout << "Error, input again: ";
		}
	}
	//return end case
	return end;
}

/************************************************************************
*	Purpose:	lets the player hit cards until bust or 21 or asks to stay
*
*	Entry:		none
*
*	Exit:		while player wants to hit, and while player didn't bust,
*				and while player didn't get 21, deals card to player, 
*				displays hands, if cards are higher than 21, bust case
*				is true, or if player has 21, set temp21 to true, or
*				if bust is false and test is false, ask player if they
*				want to hit again, and returns if player busted or not
*
************************************************************************/

bool Blackjack::HitPlayer()
{
	//boolean case to see if player busted
	bool bust = false;

	//case to see if player hits
	bool hit = false;

	//case to see if player has 21
	bool temp21 = false;

	//asks player if they want to hit
	hit = mPlayer.HitStay();

	//while player wants to hit, not bust, and doesn't have 21
	while (hit == true && bust == false && temp21 == false)
	{
		//hits player with card
		mPlayer.Hit(mDeck.Deal());
		DisplayHands();

		//if player busts, sets bust to true
		if (mPlayer.FindTotal() > 21)
		{
			bust = true;
		}

		//if 21, sets twentyOne to true
		if (mPlayer.FindTotal() == 21)
		{
			temp21 = true;
		}

		//if not bust or 21, ask player if they want to hit
		if (bust == false && temp21 == false)
		{
			hit = mPlayer.HitStay();
		}
	}
	return bust;
}

/************************************************************************
*	Purpose:	Logic for the case of a doubledown
*
*	Entry:		none
*
*	Exit:		adds mPot to mPot, subtracts mPot from playerBank
*				hits player with a card, and if player busts, return
*				true, and displays player's hand, and returns if player
*				busted or not.
*
************************************************************************/

bool Blackjack::DoubleDown()
{
	//checks if player busted
	bool bust = false;

	//doubles pot
	mPot = mPot + mPot;

	//subtracts pot from player's bankroll
	playerBank = playerBank - mPot;

	//hits player with card
	mPlayer.Hit(mDeck.Deal());

	//if player busted, set bust to true
	if (mPlayer.FindTotal() > 21)
	{
		bust = true;
	}

	cout << "\n";
	
	//display player's hand
	mPlayer.DisplayHand();

	//returns if player busted or not
	return bust;
}

/************************************************************************
*	Purpose:	Specific win instance for blackjack.
*
*	Entry:		none
*
*	Exit:		Tells player they have blackjack, adds winnings to 
*				player's bankroll
*
************************************************************************/

void Blackjack::Win21()
{
	//winnings are 3:2 of  pot's total
	int winnings = (mPot.GetmTotal()) *3 /2;

	
	cout << "Blackjack!!\n"
		<< "Player wins " << winnings << " which is 3:2 of pot rounded down\n\n";

	//adds winnings to bankroll
	playerBank = playerBank + winnings;

}

/************************************************************************
*	Purpose:	Logic for dealer's hand, determines when to hit or stay.
*
*	Entry:		none
*
*	Exit:		finds out if dealer wants to hit or stay, and while 
*				dealer doesn't bust, and they want to hit, hit dealer
*				displays hands, and if player has more than 21, sets bust
*				to true, and if bust is false, asks dealer wants to hit
*				or stay, and returns if dealer busted
*
************************************************************************/

bool Blackjack::DealerHand()
{
	//case for if dealer busts
	bool bust = false;

	//case for if dealer wants to hit
	bool hit = true;

	//asks dealer if they want to hit
	hit = mDealer.HitStay();

	//if dealer wants to hit
	while (bust == false && hit == true)
	{
		//deals card
		mDealer.Hit(mDeck.Deal());

		//display hands
		DisplayHands();

		//if hand is larger than 21, dealer busts
		if (mDealer.FindTotal() > 21)
		{
			bust = true;
		}
		//if dealer doesn't bust, ask if dealer wants to hit
		if (bust == false)
		{
			hit = mDealer.HitStay();
		}
	}
	//returns if dealer busted or not
	return bust;
}

/************************************************************************
*	Purpose:	Win instance for every other case.
*
*	Entry:		none
*
*	Exit:		informs user of win, and adds winnings to bankroll
*
************************************************************************/

void Blackjack::Win()
{
	//calculates winnings
	int winnings = (mPot.GetmTotal() * 2);
	cout << "Winner!!\n"
		<< "Player wins pot\n\n";

	//adds winnings to playerBank
	playerBank = playerBank + winnings;
}

/************************************************************************
*	Purpose:	Instance that player ties with house
*
*	Entry:		none
*
*	Exit:		informs user of tie, returns bet
*
************************************************************************/

void Blackjack::Tie()
{
	//finds money in pot
	int winnings = mPot.GetmTotal();
	cout << "Tie!\n"
		<< "Player's bet is returned\n";

	//adds pot to bankroll
	playerBank = playerBank + winnings;
}
