#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int bet;
    char cards[5];
} hand;

int vals['T'] = {0};

static int cmpChar(const void* a, const void* b) { return *(const char*)a - *(const char*)b; }

int getScore(hand* h) {
    bool isFiveOfAKind = true;
    for (int i = 0; i < 4; i++) {
        if (h->cards[i] != h->cards[i+1]) {
            isFiveOfAKind = false;
            break;
        }
    }
    if (isFiveOfAKind) return 7;
    char cardSorted[5];
    strncpy(cardSorted, h->cards, 5);
    if (cardSorted[0] == cardSorted[3] || cardSorted[1] == cardSorted[4]) return 6;
    bool isThreeOfAKind = false;
    for (int i = 0; i < 3; i++) {
        if (cardSorted[i] == cardSorted[i+1] && cardSorted[i+1] == cardSorted[i+2]) {
            isThreeOfAKind = true;
            break;
        }
    }
    if (isThreeOfAKind) {
        if (cardSorted[0] == cardSorted[1] || cardSorted[3] == cardSorted[4]) return 5;
        return 4;
    }

}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    for (int i = 0; i < 13; i++)
        vals["23456789TJQKA"[i]] = i + 1;
    
}
