#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int bet;
    char cards[5];
} hand;

int vals['T'+1] = {0};

int getScore(hand* h);

static int cmpChar(const void* a, const void* b) { return *(const char*)a - *(const char*)b; }
static int cmpHands(const void* a, const void* b) {
    hand* handA = (hand*)a;
    hand* handB = (hand*)b;
    int scoreA = getScore(handA);
    int scoreB = getScore(handB);
    if (scoreA != scoreB)
        return scoreA - scoreB;
    for (int i = 0; i < 5; i++) {
        int valA = vals[handA->cards[i]];
        int valB = vals[handB->cards[i]];
        if (valA != valB)
            return valA - valB;
    }
    return 0;
}

int getScore(hand* h) {
    // Check five of a kind
    bool isFiveOfAKind = true;
    for (int i = 0; i < 4; i++) {
        if (h->cards[i] != h->cards[i+1]) {
            isFiveOfAKind = false;
            break;
        }
    }
    if (isFiveOfAKind) return 7;
    
    // Create sorted copy of hand
    char cardSorted[5] = {0};
    memcpy(cardSorted, h->cards, 5);
    qsort(cardSorted, 5, sizeof(char), cmpChar);

    // Check four of a kind
    if (cardSorted[0] == cardSorted[3] || cardSorted[1] == cardSorted[4]) return 6;

    // Check if the hand has three of the same card
    bool isThreeOfAKind = false;
    char threeOfAKindChar = 0;
    for (int i = 0; i < 3; i++) {
        if (cardSorted[i] == cardSorted[i+1] && cardSorted[i+1] == cardSorted[i+2]) {
            threeOfAKindChar = cardSorted[i];
            isThreeOfAKind = true;
            break;
        }
    }

    // If there are three of a kind, it could be a full house
    if (isThreeOfAKind) {
        if ((cardSorted[0] == cardSorted[1] && cardSorted[0] != threeOfAKindChar)
            || (cardSorted[3] == cardSorted[4] && cardSorted[3] != threeOfAKindChar))
            return 5;
        return 4;
    }

    // Check for pairs
    char counts['T'+1] = {0};
    for (int i = 0; i < 5; i++)
        counts[h->cards[i]]++;
    int twoCounts = 0;
    for (int i = 0; i < 13; i++)
        twoCounts += counts["23456789TJQKA"[i]] == 2;
    if (twoCounts == 2) return 3;
    if (twoCounts == 1) return 2;
    return 1;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    for (int i = 0; i < 13; i++)
        vals["23456789TJQKA"[i]] = i + 1;
    FILE* in = fopen("input", "r");
    char* line = NULL;
    size_t len = 0;
    int total = 0;
    hand hands[1000] = {0};
    for (int i = 0; getline(&line, &len, in) != -1; i++) {
        memcpy(hands[i].cards, line, 5);
        hands[i].bet = atoi(line + 5);
    }
    qsort(hands, 1000, sizeof(hand), cmpHands);
    for (int i = 0; i < 1000; i++)
        total += hands[i].bet * (i + 1);
    printf("Total: %d\n", total);
    fclose(in);
    if (line) free(line);
    return EXIT_SUCCESS;
}
