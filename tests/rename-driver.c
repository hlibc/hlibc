#include <stdio.h>

int main(int argc, char **argv)
{
        if ( argc == 3 ) 
        {
		rename (argv[1], argv[2]);
        }

        return 0;
}
