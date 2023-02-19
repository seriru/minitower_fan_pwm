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
  int intensity;            
  float millidegrees;
  float systemp_c;
  FILE* thermal;
  
  if (wiringPiSetup() == -1) { /* WiringPi GPIO */
    printf("Error: Unable to initialise wiringPi in wiringPiSetup().\n");
    exit(1);
  }
  
  pinMode(fan_pwm_pin, PWM_OUTPUT) ; /* set PWM pin as output */

  softPwmCreate(fan_pwm_pin, 50, 100);
  
  while (1) {
    thermal = fopen(THERMAL_FILE, "r");

    if(thermal == NULL) {
      printf("Error: Unable to read %s.\n", THERMAL_FILE);
    }
    else {
      fscanf(thermal, "%f", &millidegrees);
      fclose(thermal);
    
      systemp_c = millidegrees / 1000;

      if(DEBUG)
	printf("CPU temperature is %3.1fC\n", systemp_c);
      
      if(systemp_c < 48.0) {
	softPwmWrite(fan_pwm_pin, 0);

	if(DEBUG)
	  printf("Fan at 0.\n");
      }
      else if(systemp_c >= 48.0 && systemp_c < 52.0) {
	softPwmWrite(fan_pwm_pin, 50);
	
	if(DEBUG)
	  printf("Fan at 50.\n");	
      }
      else if(systemp_c >= 52.0 && systemp_c < 56.0) {
	softPwmWrite(fan_pwm_pin, 65);

	if(DEBUG)
	  printf("Fan at 65.\n");	
      }
      else if(systemp_c >= 56.0 && systemp_c < 60.0) {
	softPwmWrite(fan_pwm_pin, 80);

	if(DEBUG)
	  printf("Fan at 80.\n");	
      }
      else { /* systemp_c >= 60.0 */
	softPwmWrite(fan_pwm_pin, 100);

	if(DEBUG)
	  printf("Fan at 100.\n");	
      }
    }
    
    delay(5000);
    
  }

  exit(0);
  
}
