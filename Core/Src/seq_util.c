/*
 * seq_util.c
 *
 *  Created on: Mar 18, 2021
 *      Author: moliver
 */

#include "main.h"

extern I2C_HandleTypeDef hi2c1;
extern DAC_HandleTypeDef hdac1;
extern uint16_t conversion_table[0x1000];
extern seq_parametres_TypeDef parametres;
extern uint16_t seq_adc[3];
extern TIM_HandleTypeDef htim1;

uint64_t* const memory_start = (uint64_t*) 0x0803F800;

void seq_gen(seq_TypeDef* sequence)
{
	uint8_t gen_step;
	for(gen_step=0; gen_step<8; ++gen_step)
	{
		while( !(RNG->SR&1)  );
		sequence->notes[gen_step] = RNG->DR & 0x7;
	}
	seq_disp_step(sequence,&parametres);


}

void seq_play_step(seq_TypeDef* sequence)
{

//	seq_disp_step(sequence,&parametres);
	static int b_is_running = 0;
	if(b_is_running) sequence->step++;
	sequence->step &= 7;
	DAC->DHR12R1 = conversion_table[60+gammes[parametres.mode][sequence->notes[sequence->step]]];
	HAL_GPIO_WritePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin, GPIO_PIN_RESET);


	b_is_running = 1;


}

void seq_disp_step(seq_TypeDef* sequence,seq_parametres_TypeDef* param)
{
	uint8_t step;
	for(step=0; step<8; ++step)
	{
		sequence->leds[2*step+1] = notes_led[sequence->notes[step]];
		sequence->leds[2*step+2] = 0;
	}
	sequence->leds[2*sequence->step + 2] = sequence->leds[2*sequence->step+1] ^ 0xFF;

	HAL_I2C_Master_Transmit(&hi2c1, 0xE0,sequence->leds, 17, 1000);

}

void seq_update_parameters(seq_parametres_TypeDef* parametres)
{
	parametres->tonique = seq_adc[0];
}

void seq_read_mem(seq_memoire_TypeDef* memo)
{
	uint8_t seq_int;
	uint8_t step_int;
	uint64_t* memory_pointer;
	for(seq_int=0,memory_pointer=memory_start; seq_int<8; ++seq_int)
	{
		for(step_int=0; step_int<8; ++step_int,memory_pointer++)
		{
			memo->memoire[seq_int].notes[step_int] = 7 & (uint8_t) *memory_pointer;
		}

	}

}

FLASH_EraseInitTypeDef pEraseInit;

void seq_write_mem(seq_memoire_TypeDef* memo)
{
	uint8_t w_step;
	uint64_t* memory_pointer;
	uint8_t w_mem;
	uint32_t erase_error = 0;
	pEraseInit.NbPages = 1;
	pEraseInit.Page = 127;
	pEraseInit.Banks = FLASH_BANK_1;
	pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&pEraseInit, &erase_error);
	for(memory_pointer=memory_start, w_mem=0; w_mem<8; ++w_mem)
	{
		for(w_step=0;
				w_step<8;
				++w_step, memory_pointer++)
		{
			HAL_FLASH_Program(
					FLASH_TYPEPROGRAM_DOUBLEWORD,
					(uint32_t) memory_pointer,
					(memo->memoire[w_mem].notes[w_step]));
		}
	}
	HAL_FLASH_Lock();

}
