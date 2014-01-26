#include <stdbool.h>

typedef struct data_node
{
	char* value;
	bool writable;

} data_node_t;

typedef struct menu_node
{
	const char* display_name;
	data_node_t* data_node;
	struct menu_node* parent;
	struct menu_node* children[10];
	int children_index;

} menu_node_t;

void init_menu();
void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent);
void add_child(menu_node_t* node, menu_node_t* child);
void draw_menu();
void destroy_menu();