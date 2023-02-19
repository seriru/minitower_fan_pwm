# Description
This repo contains C program that controls the fan speed of [52Pi's ZP-0130
Mini Tower NAS Kit](https://wiki.52pi.com/index.php?title=ZP-0130) for the Raspberry Pi 4b SBC.

# Compilation
The code requires the [WiringPi API](https://github.com/WiringPi/WiringPi/releases/).

`gcc fan_pwm.c -o fan_pwm -lwiringPi -lpthread`

# Systemd init
Copy the compiled binary to /usr/local/bin/ and the service file to
/lib/systemd/system/.

`sudo systemctl enable minitower_fan_pwm && sudo systemctl start minitower_fan_pwm`




