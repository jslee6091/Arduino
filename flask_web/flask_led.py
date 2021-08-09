from flask import Flask, render_template, request
import RPi.GPIO as GPIO

LED = 4
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)

app = Flask(__name__)

@app.route('/')
def hello():
    return render_template('index.html')

@app.route('/led_control', methods=['GET'])
def led_control():
    if request.method == 'GET':
        # html에서 LED 상태 표시하기 위한 변수
        status = ''

        # 전송 받은 LED 정보
        led = request.args["led"]
        
        # LED ON을 클릭시 '1' 전달됨
        if led == '1':
            # GPIO 출력 True - LED 켜기
            GPIO.output(LED, True)
            status = 'ON'
        
        # LED OFF을 클릭시 '0' 전달됨
        else:
            # LED 끄기
            GPIO.output(LED, False)
            status = 'OFF'
    
    return render_template('index.html', ret = status)

if __name__ == '__main__':
    app.run(debug=True, port=80, host='0.0.0.0')
