#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_STRING    30
#define MAX_MESSAGES  40
#define FIFO_NAME	"buffer"

void Error( char* sPrefix )
{
    printf("\n");
    perror( sPrefix );
    exit( EXIT_FAILURE );
}

int main( void )
{
    //sleep ( 1 );

    char sBuffer[ MAX_STRING ];
    int  fd = open( FIFO_NAME, O_RDWR ),
         i;

    if ( fd < 0 )
        Error( "child fifo open" );

    for ( i = 1; i <= MAX_MESSAGES; ++i )  {
        sprintf( sBuffer, "Line number %d", i );
        printf( "Child sending '%s'\n", sBuffer );

        if ( write( fd, sBuffer, MAX_STRING ) < 0 )
            Error( "child write" );

        /* sleep every now and then... */
        if ( 0 == ( i % 25 ) ) {
            printf("Sleep ... \n");
            sleep( 1 );
        }
    }

    close( fd );

    unlink( FIFO_NAME );
}
