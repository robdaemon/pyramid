*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* output the starting message
            lea     MESSAGE,a1              Loads message into address register 1
            move.b  #14,d0                  Move number 14 to d0
            trap    #15                     Display message
            
* input
*            move.b  #4,d0                   Task 4 reads a number from the keyboard into d1.l
*            trap    #15

            jsr     SHUFFLE                 Shuffle the deck
            
            bra.s   ENDGAME                 Exit the game

* how cards work -
* take number of card (0-15)
* divide by 13 - quotient gives you the suit, 0=Clubs, 1=Diamonds, 2=Hearts, 4=Spades
*                remainder gives you the card, 0=Ace, 1=Two, 2=Three, etc

SHUFFLE:    lea     CARDS,a0                put the source array in a0
            lea     SHUFFLED,a1             put the destination array in a1
            move.b  #NUMCARDS,d0            put the number of cards in d0
            jsr     MEMCPY
            rts                             we're done here

MEMCPY:     cmpi.b  #0,d0                   have we gotten to 0?
            blt.s   COPYDONE                yes, we're done here
            move.b  (a0)+,(a1)+             copy the byte from a0 to a1, incrementing both
            dbra    d0,MEMCPY               loop if d0 > -1

COPYDONE:   rts
            
ENDGAME:    move.b  #9,d0
            trap    #15         
            SIMHALT
            
* Put variables and constants here

CR:         equ     $0D                     ASCII CR
LF:         equ     $0A                     ASCII LF
MESSAGE:    dc.b    'Pyramid Solitaire',CR,LF     ASCII 0 terminated string
            dc.b    'by Robert Roland',CR,LF,0

NUMCARDS:   equ     52
CARDS:      dc.b    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52
SHUFFLED:   ds.w    CARDS
SEED:       dc.l    49152                   This is the default, but can be changed later

    END    START        ; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~0~
*~Tab size~4~
