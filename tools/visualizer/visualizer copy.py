#!/usr/bin/python3

import PySimpleGUI as sg
import colorsys
import sys

STACK_WIDTH = 200
STACK_HEIGHT = 600

# sg.Graph()
stack_A = sg.Graph(
	canvas_size = (STACK_WIDTH + 15, STACK_HEIGHT ),
	graph_bottom_left = (0,0),
	graph_top_right = (STACK_WIDTH, STACK_HEIGHT),
	background_color = 'black',
	key='-STACK_A-'
)
stack_B = sg.Graph(
	canvas_size = (STACK_WIDTH + 15, STACK_HEIGHT ),
	graph_bottom_left = (STACK_WIDTH, STACK_HEIGHT),
	graph_top_right = (STACK_WIDTH * 2, STACK_HEIGHT ),
	background_color = 'black',
	key='-STACK_B-'
)
actions = 	[
	[sg.Text('text')],
	[sg.Button('button')],
	[sg.Input()],
]

stacks = [[], [], []]
# print("stask[0] avt", stacks[1])
stacks[1] = sys.argv[1:]
stacks[0] = stacks[1].copy()
stacks[0].sort()

color = {}

# print("stask[0] avt", stacks[0])
# print("stask[1] avt", stacks[1])

print("color avt", color)


R= 255
G= 255
B= 255

layout = [
	[stack_A, stack_B],
]
window = sg.Window('Push_Swap _ Visualizer', 
                   layout,
                #    default_element_size=(12, 1),
                   resizable=True
		)

while True:
	event, value = window.read(timeout= 100)

	if event == sg.WIN_CLOSED:
		break

	stackLEN = len(stacks[0])
	for i in range(stackLEN):
		(r, g, b) = colorsys.hsv_to_rgb( i / stackLEN , 1.0, 1.0)
		R, G, B = int(255 * r), int(255 * g), int(255 * b)
		tl = float(0), STACK_HEIGHT - (i * STACK_HEIGHT / stackLEN)
		br = i * STACK_WIDTH / stackLEN + 1, tl[1] - STACK_HEIGHT / stackLEN
		print("i", i, "RGB", R, G, B, "tl", tl, "br", br)
		stack_A.DrawRectangle(
			top_left= tl,
			bottom_right= br,
			fill_color='#%02x%02x%02x' % (R, G, B),
			line_width=0,
		)

window.close()