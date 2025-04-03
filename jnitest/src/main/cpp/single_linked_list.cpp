#include <android/log.h>

// Android log function wrappers
static const char *testLinkedListTAG = "TEST_LINKED_LIST";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, testLinkedListTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, testLinkedListTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, testLinkedListTAG, __VA_ARGS__))


typedef int ElementType;

struct Node {
    ElementType data;
    struct Node *next;
};

void HeadInsert(Node *head, ElementType element) {
    LOGI("HeadInsert -> element = %d", element);
    Node *newNode = new Node;
    newNode->data = element;
    newNode->next = head->next;
    head->next = newNode;
}

void TailInsert(Node *head, ElementType element) {
    LOGI("TailInsert -> element = %d", element);
    Node *newNode = new Node;
    newNode->data = element;
    newNode->next = nullptr;
    Node *p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = newNode;
}

void PrintList(Node *head) {
    LOGI("PrintList -> head = %p", head);
    Node *p = head->next;
    while (p != nullptr) {
        LOGI("PrintList -> data = %d", p->data);
        p = p->next;
    }
}

int GetLinkedListLenth(Node *head) {
    int lenth = 0;
    if (head == nullptr) {
        return lenth;
    }
    Node *p = head->next;
    while (p != nullptr) {
        lenth++;
        p = p->next;
    }
    return lenth;
}

void DestroyList(Node *head) {
    LOGI("DestroyList -> head = %p", head);
    Node *p = head->next;
    while (p != nullptr) {
        Node *q = p->next;
        delete p;
        p = q;
    }
    head->next = nullptr;
}

void TestSingleLinkedList() {
    LOGI("TestSingleLinkedList triggered");
    // 新建一个头节点
    Node *head = new Node;
    head->next = nullptr;
    // 插入数据
    ElementType data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < length; i++) {
        HeadInsert(head, data[i]);
    }
    PrintList(head);
    LOGI("GetLinkedListLenth -> length = %d", GetLinkedListLenth(head));
    DestroyList(head);
    delete head;
    head = nullptr;
    // 打印检查
    LOGI("GetLinkedListLenth -> length = %d", GetLinkedListLenth(head));
    LOGI("PrintList -> head = %p", head);
}