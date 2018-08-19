#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52

int deck[NUM_CARDS];

/*
* how cards work -
* take number of card (0-15)
* divide by 13 - quotient gives you the suit, 0=Clubs, 1=Diamonds, 2=Hearts, 4=Spades
*                remainder gives you the card, 0=Ace, 1=Two, 2=Three, etc
*/
enum suits
{
    clubs,
    diamonds,
    hearts,
    spades
};

void clearDeck()
{
    for (int i = 0; i < NUM_CARDS; i++)
    {
        deck[i] = i;
    }
}

void shuffle()
{
    for (int i = NUM_CARDS; i > 0; i--)
    {
        int toSwap = i + (rand() % (NUM_CARDS - i));
        int temp = deck[i];
        deck[i] = deck[toSwap];
        deck[toSwap] = temp;
    }
}

void printDeck()
{
    for (int i = 0; i < NUM_CARDS; i++)
    {
        int card = deck[i];
        int suit = card / 13;
        int cardValue = card % 13;

        printf("card is: ");
        switch (cardValue)
        {
        case 0:
            printf(" Ace ");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            printf(" %d ", cardValue + 1);
            break;
        case 10:
            printf(" Jack ");
            break;
        case 11:
            printf(" Queen ");
            break;
        case 12:
            printf(" King ");
            break;
        }

        printf("of");

        switch (suit)
        {
        case clubs:
            printf(" Clubs ");
            break;
        case diamonds:
            printf(" Diamonds ");
            break;
        case hearts:
            printf(" Hearts ");
            break;
        case spades:
            printf(" Spades ");
            break;
        }

        printf("  ");

        if ((i % 2) == 0)
        {
            printf("\r\n");
        }
    }
}

void game()
{
    clearDeck();
    shuffle();
    printDeck();
}

int main(int argc, char *argv)
{
    srand(time(NULL));

    game();

    printf("Press enter to exit");
    getchar();

    return 0;
}