#include "menu.h"
#include "menu_p.h"
#include "screen.h"

menu_node_t* root;
menu_node_t* current_node;
menu_node_t menu_nodes[20];

void init_menu()
{
	int node_array_index = 0;
	root = &(menu_nodes[node_array_index++]);
	init_menu_node(root, "Main Menu", 0, 0);

	menu_node_t* temp = &(menu_nodes[node_array_index++]);
	init_menu_node(temp, "Temperature", 0, root);
	add_child(root, temp);

	temp = &(menu_nodes[node_array_index++]);
	init_menu_node(temp, "Water slip", 0, root);
	add_child(root, temp);

	current_node = root;

	init_screen();
	draw_menu();
}

void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent)
{
	node->display_name = name;
	node->data_node = data;
	node->parent = parent;
	node->children_index = 0;
}

void add_child(menu_node_t* node, menu_node_t* child) 
{
	node->children[node->children_index++] = child;
}

void draw_menu()
{
	write_line(1, current_node->display_name, -1, -1);
	write_line(2, current_node->children[0]->display_name, -1, -1);
}

void destroy_menu()
{
	destroy_screen();
}

