#include <stdbool.h>

#define MAX_CHILDREN 10
#define DISPLAY_COLS 20
#define MAX_NAME_LEN 20

typedef struct data_node
{
	char* value;
	bool writable;

} data_node_t;

typedef struct menu_node
{
	char display_name[MAX_NAME_LEN];
	data_node_t* data_node;
	struct menu_node* parent;
	struct menu_node* children[MAX_CHILDREN];
	int selected_child_index;
	int num_children;
} menu_node_t;

void init_menu();
void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent);
int add_child(menu_node_t* node, menu_node_t* child);
void done_adding_children(menu_node_t* node);
void draw_menu();
void destroy_menu();
void update_line1();
void update_line2();