import pygame
from pygame._sdl2 import controller
from time import sleep

DEADZONE = 0.1
LMOTOR_INP = pygame.CONTROLLER_AXIS_LEFTY
RMOTOR_INP = pygame.CONTROLLER_AXIS_RIGHTY
SERVO_INP = pygame.CONTROLLER_AXIS_TRIGGERRIGHT

pygame.init()
controller.init()

gamepad = None

while gamepad is None:
	pygame.event.pump()

	if controller.get_count() > 0:
		gamepad = controller.Controller(0)
		gamepad.init()
		print("gamepad connected")

running = True
while running:
	pygame.event.pump()

	left_motor = gamepad.get_axis(LMOTOR_INP) / -32768
	right_motor = gamepad.get_axis(RMOTOR_INP) / -32768
	servo = gamepad.get_axis(SERVO_INP) / 32768

	if abs(left_motor) < DEADZONE: left_motor = 0
	if abs(right_motor) < DEADZONE: right_motor = 0
	if abs(servo) < DEADZONE: servo = 0

	print(left_motor)
	print(right_motor)
	print(servo)
	print()

	sleep(0.1)
