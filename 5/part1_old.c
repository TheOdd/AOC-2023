#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "part1.h"

long hash(long x) {
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53L;
    x ^= x >> 33;
    return x;
}

int hashIndexOf(long h, int length) {
    return h % length;
}

// - capacity must be a power of 2
// - array property must be freed
HashTable* initHashTable(int capacity) {
    HashTable* ht = calloc(1, sizeof(*ht));
    ht->array = calloc(capacity, sizeof(LinkedNode*));
    ht->capacity = capacity;
    return ht;
}

void destroyLinkedList(LinkedNode* node) {
    if (node->next == NULL) {
        free(node);
        return;
    }

    destroyLinkedList(node->next);
    free(node);
}

void resizeHashTable(HashTable** htp) {
    // Make new HashTable
    HashTable* ht = *htp;
    HashTable* newHt = initHashTable(ht->capacity * 2);
    for (int i = 0; i < ht->capacity; i++) {
        if (!ht->array[i]) continue;
        LinkedNode* curNode = ht->array[i];
        while (curNode->next != NULL) {
            hashPut(&newHt, curNode->key, curNode->val);
            curNode = curNode->next;
        }
        hashPut(&newHt, curNode->key, curNode->val);
        destroyLinkedList(ht->array[i]);
    }
    free(ht->array);
    free(ht);
    *htp = newHt;
}

void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        if (!ht->array[i]) continue;
        destroyLinkedList(ht->array[i]);
    }
    free(ht->array);
    free(ht);
}

long hashGet(HashTable* ht, long key) {
    int idx = hashIndexOf(hash(key), ht->capacity);
    LinkedNode* curNode = ht->array[idx];
    while (curNode != NULL) {
        if (curNode->key == key) return curNode->val;
        curNode = curNode->next;
    }
    return -1;
}

void hashPut(HashTable** htp, long key, long val) {
    HashTable* ht = *htp;
    int idx = hashIndexOf(hash(key), ht->capacity);
    if (!ht->array[idx]) {
        ht->array[idx] = calloc(1, sizeof(LinkedNode));
        ht->array[idx]->key = key;
        ht->array[idx]->val = val;
    } else {
        // Add to end of LinkedList at idx
        LinkedNode* curNode = ht->array[idx];
        while (curNode->next != NULL)
            curNode = curNode->next;
        curNode->next = calloc(1, sizeof(LinkedNode));
        curNode->next->key = key;
        curNode->next->val = val;
    }
    double lf = ++(ht->size) / (double)ht->capacity;
    if (lf >= 0.65) resizeHashTable(htp);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    long lowest = LONG_MAX;
    char* line = NULL;
    size_t len = 0;
    HashTable* mappings[7];
    for (int i = 0; i < 7; i++)
        mappings[i] = initHashTable(64);
    int curTable = 0;
    while (getline(&line, &len, in) != -1) {

    }
    fclose(in);
    if (line) free(line);
    for (int i = 0; i < 7; i++)
        destroyHashTable(mappings[i]);
    printf("Lowest: %ld\n", lowest);
}
