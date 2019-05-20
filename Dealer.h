#pragma once
#include "Deck.h"
#include <string.h>

///The Dealer class has both parameters private since this part of the game must
///be hidden from the player. Regular methods such as the constructor, 
///function to get the points, the reset when a new round starts and
///a function to give the string parameter of the cards of the dealer
class Dealer {
	int points;	/*!< how many points the dealer has*/

	Card dealerCards[2]; /*!< Since the dealer's cards area fixed number, we set 2 cards already*/
public:	
	
	//!Constructor of the class
	Dealer(Deck& deckParam);

	//!function to get the points
	int getPoints();

	//!Function to update points
	void reset(Deck& decko);

	///Return the string name of the card to select the image
	///the parameter is the card that is choosen
	std::string getCard(int param);
};