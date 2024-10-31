#define NULL_ADDRESS -1

void map_symbol(int line_count, char *symbol);
void map_var(char *symbol);
int address(char *symbol);
void free_store();

void increase_address_count();
int available_address(char *symbol);

