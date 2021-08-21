/*
 * seq_def.h
 *
 *  Created on: Mar 23, 2021
 *      Author: moliver
 */

#ifndef INC_SEQ_DEF_H_
#define INC_SEQ_DEF_H_

/**
 * Le type d'un mode.
 */

typedef enum
{
	 mode_maj=0,
	 mode_min,
	 mode_mih,
	 mode_blu,
	 mode_wst
} seq_mode;

/**
 * Le type de structure des parametres du sequenceur.
 */
typedef struct seq_parametres_TypeDef
{
	uint8_t tonique_jck; /* La tonique de la gamme par le cable jack. */
	uint8_t tonique_pot; /* La tonique de la gamme par le potentiometre. */
	uint8_t tonique; /* La tonique du sequenceur. */
	uint8_t spread_mix; /* L'etalement des notes. */
	uint8_t mode_mix; /* Le mode de la gamme jouee. */
	uint8_t mode_def; /* Le sens de defilement. */
	seq_mode mode; /* Le mode de la gamme jouee en chaine de caractere. */
	uint8_t seq_num; /* Le numero de la sequence actuelle. */
	uint8_t shift_btn; /* Le bouton SHIFT */
	uint8_t wheel_btn; /* Le bouton de la roue codeuse. */

} seq_parametres_TypeDef;

typedef uint8_t seq_leds[17];


/**
 * Le type de structure de prise en charge d'une sequence jouee.
 */
typedef struct seq_TypeDef
{
	uint8_t notes[8];
	seq_leds leds;
	uint8_t step;
} seq_TypeDef;

typedef struct seq_memoire_TypeDef
{
	seq_TypeDef memoire[8];
	uint8_t  def[8]; /* 0 ou 1 ou 2 : est-ce que la séquence est réservée en mémoire, ou aléatoire */
	uint8_t position; /* position en memoire */
} seq_memoire_TypeDef;

void seq_update_parameters(seq_parametres_TypeDef*);

void seq_disp_step(seq_TypeDef*, seq_parametres_TypeDef*);
void seq_disp_memo(seq_TypeDef*, seq_memoire_TypeDef*);
void seq_disp_note(seq_TypeDef*, seq_parametres_TypeDef*);
void seq_read_mem(seq_memoire_TypeDef*);
void seq_write_mem(seq_memoire_TypeDef*);


#endif /* INC_SEQ_DEF_H_ */
