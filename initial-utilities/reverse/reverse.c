#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reverse.h"
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
  if (argc >= 4) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(EXIT_FAILURE);
  }

  char *input_file_name = argv[1];
  char *output_file_name = argv[2];

  FILE *input_stream = argc <= 1 ? stdin : fopen(input_file_name, "r");
  FILE *output_stream = argc <= 2 ? stdout : fopen(output_file_name, "rw");

  if (!input_stream || !output_stream) {
    fprintf(stderr, "reverse: cannot open file '%s'\n", !input_stream ? input_file_name : output_file_name);
    exit(EXIT_FAILURE);
  }

  struct stat input_file_stat, output_file_stat;
  if (fstat(fileno(input_stream), &input_file_stat) == -1 || fstat(fileno(output_stream), &output_file_stat) == - 1) {
    fprintf(stderr, "reverse: fstat error\n");
    exit(EXIT_FAILURE);
  }
  
  if (input_file_stat.st_ino == output_file_stat.st_ino) {
    fprintf(stderr, "reverse: input and output file must differ\n");
    exit(EXIT_FAILURE);
  }

  size_t buffer_size = sizeof(char *);
  struct ListNode *linked_list_a_head = malloc(sizeof(struct ListNode));
  linked_list_a_head = write_stream_to_ll(linked_list_a_head, input_stream, buffer_size);
  
  write_ll_to_stream(output_stream, linked_list_a_head);

  fclose(input_stream);
  fclose(output_stream);
  free_ll_nodes(linked_list_a_head);
}

struct ListNode *write_stream_to_ll(struct ListNode *head, FILE *stream, size_t buffer_size) {
  char *buffer = '\0';
  ssize_t nread;

  while ((nread = getline(&buffer, &buffer_size, stream)) != -1) {
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->data = strdup(buffer);
    newNode->data[nread] = '\0';
    newNode->next = head;
    head = newNode; 
  }
  free(buffer);
  return head;
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
