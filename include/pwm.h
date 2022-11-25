/*!
 *  \brief     Control PWM Library
 *  \author    Anabel Díaz Labrador
 *  \date      25/11/2022
 *  \copyright GNU Public License.
 */

#ifndef _PWM_H
#define _PWM_H

#include <types.h>
#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h>
#include <sys/locks.h>

/*! @defgroup pwm PWM Management
 *
 * Set of functions used to manage PWM signals.
 *
 */

/*! PWM Initializer function by frecuency
 *
 *  @brief This function is responsible for initializing 
 * PWM with some default parameters using frecuency: left alignment 
 * and high polarity.
 *
 *  @param channel Chosen channel.
 *  @param frecuency Frequency at which we want to see the clock. 
 * This will use prescaler.
 *  @param pwper Number of divisions in a cycle.
 *  @param per_duty Duty percentage.
 *
 */
void pwm_init(uint8_t channel, uint8_t frecuency, uint8_t pwper, uint8_t duty);

/*! PWM Initializer function
 *
 *  @brief This function is responsible for initializing 
 * PWM with some default parameters: left alignment,
 * high polarity and zero prescale.
 *
 *  @param channel Chosen channel.
 *  @param pwper Number of divisions in a cycle.
 *  @param duty Duty number.
 *
 */
void pwm_init_c(uint8_t channel, uint8_t pwper, uint8_t duty);

/*! PWM Set polarity
 *
 *  @brief Function to set the polarity.
 *
 *  @param polarity Zero is active low and any other active high.
 *
 */
void pwm_set_polarity(uint8_t polarity);

/*! PWM Set alignment
 *
 *  @brief Function to set the alignment.
 *
 *  @param alignment Param to set the alignment: Zero to set left
 * alignment and any other to set center alignment.
 *
 */
void pwm_set_alignment(uint8_t alignment);

/*! PWM Set duty
 *
 *  @brief Function to set the duty.
 *
 *  @param duty Duty number.
 *
 */
void pwm_set_duty(uint8_t n);

/*! PWM Set duty percentage
 *
 *  @brief Function to set duty percentage that relates the duty 
 * and the pwper.
 *
 *  @param percentage Duty percentage.
 *
 */
void pwm_set_duty_percentage(uint8_t percentage);

/*! PWM Set pwper
 *
 *  @brief Function to set pwper.
 *
 *  @param pwper Period number.
 *
 */
void pwm_set_per(uint8_t pwper);

/*! PWM Set channel
 *
 *  @brief Function to choose a channel. The global variables 
 * addr_period and addr_duty are also assigned the ports according 
 * to the chosen channel.
 * 
 *  @param channel Channel number.
 *
 */
void pwm_set_channel(uint8_t channel);

/*! PWM Set prescale
 *
 *  @brief Function to set prescale depending on the channel we are on.
 * Clock A is used on ports 0 and 1. Clock B is used on ports 2 and 3.
 *
 *  @param prescale Must to be a value between 0 and 7 both inclusive.
 *
 */
void pwm_set_prescale(uint8_t prescale);

/*! PWM Set frecuency
 *
 *  @brief Function to set the frecuency using the prescaler.
 * 
 *  @param channel Frecuency number in kHz.
 * 
 */
void pwm_set_frecuency(uint8_t frecuency);

/*! PWM Get data
 *
 *  @brief Function to get all PWM data.
 *
 */
void pwm_get_data(void);

#endif
