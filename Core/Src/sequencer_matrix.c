/*
 * sequencer_matrix.c
 *
 *  Created on: Mar 2, 2021
 *      Author: Célia Jaffré
 */

#include "main.h"

extern uint8_t table[64];


I2C_HandleTypeDef hi2c1;
uint8_t I2CMasterBuffer[I2C_BUFSIZE];
static uint8_t blackBoard[I2C_BUFSIZE];
uint8_t tune[I2C_BUFSIZE];
uint8_t way[I2C_BUFSIZE];

char scale[] = "mm";
static char ga1[] = "ma";
static char ga2[] = "mm";
static char ga3[] = "mh";
static char ga4[] = "bl";
static char a[] = "A";
static char b[] = "B";
static char c[] = "C";
static char d[] = "D";
static char e[] = "E";
static char f[] = "F";
static char g[] = "G";
char tonic[] = "A";


void LED_Matrix_Init()
{
	printf("\r\n=== LED MATRIX ===\r\n");
	printf("SCL sur D5 et SDA sur D4\r\n");

	I2CMasterBuffer[0] = 0x21;		// Turn on internal oscillator
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);

	I2CMasterBuffer[0] = 0x81;		// Display on, blinking off
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
	I2CMasterBuffer[0] = 0xEA;		// Dimming duty a donf!
	HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
	for (int i = 0 ; i < 17 ; i++)
	{
		I2CMasterBuffer[i] = 0;
	}
	for (int i = 0 ; i < 17 ; i++)
	{
		blackBoard[i] = 0;
	}
}

void Display(float dir, int seq, int flat, int sharp)
{
	int charging = 0;
	//All 12 sequences complete
	for (int i = 1 ; i < 17 ; i++) {
					way[i] = 0;
			}
	while (seq == 12){
				way[5]=(1<<3)+(1<<4);
				way[7]=(1<<2)+(1<<3);
				way[9]=(1<<3)+(1<<4);
				way[11]=(1<<4)+(1<<5);
				way[13]=(1<<5)+(1<<6);
				HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}

	//Choix tonique
	while(seq == 0){

		for (int i = 1 ; i < 17 ; i++) {
				tune[i] = 0;
		}
		if (strcmp(tonic,a)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			tune[4]=(1<<2)+(1<<5);
			tune[6]=(1<<2)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			//printf("\r\n===%d===\r\n",tune[2]);
		}
		else if (strcmp(tonic,b)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<3)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<4)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3);
		}
		else if (strcmp(tonic,c)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<5);
			tune[8]=(1<<1)+(1<<5);
		}
		else if (strcmp(tonic,d)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<5);
			tune[8]=(1<<2)+(1<<3)+(1<<4);
		}
		else if (strcmp(tonic,e)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<3)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<5);
			tune[8]=(1<<1)+(1<<5);
		}
		else if (strcmp(tonic,f)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<3)+(1<<5);
			tune[6]=(1<<3)+(1<<5);
			tune[8]=(1<<5);
		}
		else if (strcmp(tonic,g)==0){
			tune[2]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[4]=(1<<1)+(1<<5);
			tune[6]=(1<<1)+(1<<3)+(1<<5);
			tune[8]=(1<<1)+(1<<2)+(1<<3)+(1<<5);
		}
		else{
			tune[2]=0;
			tune[4]=0;
			tune[6]=0;
			tune[8]=0;
		}

		if (sharp){
			tune[12]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			tune[14]=(1<<2)+(1<<4);
			tune[16]=(1<<1)+(1<<2)+(1<<3)+(1<<4)+(1<<5);
			//printf("\r\n===%d===\r\n",tune[14]);
		}
		else if (flat){
			tune[12]=(1<<1)+(1<<2)+(1<<3)+(1<<4);
			tune[14]=(1<<1)+(1<<2);
			tune[16]=0;
		}
		else{
			tune[12]=0;
			tune[14]=0;
			tune[16]=0;
		}
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, tune, 17, HAL_MAX_DELAY);
		//printf("\r\n===printed===\r\n");
		//printf("\r\n===%d===\r\n",tune[14]);

	}

	//Directions
	for (int i = 1 ; i < 17 ; i++) {
		way[i] = 0;
	}

	while (dir>0){
		//fleche verte
		way[7]=(1<<6)+(1<<2);
		way[9]=(1<<5)+(1<<3);
		way[11]=(1<<4);
		//fleche rouge
		way[6]=(1<<6)+(1<<2);
		way[8]=(1<<5)+(1<<3);
		way[10]=(1<<4);
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}
	while (dir<0){
		//fleche verte
		way[9]=(1<<6)+(1<<2);
		way[7]=(1<<5)+(1<<3);
		way[5]=(1<<4);
		//fleche rouge
		way[12]=(1<<6)+(1<<2);
		way[10]=(1<<5)+(1<<3);
		way[8]=(1<<4);
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, way, 17, HAL_MAX_DELAY);
	}


	for (int i = 1 ; i < 17 ; i++) {
		way[i] = 0;
	}

	//Chargement

	int k = 0;
	while (charging) {
		for (int j = 1; j < 17; j++) {
			I2CMasterBuffer[j] = k << (j / 2);
			I2CMasterBuffer[j + 3] = k << ((j + 1) / 2);
			//printf("\r\n===charge===\r\n");
		}
		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		if (k == 0x80) {
			k = 1;
		}
		else {
			k <<= 1;
			HAL_Delay(100);
		}
	}
	printf("\r\n===no charging anymore===\r\n");
	//gamme
	while (dir == 0){
		if (strcmp(scale,ga1)==0){ //majeur
			for (int j = 1; j < 17; j+=2)
			{
				if ((table[j/2+1]==3)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
			//printf("\r\n===Fck===\r\n");
		}
		else if (strcmp(scale,ga2)==0){ //mineur mélodique
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		else if (strcmp(scale,ga3)==0){ //mineur harmonique
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==5)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else if(table[j/2+1]==6){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		else if (strcmp(scale,ga4)==0){ //blues
			for (int j = 1; j < 17; j+=2) {
				if ((table[j/2+1]==2)|(table[j/2+1]==6)|(table[j/2+1]==8)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
				}
				else if((table[j/2+1]==1)|(table[j/2+1]==5)|(table[j/2+1]==7)){
					I2CMasterBuffer[j] = 1<<(table[j/2+1]-1);
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
				else{
					I2CMasterBuffer[j+1] = 1<<(table[j/2+1]-1);
				}
			}
			HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, I2CMasterBuffer, 17, HAL_MAX_DELAY);
		}
		//else {
			//HAL_I2C_Master_Transmit (&hi2c1, HT16K33_I2C_ADDRESS, blackBoard, 17, HAL_MAX_DELAY);
		//}
	}

}

