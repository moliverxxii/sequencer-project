/*
 * seq_def.c
 *
 *  Created on: 23 mars 2021
 *      Author: Baba
 */
#include "main.h"

extern I2C_HandleTypeDef hi2c1;
/*
void seq_disp_step(seq_TypeDef* sequence, seq_parametres_TypeDef* p){
	for (int i = 0 ; i < 17 ; i++) {
		sequence->leds[i] = 0;
	  }
	if (p->mode == mode_maj){ //majeur
		for (int j = 1; j < 17; j+=2){

			if ((sequence->notes[j/2+1]==2)|(sequence->notes[j/2+1]==6)){
				sequence->leds[j] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else{
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}
		}
		HAL_I2C_Master_Transmit (&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
	}
	else if (p->mode == mode_min){ //mineur mélodique
		for (int j = 1; j < 17; j+=2) {

			if ((sequence->notes[j/2+1]==1)|(sequence->notes[j/2+1]==6)){
				sequence->leds[j] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else{
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}
		}
		HAL_I2C_Master_Transmit (&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
	}
	else if (p->mode == mode_mih){ //mineur harmonique
		for (int j = 1; j < 17; j+=2) {

			if ((sequence->notes[j/2+1]==1)|(sequence->notes[j/2+1]==4)|(sequence->notes[j/2+1]==6)){
				sequence->leds[j] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else if ((sequence->notes[j/2+1]==1)|(sequence->notes[j/2+1]==4)|(sequence->notes[j/2+1]==6)){
				sequence->leds[j] = 0;
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else{
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}

		}
		HAL_I2C_Master_Transmit (&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
	}
	else if (p->mode==mode_blu){ //blues
		for (int j = 1; j < 17; j+=2) {

			if ((sequence->notes[j/2+1]==1)|(sequence->notes[j/2+1]==5)|(sequence->notes[j/2+1]==7)){
				sequence->leds[j] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else if ((sequence->notes[j/2+1]==0)|(sequence->notes[j/2+1]==4)|(sequence->notes[j/2+1]==6)){
				sequence->leds[j] = 0;
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j] += 1<<k;
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j] = 1<<(sequence->notes[j/2+1]);
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}
			else{
				sequence->leds[j+1] = 0;
				if((j==sequence->step)|(j+1 == sequence->step)){
					for (int k = 0; k < 16; k++){
						if ((k<sequence->notes[j/2+1])|(k>sequence->notes[j/2+1])){
							sequence->leds[j+1] += 1<<k;
						}
					}
				}
				else{
					sequence->leds[j+1] = 1<<(sequence->notes[j/2+1]);
				}
			}

		}
		HAL_I2C_Master_Transmit (&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
	}

}
*/

void seq_disp_memo(seq_TypeDef* sequence,seq_memoire_TypeDef* mem){
	for (int i = 0 ; i < 17 ; i++) {
		sequence->leds[i] = 0;
	}
	sequence->leds[mem->position] = 1<<2;
	for (int k = 0; k<8; k++){
		if (mem->def[k]==1){
			sequence->leds[k*2] += 1<<4;
		}
		else{
			sequence->leds[k*2+1] += 1<<4;
		}
	}
	HAL_I2C_Master_Transmit(&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
}

void seq_disp_note(seq_TypeDef* sequence, seq_parametres_TypeDef* p){
	for (int i = 0 ; i < 17 ; i++) {
		sequence->leds[i] = 0;
	}

	if ((p->tonique-57)%12==0) {//A REFAIRE PAREIL
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4);
		sequence->leds[4] = (1 << 2) + (1 << 5);
		sequence->leds[6] = (1 << 2) + (1 << 5);
		sequence->leds[8] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4);
	}
	else if (((p->tonique-58)%12 == 0)|((p->tonique-59)%12 == 0)) {//B
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 1) + (1 << 3) + (1 << 5);
		sequence->leds[6] = (1 << 1) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[8] = (1 << 1) + (1 << 2) + (1 << 3);
	}
	else if (((p->tonique-60)%12==0)|((p->tonique-61)%12==0)) {//C
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 1) + (1 << 5);
		sequence->leds[6] = (1 << 1) + (1 << 5);
		sequence->leds[8] = (1 << 1) + (1 << 5);
	}
	else if ((p->tonique-62)%12==0) {//D
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 1) + (1 << 5);
		sequence->leds[6] = (1 << 1) + (1 << 5);
		sequence->leds[8] = (1 << 2) + (1 << 3) + (1 << 4);
	}
	else if (((p->tonique-63)%12==0)|((p->tonique-64)%12==0)) {//E
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 1) + (1 << 3) + (1 << 5);
		sequence->leds[6] = (1 << 1) + (1 << 3) + (1 << 5);
		sequence->leds[8] = (1 << 1) + (1 << 5);
	}
	else if (((p->tonique-65)%12==0)|((p->tonique-66)%12==0)) {//F
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 3) + (1 << 5);
		sequence->leds[6] = (1 << 3) + (1 << 5);
		sequence->leds[8] = (1 << 5);
	}
	else if (((p->tonique-55)%12==0)|((p->tonique-56)%12==0)) {//G
		sequence->leds[2] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[4] = (1 << 1) + (1 << 5);
		sequence->leds[6] = (1 << 1) + (1 << 3) + (1 << 5);
		sequence->leds[8] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 5);
	}
	else {
		sequence->leds[2] = 0;
		sequence->leds[4] = 0;
		sequence->leds[6] = 0;
		sequence->leds[8] = 0;
	}

	if (((p->tonique-56)%12==0)|((p->tonique-61)%12==0)|((p->tonique-66)%12==0)) {//Sharp
		sequence->leds[12] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
		sequence->leds[14] = (1 << 2) + (1 << 4);
		sequence->leds[16] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5);
	}
	else if (((p->tonique-58)%12==0)|((p->tonique-63)%12==0)) {//Flat
		sequence->leds[12] = (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4);
		sequence->leds[14] = (1 << 1) + (1 << 2);
		sequence->leds[16] = 0;
	}
	else {
		sequence->leds[12] = 0;
		sequence->leds[14] = 0;
		sequence->leds[16] = 0;
	}
	HAL_I2C_Master_Transmit(&hi2c1, 0xE0, sequence->leds, 17, HAL_MAX_DELAY);
}
