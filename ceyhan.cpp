#include "ceyhan.h"
#include "game.h"

// Easy to use for user
#define Cards_0 ( getTable()->isPreFlop() )
#define Cards_3 ( getTable()->isFlop() )
#define Cards_4 ( getTable()->isTurn() )
#define Cards_5 ( getTable()->isRiver() )

// Define aliases with league ranks
#define Bronze          HIGH_CARD
#define Silver          ONE_PAIR
#define Gold            TWO_PAIR
#define Platinum        THREE_OF_A_KIND
#define Emerald         STRAIGHT
#define Diamond         FLUSH
#define Master          FULL_HOUSE
#define Grand_Master    FOUR_OF_A_KIND
#define Challenger      STRAIGHT_FLUSH

// ShortKey's
#define Elo             MyElo.getCategory()

#define Skin_1          getHand().getFirstCard()->getSuit()
#define Skin_2          getHand().getSecondCard()->getSuit()

#define Chroma_1        MyElo.getHand().at(0)
#define Chroma_2        MyElo.getHand().at(1)
#define Chroma          Chroma_1 - Chroma_2

#define Gun             ( getGame()->getBlind() *
#define Ammo             ) - totalBet;


namespace PXL2023
{

    const char * Ceyhan::getName( void ) const
    {

        if( getChips() > 128 )
        {
            return "Aphelios, the 200-year champion! Yheeee!";
        }
        else if(  getChips() > 68 &&  getChips() < 70  )
        {
            return "Great job, Cey! That pentakill was amazing!";
        }
        else if( getChips() < getGame()->getBlind() * 10  )
        {
            return "Cey with a J";
        }
        else
        {
            return "Ceyhan";
        }
    }

    int Ceyhan::willYouRaise( unsigned int totalBet )
    {
        PokerRank MyElo = getRank();
        auto  Primary_Hand = getHand().getFirstCard();
        if ( Cards_0 ) {

            switch ( Elo ) {

            case Bronze:
                // Handle Bronze case
                if( Skin_1 == Skin_2)
                {
                    switch ( Chroma ) {
                    case 1:
                        return 9999;
                    case 13:
                        // Connected Cards
                        return Gun 8 Ammo;
                        break;
                    case 2:
                        // Missing 1 Cards in the middle.
                        return (-1);
                    case 3:
                        // Missing 2 Cards in the middle.
                        return 9999;
                    case 4:
                        // Missing 3 Cards in the middle.
                        return Gun 1 Ammo;
                        break;
                    default:
                        // Bad Cards
                        return ( -1 );
                        break;
                    }
                }
                break;

            case Silver:
                // Handle Silver case

                if ( Primary_Hand->getRank() >= 10 )
                {
                    return totalBet;
                }
                else
                {
                    Gun 10 Ammo;
                }
                break;
            default:
                // Handle the default case
                return ( -1 );
                break;
            }
        }

        else if( Cards_3 || Cards_4 || Cards_5)
        {
            switch ( Elo ) {

            case Bronze:
                // Handle Bronze case
                return Gun 1 Ammo;
                break;

            case Silver:
                // Handle Silver case
                return Gun 2 Ammo;
                break;

            case Gold:
                // Handle Gold case
                return Gun 3 Ammo;
                break;

            case Platinum:
                // Handle Platinum case
            case Emerald:
                // Handle Emerald case
            case Diamond:
                // Handle Diamond case
            case Master:
                // Handle Master case
            case Grand_Master:
                // Handle Grand_Master case
            case Challenger:
                // Handle Challenger case
                return 9999;
                break;

            default:
                // Handle the default case
                return ( -1 );
                break;
            }


        }


        if ( totalBet == 1 ){
            return 0;
        }
        return 0;
    }
}
