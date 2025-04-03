#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

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

// 函数声明
void HeadInsert(Node *head, ElementType element);
void TailInsert(Node *head, ElementType element);
void PrintList(Node *head);
void DestroyList(Node *head);
void TestSingleLinkedList();

#endif // SINGLE_LINKED_LIST_H