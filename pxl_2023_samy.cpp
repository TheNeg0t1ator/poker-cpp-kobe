#include "pxl_2023_samy.h"
#include "game.h"

namespace PXL2023
{
int PXL_2023_SAMY::amountOfWins = 0;

const char* PXL_2023_SAMY::getName() const
{
    if (getChips() > 128)
    {
        return "OW YEAH";
    }
    if (getChips() < getGame()->getBlind() * 10)
    {
        return "OH NO you sussy bakas";
    }
    return "PXL_2023_SAMY";
}

int PXL_2023_SAMY::willYouRaise(unsigned int totalBet)
{
    static int num = 0;
    std::cout << amountOfWins++ << " & " << num++ << std::endl;

    PokerRank mijnHandRank = getRank();
    int randomValue = std::rand() % 100;

    if (getTable()->isPreFlop()) // Pre-flop
    {
        return choosePreFlopAction(randomValue, totalBet);
    }
    else if (getTable()->isFlop()) // Flop
    {
        return chooseFlopAction(randomValue, totalBet);
    }
    else if (getTable()->isTurn()) // Turn
    {
        return chooseTurnAction(randomValue, totalBet);
    }
    else // River
    {
        return chooseRiverAction(randomValue, totalBet);
    }

    // Default action if not covered by the strategy.
    return 0;
}

int PXL_2023_SAMY::choosePreFlopAction(int randomValue, unsigned int totalBet)
{
    if (randomValue < 20) {
        // Strategy 1: Aggressive Bluffing
        return (getGame()->getBlind() * 2);
    } else if (randomValue < 60) {
        // Strategy 2: Conservative Play
        return totalBet;
    } else {
        // Strategy 3: Fold
        return -1;
    }
}

int PXL_2023_SAMY::chooseFlopAction(int randomValue, unsigned int totalBet)
{
    if (randomValue < 30) {
        // Strategy 4: Continue with existing strategy
        // return betSafely(getGame()->getBlind() * 3);
        return 0;
    } else if (randomValue < 80) {
        // Strategy 5: Raise
        return (getGame()->getBlind() * 2);
    } else {
        // Strategy 6: Fold
        return -1;
    }
}

int PXL_2023_SAMY::chooseTurnAction(int randomValue, unsigned int totalBet)
{
    if (randomValue < 40) {
        // Strategy 7: Aggressive Bluffing on Turn
        return (getGame()->getBlind() * 2);
    } else if (randomValue < 80) {
        // Strategy 8: Call
        return totalBet;
    } else {
        // Strategy 9: Fold
        return -1;
    }
}

int PXL_2023_SAMY::chooseRiverAction(int randomValue, unsigned int totalBet)
{
    if (randomValue < 10) {
        // Strategy 10: Very Aggressive on River
        return (getGame()->getBlind() * 3);
    } else if (randomValue < 60) {
        // Strategy 11: Conservative on River
        return totalBet;
    } else {
        // Strategy 12: Fold
        return -1;
    }
}
}
