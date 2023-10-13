#ifndef KOBED_H
#define KOBED_H

#include "player.h"

namespace PXL2023
{
class KobeD : public Player
{
public:
    KobeD( unsigned char instance = 0 )	: Player(instance)	{}
    int willYouRaise( unsigned int totalBet );
    const char* getName( void ) const;


};
}
#endif // KOBED_H
