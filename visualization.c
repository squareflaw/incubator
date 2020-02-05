#include <xc.h>
#include "lcd.h"
#include "sensor_temp_humidity_dht.h"
#include "visualization.h"

char Menu_selection_1[] 			= " Incubadora    ";
char Menu_selection_2[]				= " Config fecha  ";

char Incubator_selection_line_1[]	= "> Huevos de    ";
char Incubator_selection_line_2[]  	= "   Gallina     ";

char Incubator_interface_line_1[]	= "  Incubating   ";
char Incubator_interface_line_2[]	= "     days left";

char Incubator_interface_cancel_confirmation_line_1[]	= "  �cancelar?   ";
char Incubator_interface_cancel_confirmation_line_2[]  	= "  OK     Atras ";


char DateTime_str[]    				= "  /  /     :   ";

char Temperature_str[]      		= "Temp = 00.0 C  ";
char Humidity_str[]        	 		= "RH   = 00.0 %  ";



void display_menu(char selector){
	if (selector == 0)
	{
		Menu_selection_1[0] = '>';
		Menu_selection_2[0] = ' ';
	}
	if (selector == 1)
	{
		Menu_selection_1[0] = ' ';
		Menu_selection_2[0] = '>';
	}
	LCD_out(1,0, Menu_selection_1);
	LCD_out(2,0, Menu_selection_2);

}

void display_interface(AmbientVariables av, DateTime datetime){
	format_temp_and_RH(av);
	format_datetime(datetime);
	LCD_out(1,0,Temperature_str);
    LCD_out(2,0,DateTime_str);
}

void display_incubator_selection(){
	LCD_out(1,0,Incubator_selection_line_1);
    LCD_out(2,0,Incubator_selection_line_2);
}

void display_incubator_interface(char days){

	Incubator_interface_line_2[2] = (days / 10) % 10  + '0';
	Incubator_interface_line_2[3] = (days % 10) + '0';

	LCD_out(1,0,Incubator_interface_line_1);
    LCD_out(2,0,Incubator_interface_line_2);
}

void display_incubator_canceling_confirmation(){
	LCD_out(1,0,Incubator_interface_cancel_confirmation_line_1);
    LCD_out(2,0,Incubator_interface_cancel_confirmation_line_2);
}

void display_datetime_setting(DateTime datetime, char position){
	char selector_str[]    	= "               ";
	selector_str[position] = '^';
	format_datetime(datetime);
	LCD_out(1,0,DateTime_str);
	LCD_out(2,0,selector_str);
}

void format_temp_and_RH(AmbientVariables av){
	if (av.temperature > 0X8000)
	{                         // if temperature < 0
	  Temperature_str[6] = '-';   // put minus sign '-'
	  av.temperature = av.temperature & 0X7FFF;
	}else {
	  Temperature_str[6] = ' ';  // put space ' '
	  Temperature_str[7]  = (av.temperature / 100) % 10  + '0';
	  Temperature_str[8]  = (av.temperature / 10) % 10   + '0';
	  Temperature_str[10] =  av.temperature % 10  + '0';
	  Temperature_str[11] = 223;    // put degree symbol (°)
	}

	if(av.relative_humidity == 1000) {
	  Humidity_str[6]  = 1 + '0';   // put 1 of hundreds
	}else {
	  Humidity_str[6]  = ' ';       // put space ' '
	  Humidity_str[7]  = (av.relative_humidity / 100) % 10 + '0';
	  Humidity_str[8]  = (av.relative_humidity / 10) % 10  + '0';
	  Humidity_str[10] = av.relative_humidity % 10 + '0';
	}
}

void format_datetime(DateTime datetime){
	//day
	DateTime_str[0] = (datetime.date / 10) % 10  + '0';
	DateTime_str[1] = (datetime.date % 10) + '0';

	//month
	DateTime_str[3] = (datetime.month / 10) % 10  + '0';
	DateTime_str[4] = (datetime.month % 10) + '0';

	//year
	DateTime_str[6] = (datetime.year / 10) % 10  + '0';
	DateTime_str[7] = (datetime.year % 10) + '0';

	//hours
	DateTime_str[9] = (datetime.hours / 10) % 10  + '0';
	DateTime_str[10] = (datetime.hours % 10) + '0';

	//minutes
	DateTime_str[12] = (datetime.minutes / 10) % 10  + '0';
	DateTime_str[13] = (datetime.minutes % 10) + '0';
}


