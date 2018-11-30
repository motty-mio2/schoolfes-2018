#import
import math
import matplotlib.pyplot as plt
import RPi.GPIO as GPIO
import smbus
import time

#Number_define
TRIG_PIN1 = 8
ECHO_PIN1 = 10
Button_Pin = 13
MtL = 0x60 #Left_Driver_Address
MtR = 0x62 #Right_Driver_Address
QMC = 0x0d #QMC5883L_Address

#i2c_Config
i2c = smbus.SMBus(1)
i2c.write_byte_data(QMC,0x0b,0x01)
i2c.write_byte_data(QMC,0x09,0x1d)

#Motor_Driver_Config
def motor(L,R):
    Volt = 0x70
    if R == 1:
        R = 2
    elif R == 2:
        R = 1
    i2c.write_byte_data(MtL,0,Volt * 4 + L)
    i2c.write_byte_data(MtR,0,Volt * 4 + R)

#Compass_Config
def get2(ADD,BIX):
    return (i2c.read_byte_data(ADD,BIX))

def degHor():
    data_X = (get2(0x0d,0x01)*256+get2(0x0d,0x00))
    data_Y = (get2(0x0d,0x03)*256+get2(0x0d,0x02))
    get2(0x0d,0x06)
    get2(0x0d,0x05)
    if data_X >= 2**15:
        data_X -= 2**16
    if data_Y >= 2**15:
        data_Y -= 2**16
    return (math.degrees(math.atan2(DYi,DXi))+180)

#GPIO_Set(Sensor)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(8,GPIO.OUT) #Echo_out
GPIO.setup(10,GPIO.IN) #Echo_in
GPIO.setup(13,GPIO.IN) #Button
GPIO.setwarnings(False)

#Button
def Button():
    return GPIO.input(13)

#PWA_Check
def distance(num):
    GPIO.output("TRIG_PIN"+str(num), GPIO.LOW)
    time.sleep(0.3)
    GPIO.output("TRIG_PIN"+str(num), True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)
    t = pulseIn(ECHO_PIN)
    dist = v * t/2
    GPIO.cleanup()
    return dist

Route = []
degrs = []

#Main_Program
print("waiting")
while True:
    if Button() == 1:
        break
print("Start!")

time.sleep(1)

time_on = time.time()
while (Button() == 0):
    motor(1,1)
    if dist(1) <= 7:
        Route.append(time.time() - time_on)
        now_deg = degHor()
        while (dist(1)<=7):
            motor(1,2)
            time_on = time.time()
        degrs.append(now_deg - degHor())

print("finish")
motor(0,0)