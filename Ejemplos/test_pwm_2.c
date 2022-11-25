/* ****************************************

	Tests PWM

  *************************************** */

#include <types.h>
#include <pwm.h>
#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h>
#include <sys/locks.h>

int main () {
	uint8_t channel, duty, per, polaridad;
	uint16_t frecuency;
	while(1) {
		serial_print("\n\nControl PWM ===============\n");
		serial_print("\n\nElija canal PWM[0:3]:");
		channel = serial_getdecbyte();
		serial_print("\n\nElija un periodo entre 0 y 255:");
		per = serial_getdecbyte();
		serial_print("\n\nElija un porcentaje de duty:");
		duty = serial_getdecbyte();	
		serial_print("\n\nElija una frecuencia (Hz):");
		frecuency = serial_getdeclong();	
		pwm_init(channel, frecuency, per, duty);
		serial_print("\n\nElija un polaridad: ");
		polaridad = serial_getdecbyte();
		pwm_set_polarity(polaridad);
		serial_print("\n");
		serial_print("\nTerminó iteración\n");
	}
}
