/*
	BipStatusbarLibrary for Amazfit Bip BipOS

	(C) ugers 2020
	
	Библиотека статусбар для BipOS
	
*/
#include "BipStatusbarLib.h"
//#define BipEmulator
#ifdef BipEmulator
	#include "libbip.h"
#else
	#include <libbip.h>
#endif

//ОПЦИИ
#define BATTERY_TEXT
#define BATTERY_ICON
#define TIME
#define DATA
#define BLUETOOTH
// Выберите 1 из трех ALARM
#define ALARM_RING
//#define ALARM_CLOCK
//#define ALARM_CLOCK_RING

void show_statusbar(int y, int bgColor,int fgColor){
	set_bg_color(bgColor); // делаем фон
	set_fg_color(fgColor); // делаем фон
	draw_filled_rect_bg(0, 0, 176, y + 20);

	//БАТАРЕЯ
	#ifdef BATTERY_ICON
	set_bg_color(COLOR_BLACK); // делаем фон
	draw_filled_rect_bg(152, y, 172, y + 16); // сама батарейка
	draw_filled_rect_bg(170, y + 4, 174, y + 12); //кончик
	set_bg_color(COLOR_WHITE); // делаем фон
	draw_filled_rect_bg(153, y + 1, 171, y + 15); // сама батарейка
	draw_filled_rect_bg(171, y + 5, 173, y + 11); //кончик
	#endif
		if (get_fw_version() != 11536)
		{
			//set_bg_color(COLOR_YELLOW);
			//draw_filled_rect_bg(x + 2, y + 2, x + 21, y + 10);
		}else{
	#ifdef BipEmulator
			word battery_percentage = 100;
	#else
			word battery_percentage = *((word*)(0x20000334));
	#endif
			#ifdef BATTERY_ICON
			//Цвет индикатора батареи
			char r_count = battery_percentage / 33;
			r_count = r_count > 2 ? 2 : r_count < 1 ? 0 : r_count; // if r_count > 2 = 2 elseif r_count < 1 = 0 else r_count
				if (battery_percentage > 32) {
					set_bg_color(battery_percentage <= 65 ? COLOR_YELLOW : COLOR_GREEN);
				}else if (battery_percentage <= 32) {
					set_bg_color(COLOR_RED);
				}

				for (char i = 0; i <= r_count; i++)
				{
					draw_filled_rect_bg(155 + i * 5, y + 2, 159 + i * 5, y + 14);
				}
			#endif
			#ifdef BATTERY_TEXT
			//Проценты батареи
			char d1[4];     // переменная для перевода переменной для печати                               
			_sprintf(d1, "%01d", battery_percentage); // конвертируем
			set_bg_color(bgColor); // делаем фон
				#ifdef BATTERY_ICON
					text_out_center(d1, 138, y);
				#else
					text_out(d1, 135, y);
					text_out("%", 162, y);
				#endif
			#endif
		}
set_bg_color(bgColor); // делаем фон
#ifdef TIME
	// ВРЕМЯ
	char clock_time[8]; 			//	текст время		12:34
	struct datetime_ dt;
	get_current_date_time(&dt);
	_sprintf(clock_time, "%02d:%02d", dt.hour, dt.min);
	text_out_center(clock_time, 88,y);		// печатаем результат(время)
#endif
#ifdef DATA
	char data[12]; 			//	текст дата		день.месяц
	#ifndef TIME
		struct datetime_ dt;
		get_current_date_time(&dt);
	#endif
	_sprintf(data, "%02d.%02d", dt.day, dt.month);
	text_out(data,4,y);		// печатаем день недели
#endif
#ifdef BLUETOOTH
	// БЛЮТУЗ
	char last_bt_con;
	#ifdef BipEmulator
		last_bt_con = 0;
	#else
		last_bt_con = check_app_state(0x200);
	#endif
	if (last_bt_con){
		//paint bluetooth ON
		set_bg_color(COLOR_BLACK);
		draw_filled_rect_bg(48, y-1, 62, y+17);
		set_bg_color(COLOR_BLUE);
		draw_filled_rect_bg(49, y, 61, y+16);
		set_fg_color(COLOR_WHITE);
		text_out_center("ᛒ", 55, y);
	}else{			
		//paint bluetooth OFF
		set_bg_color(COLOR_BLACK);
		draw_filled_rect_bg(48, y-1, 62, y+17);
		set_bg_color(COLOR_RED);
		draw_filled_rect_bg(49, y, 61, y+16);
		set_fg_color(COLOR_BLACK);
		text_out_center("ᛒ", 55, y);
	}
#endif

// Будильник
#ifdef ALARM_CLOCK_RING
	set_bg_color(COLOR_BLACK);
	draw_filled_rect_bg(110, y-1, 117, y+16);
	set_bg_color(COLOR_RED);
	draw_filled_rect_bg(111, y+6, 116, y+15);
	draw_filled_rect_bg(111, y, 116, y+3);
	set_bg_color(COLOR_WHITE);
	draw_filled_rect_bg(112, y+7, 115, y+14);
	set_bg_color(COLOR_BLACK);
	draw_filled_rect_bg(114, y+7, 114, y+10);
	draw_filled_rect_bg(114, y+10, 115, y+10);
#endif
#ifdef ALARM_CLOCK
	set_bg_color(COLOR_BLACK);
	draw_filled_rect_bg(110, y-1, 117, y+16);
	set_bg_color(COLOR_RED);
	draw_filled_rect_bg(111, y, 116, y+15);
	set_bg_color(COLOR_WHITE);
	draw_filled_rect_bg(112, y+1, 115, y+14);
	set_bg_color(COLOR_BLACK);
	draw_filled_rect_bg(114, y+1, 114, y+8);
	draw_filled_rect_bg(114, y+8, 115, y+8);
#endif
#ifdef ALARM_RING
	set_bg_color(COLOR_BLACK);
	draw_filled_rect_bg(112, y-2, 115, y);
	draw_filled_rect_bg(111, y, 116, y+16);
	draw_filled_rect_bg(110, y+11, 117, y+16);
	set_bg_color(COLOR_YELLOW);
	draw_filled_rect_bg(112, y+1, 115, y+15);
	draw_filled_rect_bg(111, y+12, 116, y+15);
#endif

// РАЗДЕЛИТЕЛЬ
	set_fg_color(fgColor); // делаем фон
	draw_horizontal_line(y+19, 0, 176);
	repaint_screen_lines(0, y+19); // обновляем строки экрана
}