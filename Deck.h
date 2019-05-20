#pragma once
#include "Card.h"
/*!This is the card's deck class, it must contain 52 cards with
four different suits: Clubs, diamonds, hearts and spades. This class
must have a function equivalent to a draw and a reset when one round is finished.*/
class Deck {
	Card allCards[52];/*!< Since the cards are a fixed number, no dynamic memory is needed*/
	
	int currentCard;/*!< Current card that will de dealt to the player or dealer*/
public:
	///Constructor and initializator of the class that will
	///create the deck and initialize the 52 cards
	Deck();

	//!Function that deals the first card based on the currentCard variable
	Card dealCard();
	//!Function to shuffle the cards inside the deck
	void shuffle();
};