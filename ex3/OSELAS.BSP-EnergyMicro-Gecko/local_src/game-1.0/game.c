#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int init()
{
    if (init_gamepad() == EXIT_FAILURE) {
        printf("Error: unable to init gamepad.\n");
        return EXIT_FAILURE;
    }
    if (init_framebuffer() == EXIT_FAILURE) {
        printf("Error: unable to init framebuffer.\n");
        return EXIT_FAILURE;
    }
    new_game();
    return EXIT_SUCCESS;
}

void deinit()
{
    deinit_gamepad();
    deinit_framebuffer();
}

int init_gamepad()
{
    device = fopen("/dev/gamepad", "rb");
    if (!device) {
        printf("Unable to open driver device, maybe you didn't load the module?\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGIO, &sigio_handler) == SIG_ERR) {
        printf("An error occurred while register a signal handler.\n");
        return EXIT_FAILURE;
    }
    if (fcntl(fileno(device), F_SETOWN, getpid()) == -1) {
        printf("Error setting pid as owner.\n");
        return EXIT_FAILURE;
    }
    long oflags = fcntl(fileno(device), F_GETFL);
    if (fcntl(fileno(device), F_SETFL, oflags | FASYNC) == -1) {
        printf("Error setting FASYNC flag.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void deinit_gamepad()
{
    fclose(device);
}

int check_winner(int p1, int p2){
  if(p1==1){
      if(p2==1){
          printf("Draw\n");
          return 0;
      }
      if(p2==2){
          printf("Computer Wins!\n");
          Cscore= Cscore + 1;
          return 2;
      }
      if(p2==3){
          printf("Player Wins\n");
          Pscore = Pscore + 1;
          return 1;
      }
  }

  else  if(p1==2){
          if(p2==2){
              printf("Draw\n");
              return 0;
          }
          if(p2==3){
              printf("Player Wins!\n");
              Pscore = Pscore + 1;
              return 1;
          }
          if(p2==1){
              printf("Computer Wins!\n");
              Cscore= Cscore + 1;
              return 2;
          }
      }

      else if(p1==3){
          if(p2==3){
              printf("Draw\n");
              return 0;
          }
          if(p2==2){
              printf("Computer Wins!\n");
              Cscore= Cscore + 1;
              return 2;
          }
          if(p2==1){
              printf("Player Wins!\n");
              Pscore = Pscore + 1;
              return 1;

          }
      }
else{
  printf("Something went wrong\n");
  return 0;
}
}

int AI_move(){
  return rand()%3+1
}

int main(int argc, char *argv[])
{
  int R=1;
    int P=2;
    int S=3;
    int i;
    int Pscore =0;
    int Cscore =0;
    int choice;
    int computer
    int state // 0 = draw, 1 = player1 win, 2 = player2 win
    srand(time(NULL));
    printf("Rock=1 , Paper= 2, and Scissors= 3\n");

    for(i=0;i<5;i++){
      state = 0
      /*
          TODO: Draw idle screen with "make your choice"
      */
        printf("Enter your choice:");
        /*
           TODO:
           Handle button press here and translate it to a choice
           Someting like: choice = handlePlayerMove()
           Will return either 1,2 or 3
        */

            computer = AI_move()
            state = check_winner(choice, computer)
        /*
            TODO:
            Handle graphics update here based on winner gotten from state
        */

            }
            if(Cscore > Pscore ){
                printf("Computer wins %d to %d\n",Cscore,Pscore);
            }
            else if(Cscore < Pscore ){
                printf("Player wins %d to %d\n",Pscore,Cscore);
            }
           else if(Cscore = Pscore ){
                printf("No winner it is a draw!\n");
            }

	exit(EXIT_SUCCESS);
}
