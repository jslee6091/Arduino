import RPi.GPIO as GPIO
import time

BUZZER = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(BUZZER, GPIO.OUT)

# Tone value of Do, Re, Mi, Pa, Sol, La, Si, Do
scale = [262, 394, 330, 349, 292, 440, 494, 523]

list_lo = [4, 5, 4, 5, 1, 2, 1, 2]
term = [0.4, 0.1, 0.4, 0.2, 0.4, 0.2, 0.4, 0.2]

try:
    # Set frequency of PWM 100 Hz
    pwm = GPIO.PWM(BUZZER, 100) 
    # Set initial value of Duty cycle = 100
    pwm.start(100)
    # Change Duty Cycle to 90 percent
    pwm.ChangeDutyCycle(90)

    for i in range(8):
        # Change frequency of PWM to make different sound
        pwm.ChangeFrequency(scale[list_lo[i]])

        # delay time between sounds
        time.sleep(term[i])

    # terminate PWM
    pwm.stop()

except KeyboardInterrupt:
    pass

# Always executed whether error or not
finally:
    GPIO.cleanup()
