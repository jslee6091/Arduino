import RPi.GPIO as GPIO
import time

LED = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)

try:
    # Set frequency of PWM 100 Hz
    pwm = GPIO.PWM(LED, 100) 
    # Set initial value of Duty cycle = 0 (LED OFF)
    pwm.start(0)

    while True:
        for i in range(10):
            # Change duty cycle from 0 to 100 percent
            pwm.ChangeDutyCycle(i*10)
            print(f'duty cycle is {i*10}')
            time.sleep(1)
except KeyboardInterrupt:
    pass
# Always executed whether error or not
finally:
    pwm.stop()
    GPIO.cleanup()
