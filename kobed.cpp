#include "kobed.h"
#include "game.h"

namespace PXL2023
{

const char * KobeD::getName( void ) const
{
    if( getChips() > 128 )
    {
        return "MEEEEEOOOOOOOWWW !!! (KD)";
    }else{
        return "Kobeke";
    }
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

int KobeD::randomCopyCat(){

    Player * PlayerToCopy = nullptr;
    size_t y = 0;
    while (1) {
        y++;
        if(y == getGame()->getPlayers().size() || y== 20){
            break;
        }
        int i = rand() % getGame()->getPlayers().size();
        if((getGame()->getPlayers()[i]->hasHand()) && (getGame()->getPlayers()[i] != this)){
            PlayerToCopy = getGame()->getPlayers()[i];
            break;
        }

    }

    if(PlayerToCopy == nullptr){
        return 0;
    }else{
        return PlayerToCopy->getBet();
    }

    return 0;
}

int KobeD::moneyCopyCat(){

    Player * PlayerToCopy = nullptr;
    unsigned int maxMoneyToCopy = 0;
    for(size_t i = 0; i< getGame()->getPlayers().size(); i++ ){
        if((getGame()->getPlayers()[i]->hasHand()) && (getGame()->getPlayers()[i] != this)){
            if(getGame()->getPlayers()[i]->getChips() > maxMoneyToCopy){
                maxMoneyToCopy = getGame()->getPlayers()[i]->getChips();
                PlayerToCopy = getGame()->getPlayers()[i];
            }
        }
    }

    if(PlayerToCopy == nullptr){
        return 0;
    }else{
        return PlayerToCopy->getBet();
    }

    return 0;
}

int KobeD::ChooseCat(){

    if(rand() % 1){
        return randomCopyCat();
    }else{
        return moneyCopyCat();
    }
    return 0;
}

int KobeD::willYouRaise( unsigned int totalBet ){

    if(totalBet ==0){}//gwn d'r ff iets mee doen voor de compiler te laten zwijgen XD
    PokerRank pokerHand = getRank();
    //printf("\n handCat: %d\n",pokerHand.getCategory());
    int callerCount = (3+instance) % 7;

    if (pokerHand.getCategory() >= FULL_HOUSE)
    {
        return 10000;
    }

    switch (instance) {
    case 0:
    {

        if(getGame()->getTable()->isPreFlop()){
            return moneyCopyCat();
        }else{
        if (pokerHand.getCategory() <= ONE_PAIR)
        {
            return -1;
        }
        else
        {
            if (pokerHand.getCategory() >= THREE_OF_A_KIND)
            {
                if(NumberOfCallersOnStart ()>=callerCount){
                    return 200000;
                }


            }else{
                return 0;
            }
        }

        }


    }
    break;
    case 1:
        return randomCopyCat();
        break;
    case 2:
        return moneyCopyCat();
        break;
    case 3:
        return ChooseCat();
        break;
    default:
        return moneyCopyCat();
        break;
    }





    return 0;
}

}

