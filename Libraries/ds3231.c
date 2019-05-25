
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ds3231.h"
#include "i2c.h"
#include "hd44780.h"
#include <stdlib.h>
#include <stdio.h>

#define DS3231_ADDR 0xD0


static const char *weekDays[] = {
		"No", "Mon","Tue","Wed","Thur","Fri","Sat","Sun"
};

void ds3231_WriteRegister(uint8_t reg,uint8_t val){
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(val);
	i2cStop();
}


uint8_t ds3231_ReadRegister(uint8_t reg){
	uint8_t data;
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(reg);
	i2cStartSelect(DS3231_ADDR | TW_READ);
	data = i2cReceiveData_NACK();
	i2cStop();
	return data;
}


void ds3231_SetTime(Time *time){
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(SecondsReg);
	i2cSendByte(time->Second);
	i2cSendByte(time->Minute);
	i2cSendByte(time->Hour);
	i2cStop();
}

void ds3231_GetTime(Time *time){
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(SecondsReg);
	i2cStartSelect(DS3231_ADDR | TW_READ);
	time->Second = i2cReceiveData_ACK() & 0x7f;
	time->Minute = i2cReceiveData_ACK() & 0x7f;
	time->Hour = i2cReceiveData_NACK() & 0x3F;
	i2cStop();
}

void ds3231_SetDate(Date *date){
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(WeekDaysReg);
	i2cSendByte(date->WeekDay);
	i2cSendByte(date->Day);
	i2cSendByte(date->Month);
	i2cSendByte(date->Year);
	i2cStop();
}

void ds3231_GetDate(Date *date){
	i2cStartSelect(DS3231_ADDR | TW_WRITE);
	i2cSendByte(WeekDaysReg);
	i2cStartSelect(DS3231_ADDR | TW_READ);
	date->WeekDay = i2cReceiveData_ACK() & 0x7;
	date->Day = i2cReceiveData_ACK() & 0x3f;
	date->Month = i2cReceiveData_ACK() & 0x1F;
	date->Year = i2cReceiveData_NACK();
	i2cStop();
}


uint8_t bcd2dec(uint8_t bcd){
	return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
}

uint8_t dec2bcd(uint8_t dec){
	return ((dec / 10)<<4) | (dec % 10);
}


void showTime(Time *time, char *buf){
			LCD_Home();
			ds3231_GetTime(time);
			utoa(bcd2dec(time->Hour),buf,10);
			if (time->Hour <= 9 ) LCD_WriteData('0');
			LCD_WriteText(buf);
			LCD_WriteData(':');
			utoa(bcd2dec(time->Minute),buf,10);
			if (time->Minute <= 9 ) LCD_WriteData('0');
			LCD_WriteText(buf);
			LCD_WriteData(':');
			utoa(bcd2dec(time->Second),buf,10);
			if (time->Second <= 9 ) LCD_WriteData('0');
			LCD_WriteText(buf);
}

void showDate(Date *date, char *buf){
			LCD_GoTo(0,1);
			ds3231_GetDate(date);
			utoa(bcd2dec(date->Day),buf,10);
			if (date->Day <= 9) LCD_WriteData('0');
			LCD_WriteText(buf);
			LCD_WriteData('/');
			utoa(bcd2dec(date->Month),buf,10);
			if (date->Month <= 9) LCD_WriteData('0');
			LCD_WriteText(buf);
			LCD_WriteData('/');
			utoa(bcd2dec(date->Year),buf,10);
			LCD_WriteText(buf);
			LCD_WriteData(' ');
			LCD_WriteText(weekDays[date->WeekDay]);
}
