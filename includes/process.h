#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdbool.h>
#include <project.h>

struct params_t {
  bool variable;
  unsigned int amount;
  // list
  typNodeType * params;
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

void process_tree(nodeType * root, bool * success);

#endif