// testmod_IO.c
// a user spave program to access mod_IO.ko module register as device node "ce4052"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{ char temp1, temp2;
  int  fd,i;
  printf("opening file /dev/ce4052\n);
  fd = open("/dev/ce4052", O_RDWR);
  if (fd < 0)
     { printf("open /dev/ce4052 failed\n");
       exit (-1);
     }
  else
    printf("open /dev/ce4052 successfully\n");

    temp1 = ‘E;
    i=write(fd,temp1,1);
    printf ("number of char write  = %d\n",i);   
     
    i = read(fd,temp2,1);
    printf ("number of char read  = %i\n",i);

    if (i < 0)
       {  printf ("read error\n");
	  close(fd);
	  exit (-1);
       }
    else 
       printf ("value read = %c\n", temp2);
    
    close(fd);
    exit(0);	
}

