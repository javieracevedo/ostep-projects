#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <stddef.h>

typedef struct ListNode {
  char *data;
  struct ListNode *next;
} ListNode;

void write_stream_to_ll(struct ListNode **head, FILE *stream, size_t buffer_size);
void write_ll_to_stream(FILE *stream, struct ListNode *ll_head);
void free_ll_nodes(struct ListNode* head);

#endif