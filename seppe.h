#ifndef SEPPE_H
#define SEPPE_H

#include "game.h"
#include "player.h"

namespace PXL2023
{
class seppe : public Player //seppe is Player
{
public:
    seppe( unsigned char instance = 0 )	: Player(instance)	{}
    const char* getName( void ) const						;
    int willYouRaise( unsigned int totalBet )				;
private:
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

    bool IsFirstBet();
    int Stage();
    int PreflopFiltering();
    int NumberOfCallersOnStart ();
    bool Bluffing(int BluffPercentage);
    int FirstBet(int Hand);

    bool Bluffed = false;
};
}
#endif // SEPPE_H
