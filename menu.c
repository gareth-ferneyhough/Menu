#include "menu.h"
#include "screen.h"

void init_menu()
{
	init_screen();
	write_line(1, "hello world!", 0, 3);
	write_line(2, "from g$", 5, 6);
}

void destroy_menu()
{
	destroy_screen();
}

