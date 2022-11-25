/* ****************************************



  *************************************** */

#include <types.h>
#include <pwm.h>
#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h>
#include <sys/locks.h>

int main () {
	uint8_t channel, duty, per, frecuency;
	while(1) {
		serial_print("\n\nControl PWM ===============\n");
		serial_print("\n\nElija canal PWM[0:3]:");
		channel = serial_getdecbyte();
		serial_print("\n\nElija un periodo entre 0 y 255:");
		per = serial_getdecbyte();
		serial_print("\n\nElija un porcentaje de duty:");
		duty = serial_getdecbyte();	
		serial_print("\n\nElija una frecuencia (Hz):");
		frecuency = serial_getdecbyte();	
		pwm_init(channel, frecuency, per, duty);
		serial_print("\n");
		serial_print("\nTerminó iteración\n");
	}
	// documentación que se pone por defecto en init_c
}
// (uint8_t channel, uint8_t frecuency, uint8_t period, uint8_t per_duty)