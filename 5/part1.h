typedef struct LinkedNode LinkedNode;
struct LinkedNode{
    int key;
    int val;
    LinkedNode* next;
};

typedef struct {
    LinkedNode** array;
    int capacity;
    int size;
} HashTable;
int hash(int x);
int hashIndexOf(int h, int length);
HashTable* initHashTable(int capacity);
void resizeHashTable(HashTable** htp);
void destroyLinkedList(LinkedNode* head);
void hashPut(HashTable** htp, int key, int val);
void destroyHashTable(HashTable* ht);
int hashGet(HashTable* ht, int key);
