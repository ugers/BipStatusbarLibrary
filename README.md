# BipStatusbarLibrary
BipStatusbarLibrary for BipOS
## Usage
- Copy library files to your project
- Add [#include "BipStatusbarLib.h"] in include section in main.c your project
- Add [show_statusbar(3, COLOR_BLACK,COLOR_WHITE);] in [screen_job()] + change [set_update_period] to [set_update_period(1, 60000);] for better battery life
- Add [show_statusbar(3, COLOR_BLACK,COLOR_WHITE);] in draw_screen
- Enjoy 
## Config
show_statusbar(3, COLOR_BLACK,COLOR_WHITE) - COLOR_BLACK - Background color  COLOR_WHITE - font color. You can change it as you wish.
You can config  library in BipStatusbarLib.c - just comment unneeded function #define
Example:
	define BATTERY_TEXT
	define BATTERY_ICON
	//define TIME
	define DATA
	define BLUETOOTH
Commit TIME - disable time in statusbar