#ifndef PXL_2023_SAMY_H
#define PXL_2023_SAMY_H

#include "player.h"

namespace PXL2023
{
class PXL_2023_SAMY : public Player // PXL_2023_SAMY is a Player
{
public:
    PXL_2023_SAMY(unsigned char instance = 0) : Player(instance) {}
    const char* getName() const;
    int willYouRaise(unsigned int totalBet);

private:
    bool shouldBluff();
    int betSafely(int amount);
    bool stopRaising = false;
    static int amountOfWins;

    // Renamed functions
    int chooseAction(int randomValue, unsigned int totalBet);
    int choosePreFlopAction(int randomValue, unsigned int totalBet);
    int chooseFlopAction(int randomValue, unsigned int totalBet);
    int chooseTurnAction(int randomValue, unsigned int totalBet);
    int chooseRiverAction(int randomValue, unsigned int totalBet);
};
}
#endif // PXL_2023_SAMY_H
