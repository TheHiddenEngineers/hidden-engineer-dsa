#include <iostream>
#include <unordered_map>
using namespace std;

/* ============================================================
   ================== SINGLY LINKED LIST ======================
   ============================================================ */

struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};

/* ---------- Basic Operations ---------- */

void insertAtBeginning(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

void deleteValue(Node*& head, int key) {
    if (!head) return;

    if (head->data == key) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    while (temp->next && temp->next->data != key)
        temp = temp->next;

    if (temp->next) {
        Node* delNode = temp->next;
        temp->next = temp->next->next;
        delete delNode;
    }
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/* ---------- Reverse Linked List ---------- */

Node* reverseIterative(Node* head) {
    Node* prev = NULL;
    Node* curr = head;

    while (curr) {
        Node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

Node* reverseRecursive(Node* head) {
    if (!head || !head->next)
        return head;

    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

/* ---------- Middle of Linked List ---------- */

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/* ---------- Detect Cycle (Floyd) ---------- */

bool detectCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }
    return false;
}

/* ---------- Merge Two Sorted Lists ---------- */

Node* mergeSorted(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (l1 && l2) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1) ? l1 : l2;
    return dummy.next;
}

/* ---------- Remove Nth Node From End ---------- */

Node* removeNthFromEnd(Node* head, int n) {
    Node dummy(0);
    dummy.next = head;

    Node* first = &dummy;
    Node* second = &dummy;

    for (int i = 0; i <= n; i++)
        first = first->next;

    while (first) {
        first = first->next;
        second = second->next;
    }

    Node* delNode = second->next;
    second->next = second->next->next;
    delete delNode;

    return dummy.next;
}

/* ---------- Intersection of Two Linked Lists ---------- */

Node* getIntersection(Node* headA, Node* headB) {
    Node* a = headA;
    Node* b = headB;

    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

/* ---------- Palindrome Linked List ---------- */

Node* reverseHelper(Node* head) {
    Node* prev = NULL;
    while (head) {
        Node* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (!head || !head->next)
        return true;

    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* secondHalf = reverseHelper(slow);
    Node* firstHalf = head;

    while (secondHalf) {
        if (firstHalf->data != secondHalf->data)
            return false;
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    return true;
}

/* ---------- Rotate Linked List ---------- */

Node* rotateRight(Node* head, int k) {
    if (!head || !head->next)
        return head;

    Node* temp = head;
    int length = 1;

    while (temp->next) {
        temp = temp->next;
        length++;
    }

    temp->next = head; // Make circular
    k = k % length;
    int steps = length - k;

    while (steps--)
        temp = temp->next;

    Node* newHead = temp->next;
    temp->next = NULL;

    return newHead;
}

/* ============================================================
   ================= DOUBLY LINKED LIST =======================
   ============================================================ */

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    DNode(int val) {
        data = val;
        prev = next = NULL;
    }
};

void insertDoublyAtHead(DNode*& head, int val) {
    DNode* newNode = new DNode(val);

    if (head) {
        head->prev = newNode;
        newNode->next = head;
    }

    head = newNode;
}

/* ============================================================
   ================= MULTILEVEL FLATTEN =======================
   ============================================================ */

struct MultiNode {
    int data;
    MultiNode* next;
    MultiNode* child;

    MultiNode(int val) {
        data = val;
        next = child = NULL;
    }
};

MultiNode* flatten(MultiNode* head) {
    if (!head) return head;

    MultiNode* curr = head;

    while (curr) {
        if (curr->child) {
            MultiNode* nextNode = curr->next;
            curr->next = flatten(curr->child);

            MultiNode* temp = curr->next;
            while (temp->next)
                temp = temp->next;

            temp->next = nextNode;
            curr->child = NULL;
        }
        curr = curr->next;
    }

    return head;
}

/* ============================================================
   ====================== LRU CACHE ===========================
   ============================================================ */

class LRUCache {
private:
    struct CacheNode {
        int key, value;
        CacheNode* prev;
        CacheNode* next;

        CacheNode(int k, int v) {
            key = k;
            value = v;
            prev = next = NULL;
        }
    };

    int capacity;
    unordered_map<int, CacheNode*> cache;
    CacheNode *head, *tail;

    void addNode(CacheNode* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(CacheNode* node) {
        CacheNode* prev = node->prev;
        CacheNode* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new CacheNode(0, 0);
        tail = new CacheNode(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;

        CacheNode* node = cache[key];
        removeNode(node);
        addNode(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            removeNode(cache[key]);
            cache.erase(key);
        }

        if (cache.size() == capacity) {
            CacheNode* lru = tail->prev;
            removeNode(lru);
            cache.erase(lru->key);
        }

        CacheNode* newNode = new CacheNode(key, value);
        addNode(newNode);
        cache[key] = newNode;
    }
};

/* ============================================================
   ========================== MAIN =============================
   ============================================================ */

int main() {

    cout << "Singly Linked List Demo:" << endl;

    Node* head = NULL;
    insertAtEnd(head, 1);
    insertAtEnd(head, 2);
    insertAtEnd(head, 3);
    printList(head);

    head = reverseIterative(head);
    printList(head);

    cout << "Middle: " << findMiddle(head)->data << endl;

    cout << "Program executed successfully." << endl;

    return 0;
}
