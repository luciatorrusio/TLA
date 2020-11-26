#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdbool.h>
#include <project.h>

struct params_t {
  unsigned int amount;
  // list
  typNodeType * params;
};

struct function_info {
  typNodeType ret;
  
  identifierT id;

  struct params_t params;
};

void process_tree(nodeType * root, bool * success);

#endif