#ifndef CEYHAN_H
#define CEYHAN_H
#include "player.h"

namespace PXL2023
{
    class Ceyhan : public Player //Ceyhan is Player
    {
        public:
            Ceyhan( unsigned char instance = 0 )	: Player(instance)	{}
            const char* getName( void ) const						; //{ return "Ceyhan"; }
            int willYouRaise( unsigned int totalBet )				;
    };
}
#endif // CEYHAN_H
