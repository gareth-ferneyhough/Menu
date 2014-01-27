#include "menu.h"
#include "menu_p.h"
#include "screen.h"
#include <string.h>

menu_node_t* root;
menu_node_t* current_node;
menu_node_t* selected_node;
menu_node_t menu_nodes[20];

char line1_text[DISPLAY_COLS + 1]; // plus 1 for null char
char line2_text[DISPLAY_COLS + 1];

int selected_node_name_index;
int selected_node_name_end;

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

	done_adding_children(root);
	current_node = root;
	selected_node = root->children[0];

	update_line1();
	update_line2();

	init_screen();
	draw_menu();
}

void update_line1()
{
	strncpy(line1_text, root->display_name, DISPLAY_COLS);
	line1_text[DISPLAY_COLS + 1] = '\0';
}

void update_line2()
{
	if(strlen(root->children_text) > DISPLAY_COLS)
	{
		strncpy(line2_text, root->children_text, DISPLAY_COLS - 3);
		line2_text[DISPLAY_COLS - 3] = ' ' ;
		line2_text[DISPLAY_COLS - 2] = '.' ;
		line2_text[DISPLAY_COLS - 1] = '.' ;
	}
	else
	{	
		strncpy(line2_text, root->children_text, DISPLAY_COLS);
	}
	line2_text[DISPLAY_COLS + 1] = '\0';
}

void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent)
{
	node->display_name = name;
	node->data_node = data;
	node->parent = parent;
	node->selected_child_index = 0;
	node->last_child_index = 0;
}

int add_child(menu_node_t* node, menu_node_t* child) 
{
	if(node->last_child_index == MAX_CHILDREN -1) return -1;
	node->children[node->last_child_index++] = child;
	return 0;
}

void done_adding_children(menu_node_t* node)
{
	int destination_index = 0;
	for(int i = 0; i < node->last_child_index; ++i)
	{
		strncpy(&(node->children_text[destination_index]),
			node->children[i]->display_name, 
			strlen(node->children[i]->display_name));

		destination_index += strlen(node->children[i]->display_name);
		node->children_text[destination_index++] = ' ';
	}
	node->children[destination_index] = '\0';
}

void draw_menu()
{
	//line1_text = current_node->display_name;
	write_line(1, line1_text, -1, -1);

	//line2_text = selected_node->display_name;
	//const char* selected_node_display_name = ;
	//unsigned int name_length = strlen(selected_node_display_name);
	write_line(2, line2_text, -1, -1);

}

void destroy_menu()
{
	destroy_screen();
}

void navigate_next()
{
	// if(current_node->data == 0) // we are at a menu node
	// {
	// 	// if possible, move cursor to next node
	// 	if(current_node->selected_child < current_node->num_children)
	// 	{
	// 		current_node->selected_child++;
	// 	}
	// 	selected_node = current_node->selected_child;

	// 	// do we need to scroll the screen right?
	// 	// is selected_node name fully contained in line2?
	// 	if(strstr(line2_text, selected_node->display_name) == 0)
	// 	{
			// need to recreate line2, starting with selected_node name
			// int line2_index = 0;
			// int child_index = current_node->selected_child;
			// do
			// {
			// 	int child_length = strlen(current_node->children[child_index]);
			// 	int remaining_chars = DISPLAY_COLS - line2_index - 3;
			// 	strncpy(line2_text[line2_index], 
			// 		current_node->children[child_index]->display_name, 
			// 		)
			// }
			// line2_text = 
	// 	}
	// }
}

void navigate_previous()
{}

void navigate_select()
{}

void navigate_back()
{}