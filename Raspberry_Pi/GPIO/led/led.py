import RPi.GPIO as GPIO
import time

LED = 4

# Using BCM GPIO
GPIO.setmode(GPIO.BCM)
# Set LED pin as OUTPUT
GPIO.setup(LED, GPIO.OUT)

try:

    for i in range(1, 20):
        # turn on LED
        GPIO.output(LED, True)
        # delay 1 second
        time.sleep(1)
        # turn off LED
        GPIO.output(LED, False)
        time.sleep(1)
        print(f'LED lights {i} times')
        
except KeyboardInterrupt:
    print("keyboard interrupt")
    GPIO.cleanup()
