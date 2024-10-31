#define NULL_ADDRESS -1

void map_symbol(char *label, int line_count);
void map_var(char *label);
int address(char *label);
void free_store();

