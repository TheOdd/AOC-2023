typedef struct LinkedNode LinkedNode;
struct LinkedNode{
    long key;
    long val;
    LinkedNode* next;
};

typedef struct {
    LinkedNode** array;
    int capacity;
    int size;
} HashTable;
long hash(long x);
int hashIndexOf(long h, int length);
HashTable* initHashTable(int capacity);
void resizeHashTable(HashTable** htp);
void destroyLinkedList(LinkedNode* head);
void hashPut(HashTable** htp, long key, long val);
void destroyHashTable(HashTable* ht);
long hashGet(HashTable* ht, long key);
