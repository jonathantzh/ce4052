// select.c
// The program use select() system call to wait for data from two inputs, with a timeout of 5 sec
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h> /* for atoi() */

int process_fd1(void), process_fd2(void);


int main (int argc, char *argv[])
{ int n, fd, sock, max_fd, duration = 5;
  fd_set input;
  struct timeval timeout;

  if (argc !=2){
     printf("Usage: %s 'second' \n", argv[0]);
     return 1;
     }
  else{
     duration = atoi(argv[1]);
     printf("Wait for %i sec\n", duration);
     }

  printf("Initialize input set\n");
/* Initialize the input set */
  FD_ZERO(&input);
  FD_SET(STDIN_FILENO, &input);
 // FD_SET(sock, &input);

//  printf("calculate max_fd\n"); 
 // max_fd = (sock > fd ? sock : fd) + 1;

  printf("max_fd = %d, now initialize timeout structure\n", max_fd); 
  /* Initialize the timeout structure */
  timeout.tv_sec = duration;
  timeout.tv_usec = 0;

 printf("call select()....\n");

  /* Do the select, will typically sleep based on mask returned by poll method, and trigger again when queue wakeup */ 
  n = select(max_fd, &input, NULL, NULL, &timeout);
 
  /* See if there was an error */
  if (n < 0)
     perror("select failed");
  else
  if (n == 0)
     puts("TIMEOUT");
  else { /* n >0, we have input, from which source? */
       printf("n = %d. Input from ??\n", n);
 /*      if (FD_ISSET(fd, &input))
          process_fd1();
       if (FD_ISSET(sock, &input))
          process_fd2();
*/ 
      }
}


int  process_fd1()
{ printf("getting data from fd1\n");
  return 1 ;
}

int  process_fd2()
{ printf("getting data from fd2\n");  
  return 1 ;
}
