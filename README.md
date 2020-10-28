# BipStatusbarLibrary
BipStatusbarLibrary for BipOS
## Usage
- Copy library files to your project
- Add #include "BipStatusbarLib.h" in include section in main.c your project
- Add in void screen_job()

	show_statusbar(3, COLOR_BLACK,COLOR_WHITE);  

- change in  void screen_job() set_update_period to:(for better battery life) 

	set_update_period(1, 60000); 

- Add in void draw_screen:

	show_statusbar(3, COLOR_BLACK,COLOR_WHITE); 

- Enjoy 
## Config
show_statusbar(3, COLOR_BLACK,COLOR_WHITE) - COLOR_BLACK - Background color  COLOR_WHITE - font color. You can change it as you wish.
You can config  library in BipStatusbarLib.c - just comment unneeded function #define
Example:
- define BATTERY_TEXT
- define BATTERY_ICON
- //define TIME
- define DATA
- define BLUETOOTH

Commit TIME - disable time in statusbar