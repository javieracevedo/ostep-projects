#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <stddef.h>

typedef struct ListNode {
  char *data;
  struct ListNode *next;
} ListNode;

int arraycmp(char *a, char *b);
int llcmp(struct ListNode *lla, struct ListNode *llb);
void write_stream_to_ll(struct ListNode **head, FILE *stream, size_t buffer_size);
void reverse_write_ll_to_stream(FILE *stream, struct ListNode *ll_tail);
void write_ll_to_stream(FILE *stream, struct ListNode *ll_head);
void free_ll_nodes(struct ListNode* head);

#endif
