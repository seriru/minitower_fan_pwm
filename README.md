# Description
This repo contains C code that controls the fan speed of 52Pi's ZP-0130
Mini Tower NAS Kit for the Raspberry Pi 4b SBC.

# Compilation
The code requires wiringPi API, which can be found at
https://github.com/WiringPi/WiringPi/releases/

`gcc fan_pwm.c -o fan_pwm -lwiringPi -lpthread`

# Systemd init
Copy the compiled binary to /usr/local/bin/ and the service file to
/lib/systemd/system/.

`sudo systemctl enable minitower_fan_pwm && sudo systemctl start minitower_fan_pwm`




