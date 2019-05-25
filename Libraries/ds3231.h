#include <avr/io.h>
#define SIZE 16





enum registers{
	SecondsReg,MinutesReg,HoursReg,WeekDaysReg,DaysReg,MonthsReg,
	YearsReg,SecondAlarmReg,MinuteAlarm1Reg,HourAlarm1Reg,DateAlarm1Reg,
	MinuteAlarm2Reg,HourAlarm2Reg,DateAlarm2Reg,CtrReg1,CtrReg2,OffsetReg,TmpLsbReg,TmpMsbReg
};


enum Days{
	Monday = 1,Tuesday,Wednesday,Thursdaym,Friday,Saturday,Sunday
};

enum Months{
	January = 1,February,March,April,May,June,July,August,September,October,November,December
};


typedef struct{
	uint8_t Day;
	uint8_t WeekDay;
	uint8_t Month;
	uint8_t Year;
} Date;

typedef struct{
	uint8_t Second;
	uint8_t Hour;
	uint8_t Minute;
} Time;



char buf[SIZE];
Time time;
Date date;




void ds3231_WriteRegister(uint8_t,uint8_t);	//zapis do rejestru układu
uint8_t ds3231_ReadRegister(uint8_t);

void ds3231_SetTime(Time*);
void ds3231_GetTime(Time*);

void ds3231_SetDate(Date*);
void ds3231_GetDate(Date*);

uint8_t bcd2dec(uint8_t);
uint8_t dec2bcd(uint8_t);

void showTime(Time*,char*);
void showDate(Date*, char*);
