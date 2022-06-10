#!/usr/bin/python3

from time import sleep
import PySimpleGUI as sg
import colorsys
import sys

STACK_WIDTH = 200
STACK_HEIGHT = 600
stacks = [[], [], []]
color = {}

# sg.Graph()
stack_A = sg.Graph(
	canvas_size = (STACK_WIDTH, STACK_HEIGHT ),
	graph_bottom_left = (0,0),
	graph_top_right = (STACK_WIDTH, STACK_HEIGHT),
	background_color = 'black',
	key='-STACK_A-'
)
stack_B = sg.Graph(
	canvas_size = (STACK_WIDTH, STACK_HEIGHT ),
	graph_bottom_left = (0, 0),
	graph_top_right = (STACK_WIDTH , STACK_HEIGHT ),
	background_color = 'black',
	key='-STACK_B-'
)
actions = 	[
	[sg.Text('text')],
	[sg.Button('button')],
	[sg.Input()],
]

stacks[1] = sys.argv[1:]
stacks[0] = stacks[1].copy()
stacks[0].sort()

stackLEN = len(stacks[0])
for i in range(stackLEN):
	(r, g, b) = colorsys.hsv_to_rgb( i / stackLEN , 1.0, 1.0)
	R, G, B = int(255 * r), int(255 * g), int(255 * b)
	color[stacks[0][i]] = '#%02x%02x%02x' % (R, G, B)

print("stask[0] avt", stacks[0])
print("stask[1] avt", stacks[1])
print("stask[2] avt", stacks[2])
print("color avt", color)

layout = [
	[actions, stack_A, stack_B],
]
window = sg.Window('Push_Swap _ Visualizer', 
                   layout,
                #    default_element_size=(12, 1),
                #    resizable=True
		)

def manip(action):
	if action == "pa" and len(stacks[2]):
		print("pa!")
		tmp = stacks[2].pop(0)
		stacks[1].insert(0, tmp)
	if action == "pb" and len(stacks[1]):	
		print("pb!")
		tmp = stacks[1].pop(0)
		stacks[2].insert(0, tmp)
	if action == "sa" and len(stacks[1]) > 1:
		tmp = stacks[1][0]
		stacks[1][0] = stacks[1][1]
		stacks[1][1] = tmp
	if action == "sb" and len(stacks[2]) > 1:
		tmp = stacks[2][0]
		stacks[2][0] = stacks[2][1]
		stacks[2][1] = tmp
	if action == "ss" and len(stacks[1]) > 1 and len(stacks[2]) > 1:
		tmp = stacks[1][0]
		stacks[1][0] = stacks[1][1]
		stacks[1][1] = tmp
		tmp = stacks[2][0]
		stacks[2][0] = stacks[2][1]
		stacks[2][1] = tmp
	if action == "ra" and len(stacks[1]):
		tmp = stacks[1][0]
		stacks[1].remove(tmp)
		stacks[1].append(tmp)
	if action == "rb" and len(stacks[2]):
		tmp = stacks[2][0]
		stacks[2].remove(tmp)
		stacks[2].append(tmp)
	if action == "rr" and len(stacks[1]) and len(stacks[2]):
		tmp = stacks[1][0]
		stacks[1].remove(tmp)
		stacks[1].append(tmp)
		tmp = stacks[2][0]
		stacks[2].remove(tmp)
		stacks[2].append(tmp)
	if action == "rra" and len(stacks[1]) > 1:
		tmp = stacks[1].pop()
		stacks[1].insert(0, tmp)
	if action == "rrb" and len(stacks[2]) > 1:
		tmp = stacks[2].pop()
		stacks[2].insert(0, tmp)
	if action == "rrr" and len(stacks[1]) > 1 and len(stacks[2]) > 1:
		tmp = stacks[1].pop()
		stacks[1].insert(0, tmp)
		tmp = stacks[2].pop()
		stacks[2].insert(0, tmp)

def drawStack(stack_graph, stack):
	stack_LEN = len(stack)
	for i in range(stack_LEN):
		tl = float(0), STACK_HEIGHT - (i * STACK_HEIGHT / stack_LEN)
		# br = i * STACK_WIDTH / stack_LEN + 1, tl[1] - STACK_HEIGHT / stack_LEN
		br = stacks[0].index(stack[i]) / len(stacks[0]) * STACK_WIDTH + 1, tl[1] - STACK_HEIGHT / stack_LEN
		print("i", i, "color", color[stack[i]])
		stack_graph.DrawRectangle(
			top_left= tl,
			bottom_right= br,
			fill_color=color[stack[i]],
			line_width=0,
		)

while True:
	event, value = window.read(timeout= 10)

	if event == sg.WIN_CLOSED:
		break
# clean canvas
	stack_A.DrawRectangle( (0, STACK_HEIGHT), (STACK_WIDTH, 0), 'black')
	stack_B.DrawRectangle( (0, STACK_HEIGHT), (STACK_WIDTH, 0), 'black')
# draw Stack_A & Stack_B
	drawStack(stack_A, stacks[1])
	drawStack(stack_B, stacks[2])
# Get input to manipulate Stacks
	manip(input("entrer une manip...(sa-sb-rra-ra,etc.)"))

window.close()