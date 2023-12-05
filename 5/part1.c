#include <stdio.h>
#include <stdlib.h>
#include "part1.h"

int hash(int x) {
    int ux = (unsigned int)x;
    ux ^= (ux >> 20) ^ (ux >> 12);
    return ux ^ (ux >> 7) ^ (ux >> 4);
}

int hashIndexOf(int h, int length) {
    return h & (length - 1);
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
        free(ht->array);
    }
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

int hashGet(HashTable* ht, int key) {
    int idx = hashIndexOf(hash(key), ht->capacity);
    LinkedNode* curNode = ht->array[idx];
    while (curNode != NULL) {
        if (curNode->key == key) return curNode->val;
        curNode = curNode->next;
    }
    return -1;
}

void hashPut(HashTable** htp, int key, int val) {
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
    double lf = ++(ht->size) / ht->capacity;
    if (lf >= 0.65) resizeHashTable(htp);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    HashTable* ht = initHashTable(2);
    hashPut(&ht, 8, 27);
    hashPut(&ht, 4, 192);
    hashPut(&ht, 13, 2);
    int a = hashGet(ht, 8);
    int b = hashGet(ht, 4);
    int c = hashGet(ht, 13);
    printf("%d %d %d\n", a, b, c);
    destroyHashTable(ht);
}
