#include "kobed.h"
#include "game.h"

namespace PXL2023
{
int KobeD::willYouRaise( unsigned int totalBet ){

    if(totalBet ==0){}//gwn d'r ff iets mee doen voor de compiler te laten zwijgen XD
    PokerRank pokerHand = getRank();
    printf("\n handCat: %d\n",pokerHand.getCategory());




    if (pokerHand.getCategory() >= FULL_HOUSE)
    {
        return 10000;
    }

    if (pokerHand.getCategory() <= TWO_PAIR)
    {
        return -1;
    }
    else
    {
        if (pokerHand.getCategory() >= THREE_OF_A_KIND)
        {
            if(KobeD::NumberOfCallersOnStart()>=3){
              return 20000;
            }


        }
        return 0;
    }


    return 0;

}


const char * KobeD::getName( void ) const
{
    return "Kobeke";
}

bool KobeD::IsFirstBet(){
    bool FirstBet = false;
    if (getBet()<= getGame()->getBlind() || (getGame()->getDistanceToDealer(this) == 2 && getBet() == getGame()->getBlind()*2)){
        FirstBet = true;
    }

    return FirstBet;
}

int KobeD::NumberOfCallersOnStart ()
{
    int total = 0;

    if (IsFirstBet())
    {
        unsigned int CurrentBet = getGame()->getBlind()*2;
        for (size_t i = 0; i < getGame()->getPlayers().size(); i++)
        {
            Player* PlayerAtTable = getGame()->getPlayers().at((getGame()->getDealerLocation()+3+i)%getGame()->getPlayers().size());
            if (PlayerAtTable == this)
            {
                break;
            }

            if (PlayerAtTable->getBet() == CurrentBet)
            {
                total++;
            }
            else if (PlayerAtTable->getBet() > CurrentBet)
            {
                CurrentBet = PlayerAtTable->getBet();
            }

        }
    }
    return total;
}

}
