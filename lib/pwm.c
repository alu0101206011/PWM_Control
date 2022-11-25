/* 
 * Control PWM Library
 * 
 * Anabel Díaz Labrador
 * 25/11/2022
 * Sistemas empotrados
 *
 * */

#include <pwm.h>

uint8_t channel = 0;
uint8_t addr_pwper = M6812_PWPER0; // Suposing channel zero
uint8_t addr_duty = M6812_PWDTY0; // Suposing channel zero

void pwm_init(uint8_t channel, uint8_t frecuency, uint8_t pwper, uint8_t per_duty) {
  pwm_set_frecuency(frecuency);
  pwm_set_channel(channel);
  pwm_set_alignment(0);
  pwm_set_polarity(1);
  pwm_set_per(pwper);
  pwm_set_duty_percentage(per_duty);
}

void pwm_init_c(uint8_t channel, uint8_t pwper, uint8_t duty) {
  pwm_set_channel(channel);
  pwm_set_prescale(0);
  pwm_set_alignment(0);
  pwm_set_polarity(1);
  pwm_set_per(pwper);
  pwm_set_duty(duty);
}

void pwm_set_polarity(uint8_t polarity) {
  if(polarity == 0){
    polarity = (uint8_t)1 << channel;
    _io_ports[M6812_PWPOL] = _io_ports[M6812_PWPOL] & ~polarity;
  } else if(polarity == 1){
    polarity = (uint8_t)1 << channel;
    _io_ports[M6812_PWPOL] = _io_ports[M6812_PWPOL] | polarity;
  }
}

void pwm_set_alignment(uint8_t alignment) {
  if (alignment == 0) {
    alignment = (uint8_t)1 << 3;
    _io_ports[M6812_PWCTL] = _io_ports[M6812_PWCTL] & ~alignment;
  } else if (alignment == 1) {
    alignment = (uint8_t)1 << 3;
    _io_ports[M6812_PWCTL] = _io_ports[M6812_PWCTL] | alignment;
  }
}

void pwm_set_duty(uint8_t duty) {
  if (duty > _io_ports[addr_pwper])
    serial_print("\nError duty can't be greater than pwper\n");
  _io_ports[addr_duty] = duty;
}

void pwm_set_duty_percentage(uint8_t percentage) {
  uint16_t acc = _io_ports[addr_pwper] * percentage;
  uint8_t duty_per = acc / 100;
  _io_ports[addr_duty] = duty_per;
}

void pwm_set_per(uint8_t pwper) {
  _io_ports[addr_pwper] = pwper;
}

void pwm_set_channel(uint8_t new_channel) {
  uint8_t mask = 3; // 00000011  
  channel = new_channel & mask;
  switch (channel) {
  case 0:
    _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN0;
    addr_pwper = M6812_PWPER0;
    addr_duty = M6812_PWDTY0;
    break;
  case 1:
    _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN1;
    addr_pwper = M6812_PWPER1;
    addr_duty = M6812_PWDTY1;
    break;
  case 2:
    _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN2;
    addr_pwper = M6812_PWPER2;
    addr_duty = M6812_PWDTY2;
    break;
  case 3:
    _io_ports[M6812_PWEN] = _io_ports[M6812_PWEN] | M6812B_PWEN3;
    addr_pwper = M6812_PWPER3;
    addr_duty = M6812_PWDTY3;
    break;
  default: break;
  }
}

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

uint8_t upper_power_of_two(uint8_t v) { 
  if (0 >= v || 1 >= v || 2 >= v) {
    return v;
  } else if (4 >= v) {
    return 4;
  } else if (8 >= v) {
    return 8;
  } else if (16 >= v) {
    return 16;
  } else if (32 >= v) {
    return 32;
  } else if (64 >= v) {
    return 64;
  } else {
    return 128;
  }
}

void pwm_set_frecuency(uint8_t frecuency) {
  uint8_t prescale = 80 / frecuency;
  prescale = upper_power_of_two(prescale);
  pwm_set_prescale(prescale);
}

void pwm_get_data(void) {
  serial_print("\n======= PWM Data =======\n");
  serial_print("\n\t- Channel: ");
  serial_printdecbyte(channel);
  serial_print("\n\t- Duty: ");
  serial_printdecbyte(_io_ports[addr_duty]);
  serial_print("\n\t- Duty percentage: ");
  serial_printdecbyte((_io_ports[addr_duty] * 100 / _io_ports[addr_pwper]));
  serial_print("\n\t- PWPER: ");
  serial_printdecbyte(_io_ports[addr_pwper]);
  serial_print("\n\t- Prescale A: ");
  serial_printdecbyte((_io_ports[M6812_PWCLK] >> 3) & 7);
  serial_print("\n\t- Prescale B: ");
  serial_printdecbyte(_io_ports[M6812_PWCLK] & 7);
  serial_print("\n\t- Alignment: ");
  if (_io_ports[M6812_PWCTL] == 0) {
    serial_print("Left");
  } else {
    serial_print("Centered");
  }  
  serial_print("\n\t- Polarity: ");
  serial_printdecbyte((_io_ports[M6812_PWPOL] >> channel) & 1);
}
