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
    perror( sPrefix );
    exit( EXIT_FAILURE );
}

int main( void )
{
    if ( mknod( FIFO_NAME, S_IFIFO | 0600, 0 ) < 0 )
        Error( "mknod" );

    setbuf( stdout, NULL );

    char sBuffer[ MAX_STRING ];
    int  fd = open( FIFO_NAME, O_RDWR ),
         i;

    if ( fd < 0 )
        Error( "parent fifo open" );

    for ( i = 0; i < MAX_MESSAGES; ++i )  {
        if ( read( fd, sBuffer, MAX_STRING ) < 0 )
            Error( "parent read" );

        printf( "Parent got '%s'\n", sBuffer );

        /* sleep every now and then */
        if ( 0 == ( i % 20 ) ) {
            printf("Sleep ...");
            sleep( 1 );
        }
    }

    unlink( FIFO_NAME );
}
