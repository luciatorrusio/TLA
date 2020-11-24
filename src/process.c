#include <stdio.h>
#include <errno.h>
#include <process.h>
#include <project.h>

FILE * fp = NULL;

static void pyhead(const char * headToWrite) {
	// TODO: Write at the beggining of file
	fputs(headToWrite, fp);
}

static void pybody(const char * bodyToWrite) {
	fputs(bodyToWrite, fp);
}

static void prefixPrint(nodeType * t, int depth) {
	if (t == NULL) {
		return;
	}

	char indent[200] = {0};

	unsigned int j;
	
	for (j = 0; j < depth; j++) {
		indent[j] = '\t';
	}

	indent[j] = '\0';

	printf("%snode type: %d\n", indent, t->type);

	switch(t->type) {
		case typeOpr: 
			printf("%soper: %d\n", indent, t->opr.oper);
			printf("%snops: %d\n", indent, t->opr.nops);
			for (unsigned int i = 0; i < t->opr.nops; i++) {
				prefixPrint(t->opr.op[i], depth+1);
			}
			break;
		case typeCon: 
			printf("%sintConst: %d\n", indent, t->con.value);
			break;
		case typeStr: 
			printf("%sstring: %s\n", indent, t->str.s);
			break;
		case typeId: 
			printf("%sid: %d\n", indent, t->ide.i);
			break;
		case typeTyp: 
			printf("%stype: %d\n", indent, t->typ.t);
			break;
	}
}

static void checkLibraries(nodeType * t){
  
}

static void checkTypes(nodeType * t, bool * checked){
  
}

static void translateToPython(nodeType * t){
  
}

void processTree(nodeType * root, bool * success) {
	
	prefixPrint(root, 0);

	bool checked = true;

	checkTypes(root, &checked);
	checkLibraries(root);

	if (!checked) {
		*success = false;
		printf("Type Conflict\n");
		return;
	}

	fp = fopen("translated.py", "w");
	
	if (fp == NULL) {
			perror("fopen");
	}

	translateToPython(root);

  if (fclose(fp) < 0) {
    perror("fclose");
  }
}