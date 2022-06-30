#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
  char *data;
  int data_length;
  struct ListNode *prev;
  struct ListNode *next;
};

int arraycmp(char *a, char *b) {
  if (a == NULL || b == NULL) return -1;
  
  while (*a && *b) {
    if (*a != *b) {
      return 0;
    }
    a++;
    b++;
  }
  return 1;
}

int llcmp(struct ListNode *lla, struct ListNode *llb) {
  struct ListNode *lla_temp_node = lla;
  struct ListNode *llb_temp_node = llb;

  while (lla_temp_node != NULL && llb_temp_node != NULL) {
    if (arraycmp(lla_temp_node->data, llb_temp_node->data) == 0) {
      return 0;
    }
    
    lla_temp_node = lla_temp_node->next;
    llb_temp_node = llb_temp_node->next;
  }

  return lla_temp_node == NULL && llb_temp_node == NULL ? 1 : 0;
}


struct ListNode *write_stream_to_ll(struct ListNode *head, FILE *stream, size_t buffer_size) {
  char *buffer = '\0';
  struct ListNode *ll_current_node = head;
  ssize_t nread;

  while ((nread = getline(&buffer, &buffer_size, stream)) != -1) {
    ll_current_node->data = strdup(buffer);
    ll_current_node->data_length = nread;
    ll_current_node->data[nread] = '\0';

    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    ll_current_node->next = newNode;
    
    struct ListNode *prevNode = ll_current_node;
    ll_current_node = newNode;

    ll_current_node->prev = prevNode;
  }

  return ll_current_node;
}

void reverse_write_ll_to_stream(FILE *stream, struct ListNode *ll_tail) {
  struct ListNode *tmp = ll_tail;
  while (tmp != NULL) {
    if (tmp->data) {
      fwrite(tmp->data, sizeof(char), strlen(tmp->data), stream);
    }
    tmp = tmp->prev;
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


int main(int argc, char *argv[]) {
  if (argc >= 4) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(EXIT_FAILURE);
  }

  char *input_file_name = argv[1];
  char *output_file_name = argv[2];

  if (input_file_name && output_file_name) {
    if (strcmp(input_file_name, output_file_name) == 0) {
      fprintf(stderr, "reverse: input and output file must differ\n");
      exit(EXIT_FAILURE);
    }
  }

  FILE *input_stream = argc <= 1 ? stdin : fopen(input_file_name, "r");
  FILE *output_stream = argc <= 2 ? stdout : fopen(output_file_name, "rw");

  if (!input_stream || !output_stream) {
    char *file_name = !input_stream ? input_file_name : output_file_name;
    fprintf(stderr, "reverse: cannot open file '%s'\n",file_name);
    exit(EXIT_FAILURE);
  }

  struct ListNode *linked_list_a_head = malloc(sizeof(struct ListNode));
  struct ListNode *linked_list_b_head = malloc(sizeof(struct ListNode));
  struct ListNode *linked_list_a_tail = malloc(sizeof(struct ListNode));
  struct ListNode *linked_list_b_tail = malloc(sizeof(struct ListNode));

  size_t buffer_size = sizeof(char *);
  linked_list_a_tail = write_stream_to_ll(linked_list_a_head, input_stream, buffer_size);
  
  if (llcmp(linked_list_a_head, linked_list_b_head) == 1) {
    fprintf(stderr, "reverse: input and output file must differ\n");
    exit(EXIT_FAILURE);
  } 

  reverse_write_ll_to_stream(output_stream, linked_list_a_tail);

  fclose(input_stream);
  fclose(output_stream);
  free_ll_nodes(linked_list_a_head);
  free_ll_nodes(linked_list_b_head);
} 
