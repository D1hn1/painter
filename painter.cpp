#include <string>
#include <cstring>
#include <iostream>
#include "termdax-v.2.h"

#define CANVAS_TOP 2
#define CANVAS_LEFT 0
#define CANVAS_BOTTOM TRM_WINDOW_Y 
#define CANVAS_RIGHT TRM_WINDOW_X

bool QUIT = false;
bool DRAWING = false;
int cursor_x = 2;
int cursor_y = 3;
std::string info_text = "(Q)uit (C)lear (W,A,S,D)move (T)oggle drawing";

int main ()
{
	trm::Termdax root;
	root.utilities.clear();
	root.utilities.noecho();
	root.utilities.nocanon();
	root.utilities.rawterm();

	trm::TRM_RECTANGLE menu_bar;
	menu_bar.Push(0,0,TRM_WINDOW_X,1,true,' ', TRM_NULL, TRM_BG_WHITE);

	trm::TRM_TEXT menu_text;
	menu_text.Push(0,0,info_text.c_str(),TRM_BLACK,TRM_BG_WHITE);

	trm::TRM_RECTANGLE brush;
	brush.Push(2,3,1,1,true, ' ', TRM_NULL, TRM_NULL);
	root.Draw();

	while ( QUIT != true ) {

		brush.bg_color = TRM_BG_BLUE;

		switch ( root.Event() ) {

			case TRM_EVENT_RESIZE:
				root.utilities.clear();
				menu_bar.w = TRM_WINDOW_X;
				menu_text.Update();
				menu_bar.Update();

			default:
				char user_key = getchar();

				if ( DRAWING ) {
					if ( user_key == 'q' ) { QUIT = true; };
					if ( user_key == 'w' && brush.y != 0 ) { brush.y--; };
					if ( user_key == 's' && brush.y != CANVAS_BOTTOM ) { brush.y++; };
					if ( user_key == 'a' && brush.x != 0 ) { brush.x--; };
					if ( user_key == 'd' && brush.x != CANVAS_RIGHT ) { brush.x++; };
					if ( user_key == 'c' ) { root.utilities.clear(); root.Draw();};
					if ( user_key == 't' ) { if ( DRAWING ) { DRAWING = false; } else { DRAWING = true; };};
					root.utilities.cmoveto(brush.x,brush.y);
					cursor_x = brush.x;
					cursor_y = brush.y;
					brush.Update();
					menu_bar.Update();
					menu_text.Update();
					root.Draw();
				} else {
					if ( user_key == 'q' ) { QUIT = true; };
					if ( user_key == 'w' && cursor_y != 0 ) { cursor_y--; };
					if ( user_key == 's' && cursor_y != CANVAS_BOTTOM ) { cursor_y++; };
					if ( user_key == 'a' && cursor_x != 0 ) { cursor_x--; };
					if ( user_key == 'c' ) { root.utilities.clear(); root.Draw();};
					if ( user_key == 'd' && cursor_x != CANVAS_RIGHT ) { cursor_x++; };
					if ( user_key == 't' ) { if ( DRAWING ) { DRAWING = false; } else { DRAWING = true; };};
					brush.x = cursor_x;
					brush.y = cursor_y;
					root.utilities.cmoveto(cursor_x,cursor_y);
					menu_bar.Update();
					menu_text.Update();
				};
				
		};

	};

	root.utilities.clear();
	root.Endtermdax();
	return 0;
}
