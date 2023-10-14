#include "seppe.h"
#include "game.h"

namespace PXL2023
{
    const char * seppe::getName( void ) const
    {
        return "Seppe";
    }
    bool seppe::IsFirstBet(){
        bool FirstBet = false;
        if (getBet()<= getGame()->getBlind() || (getGame()->getDistanceToDealer(this) == 2 && getBet() == getGame()->getBlind()*2)){
            FirstBet = true;
        }

        return FirstBet;
    }

    int seppe::Stage(){
        if(getTable()->isPreFlop()){return PREFLOP;}
        else if(getTable()->isFlop()){return POSTFLOP;}
        else if(getTable()->isTurn()){return TURN;}
        else if(getTable()->isRiver()){return RIVER;}
        else return 5;
    }

    int seppe::PreflopFiltering()
    {
        //initss
        int Hand = 0;
        int LutSuited [14][14] = {
            {HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //ace
            {LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//two
            {LOW_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//three
            {LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//four
            {LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//five
            {MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND},//six
            {MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND},//seven
            {MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND},//eight
            {MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND},//nine
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//ten
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //jack
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //queen
            {HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //king
            {HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND} //ace
        };
        int LutNotSuited [14][14] = {
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //ace
            {UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//two
            {UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//three
            {UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//four
            {UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//five
            {UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//six
            {LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND},//seven
            {LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND},//eight
            {LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND},//nine
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND},//ten
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND},//jack
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//queen
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//king
            {HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//ace
        };

        //fiding highest card
        bool fliphand = false;
        if (getHand().getFirstCard()->getRank() <= getHand().getSecondCard()->getRank() || getHand().getSecondCard()->getRank() == 1)
        {
            fliphand = true;
        }

        // filtering hand combinations
        if (getHand().getFirstCard()->getSuit() == getHand().getSecondCard()->getSuit()) // suited
        {
            if(fliphand)
            {
                Hand = LutSuited[getHand().getSecondCard()->getRank()-1][getHand().getFirstCard()->getRank()-1];
            }
            else
            {
                Hand = LutSuited[getHand().getFirstCard()->getRank()-1][getHand().getSecondCard()->getRank()-1];
            }
        }
        else // not suited
        {
            if(fliphand)
            {
                Hand = LutNotSuited[getHand().getSecondCard()->getRank()-1][getHand().getFirstCard()->getRank()-1];
            }
            else
            {
                Hand = LutNotSuited[getHand().getFirstCard()->getRank()-1][getHand().getSecondCard()->getRank()-1];
            }
        }

        return Hand;
    }

    int seppe::NumberOfCallersOnStart ()
    {
        int total = 0;

        if (IsFirstBet())
        {
            unsigned int CurrentBet = getGame()->getBlind()*2;
            for (int i = 0; i < getGame()->getPlayers().size(); i++)
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

    bool seppe::Bluffing(int BluffPercentage)
    {
        if(BluffPercentage <= 0)
        {
            if((rand()%BluffPercentage) == 0){return true;}
            else{return false;}
        }
        else {return false;}
    }

    int seppe::willYouRaise( unsigned int totalBet )
    {
        // initialization
        bool Fold = false;
        int BigBlind = getGame()->getBlind() *2;
        int Bet = 0;

        // initialization of settings
        int MaxBet = getChips();
        float FoldBarrier = 0.45;
        unsigned int AllInPercentage = 35;
        int BluffPercentage = -1;
        unsigned int EarlyPosition = (getGame()->getPlayers().size() * 0.25);
        unsigned int MidPosition = (getGame()->getPlayers().size() * 0.75);

        switch( instance ) // settings
        {
        case 0:
            // default intializations
            break;
        case 1:
            MaxBet = getChips();
            FoldBarrier = 40;
            AllInPercentage = 40;
            BluffPercentage = -1;
            EarlyPosition = (getGame()->getPlayers().size() * 0.25);
            MidPosition = (getGame()->getPlayers().size() * 0.75);
            break;
        case 2:
            MaxBet = getChips();
            FoldBarrier = 55;
            AllInPercentage = 30;
            BluffPercentage = -1;
            EarlyPosition = (getGame()->getPlayers().size() * 0.25);
            MidPosition = (getGame()->getPlayers().size() * 0.75);
            break;
        case 3:
            MaxBet = getChips();
            FoldBarrier = 0.50;
            AllInPercentage = 37;
            BluffPercentage = -1;
            EarlyPosition = (getGame()->getPlayers().size() * 0.25);
            MidPosition = (getGame()->getPlayers().size() * 0.75);
            break;
        }

        STAGE GameState = STAGE(Stage());
        int  Hand = PreflopFiltering();

        switch (GameState) // game state logic
        {
        case PREFLOP:
            if(IsFirstBet()){
                if(((getGame()->getDistanceToDealer(this)-3)%getGame()->getPlayers().size())>= EarlyPosition){
                    if(Hand >= HIGH_HAND)
                    {
                        if(getChips()<(20 * BigBlind)){Bet = (2 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((20 * BigBlind) <= getChips()<(35 * BigBlind)){Bet = (2.25 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((35 * BigBlind) <= getChips()<(60 * BigBlind)){Bet = (2.5 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else{Bet = (2.75 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                    }
                    else{Fold = true;}
                }
                else if(((getGame()->getDistanceToDealer(this)-3)%getGame()->getPlayers().size())>= MidPosition){
                    if(Hand >= MEDIUM_HAND)
                    {
                        if(getChips()<(20 * BigBlind)){Bet = (2 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((20 * BigBlind) <= getChips()<(35 * BigBlind)){Bet = (2.25 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((35 * BigBlind) <= getChips()<(60 * BigBlind)){Bet = (2.5 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else{Bet = (2.75 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                    }
                    else{Fold = true;}
                }
                else
                {
                    if(Hand >= LOW_HAND)
                    {
                        if(getChips()<(20 * BigBlind)){Bet = (2 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((20 * BigBlind) <= getChips()<(35 * BigBlind)){Bet = (2.25 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else if ((35 * BigBlind) <= getChips()<(60 * BigBlind)){Bet = (2.5 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                        else{Bet = (2.75 * BigBlind) + (NumberOfCallersOnStart() * 1);}
                    }
                    else{Fold = true;}
                }
            }
            else
            {

            }

            if(Fold && (!Bluffed))
            {
                if(getBet()>= (getChips() * FoldBarrier)){return CHECK;}
                else{return FOLD;}
            }
            else
            {
                if(Bluffing(BluffPercentage))
                {
                    Bluffed = true;
                    return ALLIN;
                }
                else
                {
                    if((Bet * 100)/getChips() >= AllInPercentage)
                    {
                        return ALLIN;
                    }
                    else if((Bet - totalBet) >= 0)
                    {
                        return Bet - totalBet;
                    }
                    else {return CHECK;}
                }
            }

            break;
        case POSTFLOP:
            return CHECK;
            break;
        case TURN:
            return CHECK;
            break;
        case RIVER:
            return CHECK;
            break;
        }
        std::cout <<"number of calls this round" <<NumberOfCallersOnStart ()<<std::endl;
        return( 0 );
    }
}
