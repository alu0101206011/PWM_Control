/* 
 * PWM Control
 * 
 * Anabel Díaz Labrador
 * Sistemas empotrados
 *
 * */

#include <pwm.h>

uint8_t channel = 0;
uint8_t addr_period = M6812_PWPER0; // Suposing channel zero
uint8_t addr_duty = M6812_PWDTY0; // Suposing channel zero
uint8_t percentage_flag = 0;

/*! PWM init Frecuency
 *
 *  @brief PWM initiator function by the frecuency.
 *
 *  @param channel
 *  @param frecuency
 *  @param duty
 *
 */
void pwm_init(uint8_t channel, uint8_t frecuency, uint8_t period, uint8_t duty) {
    pwm_set_frecuency(frecuency);
    pwm_set_channel(channel);
    pwm_set_prescale(5);
    pwm_set_alignment(0);
    pwm_set_period(period);
    pwm_set_duty_percentage(20);
}

/*! PWM init period and cycles
 *
 *  @brief PWM initiator function.
 *
 *  @param channel
 *  @param clock
 *  @param period
 *
 */
void pwm_init_c(uint8_t channel, uint8_t period, uint8_t duty) {
	serial_print("\nEntré en init c\n");
    pwm_set_channel(channel);
    //pwm_set_prescale(0);
    //pwm_set_alignment(0);
    serial_print("\nSalí de elegir canal\n");
    pwm_set_polarity(1);
    pwm_set_period(period);
    pwm_set_duty(duty);
}

/*! PWM polarity
 *
 *  @brief Function to set the polarity (active high or active low).
 *
 *  @param polarity Zero is active low and any other active high
 *
 */
void pwm_set_polarity(uint8_t polarity) {
    if(polarity == 0){
      polarity = (uint8_t)1 << channel;
      _io_ports[M6812_PWPOL] = _io_ports[M6812_PWPOL] & ~polarity;
    } else if(polarity == 1){
      polarity = (uint8_t)1 << channel;
      _io_ports[M6812_PWPOL] = _io_ports[M6812_PWPOL] | polarity;
    }
}

/*! PWM alignment
 *
 *  @brief Function to set the alignment.
 *
 *  @param alignment Param to set the alignment: Zero to set left
 * alignment and any other to set center alignment.
 *
 */
void pwm_set_alignment(uint8_t alignment) {
    if (alignment == 0) {
        alignment = (uint8_t)1 << 3;
        _io_ports[M6812_PWCTL] = _io_ports[M6812_PWCTL] & ~alignment;
    } else if (alignment == 1) {
        alignment = (uint8_t)1 << 3;
        _io_ports[M6812_PWCTL] = _io_ports[M6812_PWCTL] | alignment;
    }
}

/*! PWM Duty
 *
 *  @brief Function to set the dty.
 *
 *  @param n Duty number
 *
 */
void pwm_set_duty(uint8_t duty) {
	if (duty > _io_ports[addr_period])
		serial_print("\nError duty can't be greater than period\n");
	_io_ports[addr_duty] = duty;
	serial_print("\nSe puso duty\n");
}

/*! PWM percent
 *
 *  @brief Function to set percentage that relates the dty and the period
 *
 *  @param n percentage
 *
 */
void pwm_set_duty_percentage(uint8_t percentage) {
    uint16_t acc = _io_ports[addr_period] * percentage;
    uint8_t duty_per = acc / 100;
    _io_ports[addr_duty] = duty_per;
}

/*! PWM period
 *
 *  @brief Function to set period
 *
 *  @param period period
 *
 */
void pwm_set_period(uint8_t period) {
    _io_ports[addr_period] = period;
    serial_print("\nSe puso periodo\n");
}

/*! PWM Set channel
 *
 *  @brief Function to choose a channel
 *  @param channel
 *
 */
void pwm_set_channel(uint8_t new_channel) {
    uint8_t mask = 3; // 00000011  
    channel = new_channel & mask;
    switch (channel) {
    case 0:
        _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN0;
        addr_period = M6812_PWPER0;
        addr_duty = M6812_PWDTY0;
        serial_print("\nElegi canal 0\n");
        break;
    case 1:
        _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN1;
        addr_period = M6812_PWPER1;
        addr_duty = M6812_PWDTY1;
        break;
    case 2:
        _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN2;
        addr_period = M6812_PWPER2;
        addr_duty = M6812_PWDTY2;
        break;
    case 3:
        _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN3;
        addr_period = M6812_PWPER3;
        addr_duty = M6812_PWDTY3;
        break;
    default: break;
    }
    serial_print("\nsaliendo canal 0\n");
}

/*! PWM Set prescale
 *
 *  @brief Function to set prescale.
 *
 *  @param prescale Must to be a value between 0 and 7 both inclusive.
 *
 */
void pwm_set_prescale(uint8_t prescale) {
    uint8_t mask = 7; // 00000111
    prescale = prescale & mask;
    if (channel == 0 || channel == 1) {
        mask = mask << 3;
        prescale = prescale << 3;
        _io_ports[M6812_PWCLK] = (_io_ports[M6812_PWCLK] & ~mask) | prescale;  // Deleting current prescale and setting the new one
    } else if (channel == 2 || channel == 3) {
        _io_ports[M6812_PWCLK] = (_io_ports[M6812_PWCLK] & ~mask) | prescale;  // Deleting current prescale and setting the new one
    }
}

/*! PWM Frecuency to period
 *
 *
 */
void pwm_set_frecuency(uint8_t frecuency) {
	//Se debe llamar al prescale
}
