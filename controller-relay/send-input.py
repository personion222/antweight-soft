import serial
import threading
import time
import pygame
from pygame._sdl2 import controller


PORT = "/dev/ttyACM0"
BAUD = 115200

DEADZONE = 0.1
LMOTOR_INP = pygame.CONTROLLER_AXIS_LEFTY
RMOTOR_INP = pygame.CONTROLLER_AXIS_RIGHTY
SERVO_INP = pygame.CONTROLLER_AXIS_TRIGGERRIGHT
THROTTLE_STICK = pygame.CONTROLLER_AXIS_LEFTY

FREQUENCY = 15


def clamp(val):
	return min(max(val, 0), 1)

def reader(ser):
	while 1:
		log = ser.readline().decode("utf-8")
		# if log: print(log)


pygame.init()
controller.init()

clock = pygame.time.Clock()
gamepad = None

while gamepad is None:
	pygame.event.pump()

	if controller.get_count() > 0:
		gamepad = controller.Controller(0)
		gamepad.init()
		print("gamepad connected")

ser = serial.Serial(PORT, BAUD, timeout=1)
print(f"connected to {PORT} @ baud rate {BAUD}")

reader_thread = threading.Thread(target=reader, args=(ser,), daemon=True)
reader_thread.start()

while 1:
	clock.tick(FREQUENCY)
	pygame.event.pump()

	left_motor = gamepad.get_axis(LMOTOR_INP) / -32767
	right_motor = gamepad.get_axis(RMOTOR_INP) / -32767
	servo = gamepad.get_axis(SERVO_INP) / 32767

	if abs(left_motor) < DEADZONE: left_motor = 0
	if abs(right_motor) < DEADZONE: right_motor = 0
	if abs(servo) < DEADZONE: servo = 0

	left_motor = (left_motor + 1) / 2
	right_motor = (right_motor + 1) / 2

	left_motor = clamp(left_motor)
	right_motor = clamp(right_motor)
	servo = clamp(servo)

	left_motor = int(255 * left_motor)
	right_motor = int(255 * right_motor)
	servo = int(255 * servo)

	print(left_motor)
	print(right_motor)
	print(servo)

	left_motor_byte = left_motor.to_bytes(1, "big")
	right_motor_byte = right_motor.to_bytes(1, "big")
	servo_byte = servo.to_bytes(1, "big")

	out_string = b''.join([left_motor_byte, right_motor_byte, servo_byte])
	print(out_string)

	ser.write(b''.join([left_motor_byte, right_motor_byte, servo_byte]))

	print()
	# time.sleep(1)
