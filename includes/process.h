#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdbool.h>
#include <project.h>

typedef struct paramNode {
  typNodeType p;
  struct paramNode * next;
} paramNode;

struct params_t {
  bool variable;
  unsigned int amount;
  // list
  paramNode * params;
};

struct function_info {
  typNodeType ret;
  
  identifierT id;

  struct params_t params;

  struct function_info * next;
};

struct var_info {
  typNodeType type;

  identifierT id;

  struct var_info * next;
};

void process_tree(nodeType * root, char * output_file_name, bool * success);

#endif