#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <tos.h>
#include <gem.h>

short work_in[11], work_out[57];
VdiHdl handle;
short contrl[12], intin[128];
short ptsin[128], intout[128], ptsout[128];
short gr_hwchar, gr_hhchar, gr_hwbox, gr_hhbox, dummy;
#define NUM_CARDS 52

int deck[NUM_CARDS];

#define CARD_ROWS 6

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 200

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

void clear_deck()
{
    for (int i = 0; i < NUM_CARDS; i++)
    {
        deck[i] = i;
    }
}

void shuffle()
{
    for (int i = NUM_CARDS; i >= 0; i--)
    {
        int toSwap = i + (rand() % (NUM_CARDS - i));
        int temp = deck[i];
        deck[i] = deck[toSwap];
        deck[toSwap] = temp;
    }
}

int card_suit(int card)
{
    return card / 13;
}

char *suit_name(int card)
{
    int suit = card / 13;
    switch (suit)
    {
    case hearts:
        return "H";
        break;
    case diamonds:
        return "D";
        break;
    case clubs:
        return "C";
        break;
    case spades:
        return "S";
        break;
    }

    return "";
}

void card_face(char *buffer, int card)
{
    char *suit = suit_name(card);
    int cardValue = card % 13;
    switch (cardValue)
    {
    case 0:
        sprintf(buffer, "Ace %s", suit);
        break;
    case 1:
        sprintf(buffer, "2 %s", suit);
        break;
    case 2:
        sprintf(buffer, "3 %s", suit);
        break;
    case 3:
        sprintf(buffer, "4 %s", suit);
        break;
    case 4:
        sprintf(buffer, "5 %s", suit);
        break;
    case 5:
        sprintf(buffer, "6 %s", suit);
        break;
    case 6:
        sprintf(buffer, "7 %s", suit);
        break;
    case 7:
        sprintf(buffer, "8 %s", suit);
        break;
    case 8:
        sprintf(buffer, "9 %s", suit);
        break;
    case 9:
        sprintf(buffer, "10 %s", suit);
        break;
    case 10:
        sprintf(buffer, "Jack %s", suit);
        break;
    case 11:
        sprintf(buffer, "Queen %s", suit);
        break;
    case 12:
        sprintf(buffer, "King %s", suit);
        break;
    }
}

// draw_card will draw a card on the screen. x and y are the upper left
void draw_card(int card, short x, short y)
{
    // cards are 20 pixels tall x 30 wide
    short pxy[] = {x, y, x + 50, y + 30};
    vsl_type(handle, 1);
    vsl_width(handle, 1);
    vsl_color(handle, G_BLACK);
    vsf_interior(handle, 2);
    vsf_perimeter(handle, 1);
    v_rfbox(handle, pxy);

    switch (card_suit(card))
    {
    case hearts:
    case diamonds:
        vst_color(handle, G_RED);
        break;
    case spades:
    case clubs:
        vst_color(handle, G_BLACK);
        break;
    }
    vst_point(handle, 8, &dummy, &dummy, &dummy, &dummy);
    // 0 = left justified, 5 = top line
    vst_alignment(handle, 0, 5, &dummy, &dummy);
    vst_effects(handle, 0);
    // vqt_width(handle, 8, &dummy, &dummy, &dummy);
    char *card_text = malloc(50);
    card_face(card_text, card);
    v_gtext(handle, x + 5, y + 4, card_text);
    free(card_text);
}

void open_vwork()
{
    int i;
    for (i = 0; i < 10; work_in[i++] = 1)
        ;
    work_in[2] = 2;
    handle = graf_handle(&gr_hwchar, &gr_hhchar, &gr_hwbox, &gr_hhbox);
    v_opnvwk(work_in, &handle, work_out);
}

void draw_board()
{
    int card_num = 0;
    int x = 0;
    int y = 0;
    for (int rows = 0; rows < 6; rows++)
    {
        // calculate starting position
        x = (SCREEN_WIDTH / 2) - (26 * (rows + 1));

        for (int row_card = 0; row_card <= rows; row_card++)
        {
            draw_card(deck[card_num++], x, y);

            x = x + 52;
        }

        y = y + 24;
    }
}

void game()
{
    clear_deck();
    shuffle();
    draw_board();
}

int main(int argc, char *argv)
{
    appl_init();
    open_vwork();
    v_clrwk(handle);

    srand(time(NULL));

    game();

    getchar();

    v_clsvwk(handle);
    appl_exit();

    return 0;
}