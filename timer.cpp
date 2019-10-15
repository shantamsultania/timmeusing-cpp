#include <stdio.h>
#include <time.h>         //this is header file for time
#include <windows.h>
void ClearConsoleToColors(int ForgC, int BackC);
COORD coord = {0, 0};
void gotoxy (int x, int y)
{
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main()
{

    long i = 0;                      /* Loop counter              */
    clock_t now = 0;                 /* Holds initial clock time  */
    int interval = 1;                /* Seconds interval for o/p  */
    int elapsed = 0;
    int min=0,MIN=0,hrs=0,sec=0;
    int d=0,f=0;
    now = clock();
    ClearConsoleToColors(2,1);               /* Get current clock time    */



    for(i = 0L ;  ; i++)
    {
      elapsed = (clock()-now)/CLOCKS_PER_SEC;

      if(elapsed>=interval)
      {
        interval += 1;
            if(elapsed%60==0)
        {
            min=elapsed/60;
            d=60*min;
                if(min%60==0)
            {
                hrs=min/60;
                f=60*hrs;
            }
        }
        sec=elapsed-d;
        MIN=min-f;
         if(hrs<10)
        {
            gotoxy(2,4);printf("0%d",hrs);
            }
        else
        {
            gotoxy(2,4);printf(":%d",hrs);
            }
        if(min<10)
        {
            gotoxy(4,4);printf(":0%d",MIN);
            }
        else
        {
            gotoxy(4,4);printf(":%2d",MIN);
            }

        if(sec<10)
        {
            gotoxy(7,4);printf(":0%d",sec);
            }
        else
        {
            gotoxy(7,4);printf(":%2d",sec);
            }
        gotoxy(7,7);
        printf("%dhrs:%dmin:%dsec",hrs,MIN,sec);
      }
    }

 return 0;
}


void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
                   //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                       //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
                         //A return value... indicating how many chars were written
                      //   not used but we need to capture this since it will be
                       //   written anyway (passing NULL causes an access violation).
     DWORD count;

                     //This is a structure containing all of the console info
                          // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
                     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                          //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                           //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

