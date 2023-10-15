#ifndef SEPPE_H
#define SEPPE_H

#include "player.h"

namespace PXL2023
{
class seppe : public Player //seppe is een Player Object
{
public:
    seppe( unsigned char instance = 0 )	: Player(instance)	{}
    const char* getName( void ) const;
    int willYouRaise( unsigned int totalBet );
private:
    //Readability
    #define FOLD -1
    #define CHECK 0
    #define ALLIN getChips()
    enum HAND
    {
        UNPLAYABLE_HAND = 0,
        LOW_HAND,
        MEDIUM_HAND,
        HIGH_HAND,
    };
    enum STAGE
    {
        PREFLOP = 0,
        POSTFLOP,
        TURN,
        RIVER
    };

    //General Game Logic
    int Stage();
    bool Fold = false;

    //Bluffing Logic
    bool Bluffing(int BluffPercentage);
    bool Bluffed = false;

    //PreFlop Logic
    int NumberOfCallersOnStart ();
    bool IsFirstBet();
    int PreFlopFiltering();
    int PreFlopBetting(int Hand, unsigned int EarlyPosition, unsigned int MidPosition ,float FoldBarrier,int BluffPercentage, unsigned int AllInPercentage, unsigned int totalBet);

    //colluding Logic
    bool OtherSeppeAtTable();
    int DataViaChips();
};
}
#endif // SEPPE_H
