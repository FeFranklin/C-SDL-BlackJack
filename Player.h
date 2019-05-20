#pragma once
#include "Deck.h"

//!Player class that has a "hand" of maximum 5 cards and has actions with them
class Player {	
public:
	///Players cards are not defined, so memory will be alocated dynamically
	///Since player's cards are not a hidden, they are set to public 
	Card* playerCartas;/*!< the number of cards the player has*/

	int card_num; /*!< The number of cards the player has*/
	int points; /*!< The points of the player */

	//!Default constructor of the class
	Player(Deck& decko);

	//!Destructor of the class to delete the dynamic memory allocated
	~Player();

	//!Function to set the cards to the player in ascending order
	void SetCards(Deck& theDeck);

	//!Function to return if player BUSTED
	bool bust();

	//!Reset the player after the round finishes
	void resetP(Deck& decko);
};