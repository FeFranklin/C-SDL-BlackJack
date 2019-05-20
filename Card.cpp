#include "Card.h"
#include <string>

/*!Function to creat string that is used to select the image when displayed*/
std::string Card::toString()
{
	std::string suit;

	switch(cardSuit){
	case 1:
		suit = "diamond";break;
	case 2:
		suit = "club"; break;
	case 3:
		suit = "heart"; break;
	case 4:
		suit = "spade"; break;
	default:
		break;
	}	
	suit = "imgs/" + suit + std::to_string(cardRank) + ".bmp";
	
	return suit;
}
/*! Functio to return the card's points */
int Card::getPoint()
{
	if (cardRank > 10)
		return 10;
	else
		return cardRank;
}
