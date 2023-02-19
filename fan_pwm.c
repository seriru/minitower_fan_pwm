/*
  Change the fan speed using PWM on Raspberry Pi
*/

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

#define THERMAL_FILE "/sys/class/thermal/thermal_zone0/temp"
#define DEBUG 0

const int fan_pwm_pin = 15;   /* GPIO 15 as per WiringPi, GPIO14 as per BCM */

int main (void) {
  float millidegrees;
  float cpu_temp_c;
  int fan_speed = 50;
  FILE* thermal;
  
  if (wiringPiSetup() == -1) { /* WiringPi GPIO */
    printf("Error: Unable to initialise wiringPi in wiringPiSetup().\n");
    exit(1);
  }
  
  pinMode(fan_pwm_pin, PWM_OUTPUT) ; /* set PWM pin as output */

  softPwmCreate(fan_pwm_pin, fan_speed, 100);
  
  while (1) {
    thermal = fopen(THERMAL_FILE, "r");

    if(thermal == NULL) {
      printf("Error: Unable to read %s.\n", THERMAL_FILE);
    }
    else {
      fscanf(thermal, "%f", &millidegrees);
      fclose(thermal);
    
      cpu_temp_c = millidegrees / 1000;

      if(cpu_temp_c < 48.0) {
	fan_speed = 0;
      }
      else if(cpu_temp_c >= 48.0 && cpu_temp_c < 52.0) {
	fan_speed = 50;
      }
      else if(cpu_temp_c >= 52.0 && cpu_temp_c < 56.0) {
	fan_speed = 65;
      }
      else if(cpu_temp_c >= 56.0 && cpu_temp_c < 60.0) {
	fan_speed = 80;
      }
      else { /* cpu_temp_c >= 60.0 */
	fan_speed = 100;
      }
      
      softPwmWrite(fan_pwm_pin, fan_speed);
      
      if(DEBUG) {
	printf("CPU temperature is %3.1fC\n", cpu_temp_c);
      	printf("Fan speed at %i.\n", fan_speed);
      }
    }
    
    delay(5000);
    
  }

  exit(0);
  
}
