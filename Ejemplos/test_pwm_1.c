/* ****************************************

  Ejemplo de función para generar un retraso
  con precisón de microsegundos.
  Si retraso es mayor que alcance del temporizador
  se cuentan más de un disparo.
  Utiliza el canal 6 del temporizador.

  Copyright (C) Alberto F. Hamilton Castro
  Dpto. de Ingeniería Informática de Sistemas
  Universidad de La Laguna

  Licencia: GPLv3

  *************************************** */

#include <types.h>
#include <pwm.h>
#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h>
#include <sys/locks.h>

int main () {
	uint8_t channel, duty, per;
	while(1) {
		serial_print("\n\nControl PWM ===============\n");
		serial_print("\n\nElija canal PWM[0:3]:");
		channel = serial_getdecbyte();
		serial_print("\n\nElija un periodo entre 0 y 255:");
		per = serial_getdecbyte();
		serial_print("\n\nElija un duty entre 0 y 255:");
		duty = serial_getdecbyte();	
		pwm_init_c(channel, per, duty);
		serial_print("\n");
		serial_print("\nTerminó iteración\n");
	}
	// documentación que se pone por defecto en init_c
	/*
	pwm_set_channel(channel);
    pwm_set_prescale(0);
    pwm_set_alignment(0);
    pwm_set_period(100);
    pwm_set_duty(30);
    */
}
