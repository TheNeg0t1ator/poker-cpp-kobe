#include <iostream>
#include <string.h>

#include "shootout.h"
#include "tournament.h"
#include "king_of_aces.h"
#include "bart.h"
#include "kobed.h"
#include "seppe.h"
using namespace std;

int main( int argumentCount, char * argumentVector[] )
{
	srand( (unsigned int) time( NULL ) );
	Tournament tour;

    for( unsigned char i = 0 ; i < 8 ; i++ )
    {
		tour.registerPlayer( new PXL2022::KingOfAces( i ), PXL_2022 );
		tour.registerPlayer( new PXL2022::Bart( i ), PXL_2021 );
        tour.registerPlayer( new PXL2023::KobeD( i ), PXL_2023_KOBE);
        tour.registerPlayer( new PXL2023::seppe( i ), PXL_2023_SEPPE);
	}

	if( argumentCount > 1 && ( strcmp( argumentVector[argumentCount-1], "stats" ) == 0 ) )
	{
        runStatistics( tour, 50 );
	}
	else
    {
		/*const Player * winnaar = */tour.start();
	}
	return( 0 );
}
