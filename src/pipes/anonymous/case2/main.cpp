#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STRING      30
#define MAX_MESSAGES    50

int main( void )
{
    int  i;
    int  fd[ 2 ];
    char s[ MAX_STRING ];

    setbuf( stdout, NULL );

    if ( pipe( fd ) < 0 )  {
        perror( "pipe" );
        exit( EXIT_FAILURE );
    }

    if ( 0 == fork() )  {
        /* child will write back to parent, so close read fd */
        close( fd[ 0 ] );

        for ( i = 1; i <= MAX_MESSAGES; ++i )  {
            sprintf( s, "Line number %d", i );
            printf( "Child sending '%s'\n", s );
            write( fd[ 1 ], s, MAX_STRING );

            /* sleep now and then, just for fun */
            if ( 0 == ( i % 8 ) )
                sleep( 1 );
        }

        close( fd[ 1 ] );
    } else  {
        /* parent will read from child, so close write fd */
        close( fd[ 1 ] );

        for ( i = 0; i < MAX_MESSAGES; ++i )  {
            read( fd[ 0 ], s, MAX_STRING );
            printf( "Parent got '%s'\n", s );
        }

        close( fd[ 0 ] );
    }
}
