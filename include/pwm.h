/*!
 *  \brief     Control PWM Library
 *  \author    Anabel Díaz Labrador
 *  \date      22/11/2022
 *  \pre       Without trying
 *  \warning   
 *  \copyright GNU Public License.
 *  @file
 */

#ifndef _PWM_H
#define _PWM_H

#include <types.h>
#include <sys/param.h> // revisar
#include <sys/interrupts.h> // revisar
#include <sys/sio.h> // revisar
#include <sys/locks.h> // revisar

/*! @defgroup pwm PWM Management
 *
 * Set of functions used to manage PWM signals.
 *
 */

/*! PWM init Frecuency
 *
 *  @brief PWM initiator function by the frecuency.
 *
 *  @param channel
 *  @param frecuency
 *  @param period
 *  @param per_duty
 *
 */
void pwm_init(uint8_t channel, uint8_t frecuency, uint8_t period, uint8_t duty);

/*! PWM init period and cycles
 *
 *  @brief PWM initiator function by the frecuency.
 *
 *  @param channel
 *  @param clock
 *  @param period
 *
 */
void pwm_init_c(uint8_t channel, uint8_t period, uint8_t duty);

/*! PWM polarity
 *
 *  @brief Function to set the polarity (active high or active low).
 *
 *  @param polarity Zero is active low and any other active high
 *
 */
void pwm_set_polarity(uint8_t polarity);

/*! PWM alignment
 *
 *  @brief Function to set the alignment.
 *
 *  @param alignment Param to set the alignment: Zero to set left
 * alignment and any other to set center alignment.
 *
 */
void pwm_set_alignment(uint8_t alignment);

/*! PWM dty
 *
 *  @brief Function to set the dty.
 *
 *  @param n Dty number
 *
 */
void pwm_set_duty(uint8_t n);

/*! PWM percent
 *
 *  @brief Function to set percentage that relates the dty and the period
 *
 *  @param percentage percentage
 *
 */
void pwm_set_duty_percentage(uint8_t percentage);

/*! PWM percent
 *
 *  @brief Function to set percentage that relates the dty and the period
 *
 *  @param percentage percentage
 *
 */
void pwm_set_period(uint8_t period);

/*! PWM Set channel
 *
 *  @brief Function to choose a channel and set the corresponding clock
 *
 *  @param channel
 *
 */
void pwm_set_channel(uint8_t channel);

/*! PWM Set prescale
 *
 *  @brief Function to choose prescale
 *
 *  @param prescale
 *
 */
void pwm_set_prescale(uint8_t prescale);

/*! PWM Set frecuency 
 *
 *  @brief Function to set frecuency
 *
 *  @param frecuency
 * 
 */
void pwm_set_frecuency(uint8_t frecuency);

/*! PWM Upper power of two
 *
 *  @brief Function to Upper power of two
 *
 *  @param value
 * 
 */
uint8_t upper_power_of_two(uint8_t value);

#endif
