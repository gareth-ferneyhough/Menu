#include "menu.h"
#include "menu_p.h"
#include "screen.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

menu_node_t* root;
menu_node_t* current_node;
menu_node_t* selected_node;
menu_node_t menu_nodes[20];
data_node_t data_nodes[20];

char line1_text[DISPLAY_COLS + 1]; // plus 1 for null char
char line2_text[DISPLAY_COLS + 1];

bool data_node_selected;
int cursor_col;

void init_menu()
{
	int node_array_index = 0;
	int data_array_index = 0;
	data_node_selected = false;
	cursor_col = 1;

	// CH1 data node
	data_node_t* ch1_data = &(data_nodes[data_array_index++]);
	ch1_data->f_value = 4.0;
	ch1_data->uses_i_value = false;
	ch1_data->writable = true;
	ch1_data->increment_value = 0.1;

	// CH2 data node
	data_node_t* ch2_data = &(data_nodes[data_array_index++]);
	ch2_data->f_value = 4.0;
	ch2_data->uses_i_value = false;
	ch2_data->writable = true;
	ch2_data->increment_value = 0.1;

	// High temp data node
	data_node_t* high_temp_data = &(data_nodes[data_array_index++]);
	high_temp_data->f_value = 6.0;
	high_temp_data->uses_i_value = false;
	high_temp_data->writable = true;
	high_temp_data->increment_value = 0.1;

	// Low temp data node
	data_node_t* low_temp_data = &(data_nodes[data_array_index++]);
	low_temp_data->f_value = 0.0;
	low_temp_data->uses_i_value = false;
	low_temp_data->writable = true;
	low_temp_data->increment_value = 0.1;

	// Water Slip CH1 Dry
	data_node_t* c1_dry_data = &(data_nodes[data_array_index++]);
	c1_dry_data->f_value = 1.2;
	c1_dry_data->uses_i_value = false;
	c1_dry_data->writable = true;
	c1_dry_data->increment_value = 0.01;

	// Water Slip CH1 Wet
	data_node_t* c1_wet_data = &(data_nodes[data_array_index++]);
	c1_wet_data->f_value = 1.4;
	c1_wet_data->uses_i_value = false;
	c1_wet_data->writable = true;
	c1_wet_data->increment_value = 0.01;

	// Water Slip CH2 Dry
	data_node_t* c2_dry_data = &(data_nodes[data_array_index++]);
	c2_dry_data->f_value = 1.2;
	c2_dry_data->uses_i_value = false;
	c2_dry_data->writable = true;
	c2_dry_data->increment_value = 0.01;

	// Water Slip CH2 Wet
	data_node_t* c2_wet_data = &(data_nodes[data_array_index++]);
	c2_wet_data->f_value = 1.4;
	c2_wet_data->uses_i_value = false;
	c2_wet_data->writable = true;
	c2_wet_data->increment_value = 0.01;

	// Root Menu
	root = &(menu_nodes[node_array_index++]);
	init_menu_node(root, "Main Menu", 0, 0);

	// Temperature Nodes
	menu_node_t* temperature = &(menu_nodes[node_array_index++]);
	init_menu_node(temperature, "Temperature", 0, root);
	add_child(root, temperature);

	menu_node_t* tc1 = &(menu_nodes[node_array_index++]);
	init_menu_node(tc1, "CH1 Setpoint", ch1_data, temperature);
	add_child(temperature, tc1);

	menu_node_t* tc2 = &(menu_nodes[node_array_index++]);
	init_menu_node(tc2, "CH2 Setpoint", ch2_data, temperature);
	add_child(temperature, tc2);

	menu_node_t* high_temp = &(menu_nodes[node_array_index++]);
	init_menu_node(high_temp, "High Temp Alarm", high_temp_data, temperature);
	add_child(temperature, high_temp);

	menu_node_t* low_temp = &(menu_nodes[node_array_index++]);
	init_menu_node(low_temp, "Low Temp Alarm", low_temp_data, temperature);
	add_child(temperature, low_temp);

	// Water Slip Nodes
	menu_node_t* waterslip = &(menu_nodes[node_array_index++]);
	init_menu_node(waterslip, "Water Slip", 0, root);
	add_child(root, waterslip);

	menu_node_t* ch1wet = &(menu_nodes[node_array_index++]);
	init_menu_node(ch1wet, "CH1 Wet", c1_wet_data, waterslip);
	add_child(waterslip, ch1wet);

	menu_node_t* ch1dry = &(menu_nodes[node_array_index++]);
	init_menu_node(ch1dry, "CH1 Dry", c1_dry_data, waterslip);
	add_child(waterslip, ch1dry);

	menu_node_t* ch2wet = &(menu_nodes[node_array_index++]);
	init_menu_node(ch2wet, "CH2 Wet", c2_wet_data, waterslip);
	add_child(waterslip, ch2wet);

	menu_node_t* ch2dry = &(menu_nodes[node_array_index++]);
	init_menu_node(ch2dry, "CH2 Dry", c2_dry_data, waterslip);
	add_child(waterslip, ch2dry);


	// Network Nodes
	menu_node_t* temp = &(menu_nodes[node_array_index++]);
	init_menu_node(temp, "Network", 0, root);
	add_child(root, temp);

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
 		char parameter_string[20];
 		if(selected_node->data_node->uses_i_value)
 		{
 			sprintf(parameter_string, "%d", selected_node->data_node->i_value);
 		}
 		else
 		{
 			sprintf(parameter_string, "%.02f", selected_node->data_node->f_value);
 		} 		

 		int num_spaces = DISPLAY_COLS - strlen(line2_text) 
 				- strlen(parameter_string);

 		cursor_col = DISPLAY_COLS - strlen(parameter_string) + 1;

		for(int i = 0; i < num_spaces; ++i)
		{
			strcat(line2_text, " ");
		}
		strcat(line2_text, parameter_string);
	}

	line1_text[DISPLAY_COLS + 1] = '\0';
}

void init_menu_node(menu_node_t* node, const char* name, data_node_t* data, menu_node_t* parent)
{
	strcpy(node->display_name, name);

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

void increment_data_node()
{
	if(selected_node->data_node->uses_i_value)
	{
		selected_node->data_node->i_value += 
			selected_node->data_node->increment_value;
	}
	else
	{
		selected_node->data_node->f_value += 
			selected_node->data_node->increment_value;
	} 
}

void decrement_data_node()
{
	if(selected_node->data_node->uses_i_value)
	{
		selected_node->data_node->i_value -= 
			selected_node->data_node->increment_value;
	}
	else
	{
		selected_node->data_node->f_value -= 
			selected_node->data_node->increment_value;
	} 
}

void draw_menu()
{
	update_line1();
	update_line2();

	if(data_node_selected)
	{
	 	set_cursor_position(2, cursor_col);
	}
	else
	{
		set_cursor_position(2, 1);			
	}

	write_line(1, line1_text);
	write_line(2, line2_text);
}

void destroy_menu()
{
	destroy_screen();
}

void navigate_up()
{
	if(data_node_selected)
	{
		increment_data_node();
	}

	else if(current_node->selected_child_index > 0)
	{
		current_node->selected_child_index--;
		selected_node = current_node->children[current_node->selected_child_index];
	}
	draw_menu();
}

void navigate_down()
{
	if(data_node_selected)
	{
		decrement_data_node();
	}

	else if(current_node->selected_child_index < current_node->num_children - 1)
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

	else if(selected_node->data_node && 
		selected_node->data_node->writable)
	{
		data_node_selected = true;
	}

	draw_menu();
}

void navigate_back()
{
	if(data_node_selected)
	{
		data_node_selected = false;
	}
	else if(current_node->parent)
	{
		current_node = current_node->parent;
		selected_node = current_node->children[current_node->selected_child_index];	
	}
	draw_menu();
}