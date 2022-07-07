#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list_lib.h"


void write_stream_to_ll(struct ListNode **head, FILE *stream, size_t buffer_size) {
  char *buffer = '\0';
  ssize_t nread;

  while ((nread = getline(&buffer, &buffer_size, stream)) != -1) {
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->data = strdup(buffer);
    newNode->data[nread] = '\0';
    newNode->next = *head;
    *head = newNode;
  }
  free(buffer);
}

void write_ll_to_stream(FILE *stream, struct ListNode *ll_head) {
  struct ListNode *tmp = ll_head;
  while (tmp != NULL) {
    if (tmp->data) {
      fwrite(tmp->data, sizeof(char), strlen(tmp->data), stream);
    }
    tmp = tmp->next;
  }
}

void free_ll_nodes(struct ListNode* head) {
  struct ListNode* tmp;
  while (!tmp) {
    tmp = head;
    head = head->next;
    if (head->data) free(head->data);
    free(tmp);
  }
}
