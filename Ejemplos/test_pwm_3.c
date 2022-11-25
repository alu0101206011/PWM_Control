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
	uint8_t channel, duty, per, answer, polaridad, alineamiento;
	uint16_t frecuency;
	
	while(1) {
		serial_print("\n\nControl PWM ===============\n");
		
		serial_print("\n\nElija canal PWM[0:3]:");
		channel = serial_getdecbyte();
		serial_print("\n\n Configuración basica del canal.\n");
		serial_print("\n\nElija un periodo entre 0 y 255:");
		per = serial_getdecbyte();
		serial_print("\n\nElija un porcentaje de duty:");
		duty = serial_getdecbyte();	
		serial_print("\n\nElija una frecuencia (kHz):");
		frecuency = serial_getdecword();
		pwm_init(channel, frecuency, per, duty);

		while(1) {
			serial_print("\n¿Desea ver la configuración actual 1 o 0: ");		
			answer = serial_getdeclong();
			if (answer == 1) 
				pwm_get_data();

			serial_print("\n¿Desea configurar otro canal? 1 o 0: ");
			answer = serial_getdeclong();
			if (answer == 1) break;

			serial_print("\n\nElija un porcentaje de duty:");
			duty = serial_getdecbyte();				
			pwm_set_duty_percentage(duty);

			serial_print("\n\nElija una frecuencia (kHz):");
			frecuency = serial_getdecword();			
			pwm_set_frecuency(frecuency);	
			pwm_set_polarity(!polaridad); // para refrescar la frecuencia y que sea visible el cambio
			pwm_set_polarity(polaridad);
			
			serial_print("\n\nElija alineamiento 0 izq 1 centrado:");
			alineamiento = serial_getdecbyte();		
			pwm_set_alignment(alineamiento);

			serial_print("\n\nElija un polaridad: ");
			polaridad = serial_getdecbyte();
			pwm_set_polarity(polaridad);
		}
	}
}
