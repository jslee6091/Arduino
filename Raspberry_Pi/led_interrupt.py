import RPi.GPIO as GPIO
import time

LED = 4
INTERRUPT = 5

# Using BCM GPIO
GPIO.setmode(GPIO.BCM)
# Set LED pin as OUTPUT
GPIO.setup(LED, GPIO.OUT)
# Set BUTTON pin as INPUT
GPIO.setup(INTERRUPT, GPIO.IN, pull_up_down = GPIO.PUD_UP)

# Interrupt callback function
def my_call(pin):
    print('GPIO input LED : ', GPIO.input(LED))

    if GPIO.input(LED):
        GPIO.output(LED, False)
        print('LED turn off')
    else:
        GPIO.output(LED, True)
        print('LED turn on')

# Add interrupt service routine
GPIO.add_event_detect(INTERRUPT, GPIO.FALLING, callback=my_call, bouncetime=300)

count = 0

try:

    while True:
        print(f'{count} seconds')
        count += 1
        time.sleep(1)
        
except KeyboardInterrupt:
    print("keyboard interrupt")
    # Remove interrupt service routine
    GPIO.remove_event_detect(INTERRUPT)
    GPIO.cleanup()
