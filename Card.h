#pragma once
#include <iostream>
#include <string>

/*!Cards class that will be contained in a deck, it must have
2 characteristics. The suit and the number from 1 - 10 including
a king, a queen and a jack.*/
class Card{
	//!The code for the suit of the cards are:	
	int cardSuit; /*!<  1 = Diamond	2 = Club	3 = Heart	4 = Spade */
	
	int cardRank; /*!< For the card rank 1 = A, 2 = 2, 3 = 3, .. 11 = J, 12 = Q, 13 = K*/
public:
	//!Default constructor
	Card() :cardSuit(0), cardRank(0) {}
	//!Constructor of the class
	Card(int suit, int rank) : cardSuit(suit), cardRank(rank) {}

	//!Functions to return rank and suit
	int getRank() { return cardRank; };
	int getSuit() { return cardSuit; };

	///Function that build cards name, useful to load the
	///image when the card is displayed on the screen
	std::string toString();

	//!Function to return the equivalent points that the cards worths
	int getPoint();

};
