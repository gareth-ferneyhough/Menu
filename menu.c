#include "menu.h"
#include "screen.h"

void init_menu()
{
	init_screen();
	write_line(1, "hello world!");
	write_line(2, "from g$");
}

void destroy_menu()
{
	destroy_screen();
}

