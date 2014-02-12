#include "menu.h"
#include "menu_p.h"
#include "screen.h"
#include <string.h>
#include <stdlib.h>

menu_node_t* root;
menu_node_t* current_node;
menu_node_t* selected_node;
menu_node_t menu_nodes[20];
data_node_t data_nodes[20];

char line1_text[DISPLAY_COLS + 1]; // plus 1 for null char
char line2_text[DISPLAY_COLS + 1];

void init_menu()
{
	int node_array_index = 0;
	int data_array_index = 0;

	// Create data nodes
	data_node_t* data = &(data_nodes[data_array_index++]);
	data->value = "3.21";
	data->writable = true;

	root = &(menu_nodes[node_array_index++]);
	init_menu_node(root, "Main Menu", 0, 0);

	menu_node_t* temperature = &(menu_nodes[node_array_index++]);
	init_menu_node(temperature, "Temperature", 0, root);
	add_child(root, temperature);

	menu_node_t* tc1 = &(menu_nodes[node_array_index++]);
	init_menu_node(tc1, "TC1", data, temperature);
	add_child(temperature, tc1);

	menu_node_t* tc2 = &(menu_nodes[node_array_index++]);
	init_menu_node(tc2, "TC2", 0, temperature);
	add_child(temperature, tc2);

	menu_node_t* temp = &(menu_nodes[node_array_index++]);
	init_menu_node(temp, "Water Slip", 0, root);
	add_child(root, temp);

	temp = &(menu_nodes[node_array_index++]);
	init_menu_node(temp, "Network", 0, root);
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
	/* Line1 displays the name of the current menu. */
	strncpy(line1_text, current_node->display_name, DISPLAY_COLS);
	line1_text[DISPLAY_COLS + 1] = '\0';
}

void update_line2()
{
	/* Line2 displays the name of the currently selected child, plus
	 * its value if it is a parameter.
	 */ 
 	strncpy(line2_text, selected_node->display_name, DISPLAY_COLS);
 	if(selected_node->data_node)
 	{
 		int num_spaces = DISPLAY_COLS - strlen(line2_text) 
 				- strlen(selected_node->data_node->value);

		for(int i = 0; i < num_spaces; ++i)
		{
			strcat(line2_text, " ");
		}
		//sprintf(num, "%d", num_spaces);
		strcat(line2_text, selected_node->data_node->value);
	}

	line1_text[DISPLAY_COLS + 1] = '\0';
}

void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent)
{
	strcpy(node->display_name, name);
	//node->display_name = name;

	node->data_node = data;
	node->parent = parent;
	node->selected_child_index = 0;
	node->num_children = 0;
}

int add_child(menu_node_t* node, menu_node_t* child) 
{
	if(node->num_children == MAX_CHILDREN) return -1;

	node->children[node->num_children] = child;
	node->num_children++;
	
	return 0;
}

void done_adding_children(menu_node_t* node)
{
	// int destination_index = 0;
	// for(int i = 0; i < node->last_child_index; ++i)
	// {
	// 	strncpy(&(node->children_text[destination_index]),
	// 		node->children[i]->display_name, 
	// 		strlen(node->children[i]->display_name));

	// 	destination_index += strlen(node->children[i]->display_name);
	// 	node->children_text[destination_index++] = ' ';
	// }
	// node->children[destination_index] = '\0';
}

void draw_menu()
{
	update_line1();
	update_line2();

	write_line(1, line1_text, -1, -1);
	//write_line(2, selected_node->display_name, -1, -1);
	write_line(2, line2_text, -1, -1);

}

void destroy_menu()
{
	destroy_screen();
}

void navigate_up()
{
	if(current_node->selected_child_index > 0)
	{
		current_node->selected_child_index--;
		selected_node = current_node->children[current_node->selected_child_index];
	}
	draw_menu();
}

void navigate_down()
{
	if(current_node->selected_child_index < current_node->num_children - 1)
	{
		current_node->selected_child_index++;
		selected_node = current_node->children[current_node->selected_child_index];
	}
	draw_menu();
}

void navigate_forward()
{
	if(selected_node->num_children != 0)
	{
		selected_node->selected_child_index = 0;
		current_node = selected_node;
		selected_node = selected_node->children[0];
	}
	draw_menu();
}

void navigate_back()
{
	if(current_node->parent)
	{
		current_node = current_node->parent;
		selected_node = current_node->children[current_node->selected_child_index];	
	}
	draw_menu();
}