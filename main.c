#include "menu.h"
#include "screen.h"

int main()
{
	init_menu();

	while(1)
	{
		int key = get_char();
		if(key == 1) navigate_up();
		else if(key == 2) navigate_down();
		else if(key == 3) navigate_forward();
		else if(key == 4) navigate_back();
	}
	
	destroy_menu();
	return 0;
}