import RPi.GPIO as GPIO
import time

LED = 4
BUTTON = 5

# Using BCM GPIO
GPIO.setmode(GPIO.BCM)
# Set LED pin as OUTPUT
GPIO.setup(LED, GPIO.OUT)
# Set BUTTON pin as INPUT
GPIO.setup(BUTTON, GPIO.IN, pull_up_down = GPIO.PUD_UP)

count = 0

try:

    while True:
        # Do not click the button
        if GPIO.input(BUTTON):
            # turn off LED
            GPIO.output(LED, False)
        # Click the button
        else:
            # turn on LED
            GPIO.output(LED, True)
            count += 1
        print(f'LED lights {count} times')
        
except KeyboardInterrupt:
    print("keyboard interrupt")
    GPIO.cleanup()
