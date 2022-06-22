#!/usr/bin/python3
import PySimpleGUI as sg
import colorsys
import sys

STACK_WIDTH = 400
STACK_HEIGHT = 800
moreinput = True
readSpeed = 1
reading = False
actions = []
stacks = [[], [], []]
color = {}

sg.theme('DarkBlue6')
stack_A = sg.Graph(
	canvas_size = (STACK_WIDTH, STACK_HEIGHT),
	graph_bottom_left = (0,0),
	graph_top_right = (STACK_WIDTH, STACK_HEIGHT),
	expand_x=True,
	expand_y=True,
	background_color = 'black',
	key='-STACK_A-'
)
stack_B = sg.Graph(
	canvas_size = (STACK_WIDTH, STACK_HEIGHT),
	graph_bottom_left = (0, 0),
	graph_top_right = (STACK_WIDTH , STACK_HEIGHT),
	expand_x=True,
	expand_y=True,
	background_color = 'black',
	key='-STACK_B-'
)
actionsTable = sg.Table(
	# max_col_width="5",
	# col_widths="5",
	display_row_numbers=True,
	# justification='right',
	background_color = 'black',
	headings=["Actions"],
	values=actions,
	expand_x=True,
	expand_y=True,
	key='-ACTIONSTABLE-'
	)

boutons = 	[
	[	
		sg.Button('<<', key='-RW_BTN-'),
		sg.Button('Play/Pause', key='-PLAY_BTN-'),
		sg.Button('>>', key='-FD_BTN-'),
		sg.Text("Speed >> x"),
		sg.Spin([1, 2, 3, 4, 5, 10, 20, 30, 40, 50], key='-SPIN-', enable_events = True)
	],
	[sg.Slider(
		range=(int(0),len(sys.argv) - 1),
		default_value=0,
		size=(30,15),
		orientation='horizontal',
		font=('Helvetica', 12),
		key='-SLIDER-',
		expand_x=True,
		enable_events = True
		)
	],
]

stacks[1] = [int(numeric_string) for numeric_string in sys.argv[1:]]
stacks[0] = stacks[1].copy()
stacks[0].sort()

stackLEN = len(stacks[0])
for i in range(stackLEN):
	(r, g, b) = colorsys.hsv_to_rgb( i / stackLEN , 1.0, 1.0)
	R, G, B = int(255 * r), int(255 * g), int(255 * b)
	color[stacks[0][i]] = '#%02x%02x%02x' % (R, G, B)

layout = [
	[boutons],
	[stack_A, stack_B, actionsTable],
]
window = sg.Window('Push_Swap _ Visualizer', 
                   layout,
                #    default_element_size=(12, 1),
                   resizable=True
		)

def manip(action):
	# print(action)
	if action == "pa" and len(stacks[2]):
		tmp = stacks[2].pop(0)
		stacks[1].insert(0, tmp)
	if action == "pb" and len(stacks[1]):	
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
	# clean canvas
	stack_graph.DrawRectangle( (0, STACK_HEIGHT), (STACK_WIDTH, 0), 'black')
	stack_LEN = len(stack)
	for i in range(stack_LEN):
		tl = float(0), STACK_HEIGHT - (i * STACK_HEIGHT / stack_LEN)
		br = stacks[0].index(stack[i]) / len(stacks[0]) * STACK_WIDTH + 5, tl[1] - STACK_HEIGHT / stack_LEN
		stack_graph.DrawRectangle(
			top_left= tl,
			bottom_right= br,
			fill_color=color[stack[i]],
			line_width=0,
		)

def refreshStackState(valueAddedToSlider):
		values["-SLIDER-"] += valueAddedToSlider
		window["-SLIDER-"].update(values["-SLIDER-"])
		window['-ACTIONSTABLE-'].set_vscroll_position(values["-SLIDER-"]/ len(actions))
# Get input to manipulate Stacks
window.read(timeout=1)
window.bind('<Configure>',"Event")
try:
	while str != '':
		str = input() #input("entrer une manip...")
		if str != '':
			actions.append([str])
			manip(str)
		else:
			window['-SLIDER-'].update(range=(0, len(actions)), value = len(actions))
			window['-ACTIONSTABLE-'].update(actions)
			moreinput = False
except EOFError as e:
	print("EOF reached")
	window['-SLIDER-'].update(range=(0, len(actions)), value = len(actions))
	window['-ACTIONSTABLE-'].update(actions)
	moreinput = False
	pass

while True:
	event, values = window.read(timeout= (1000 / readSpeed)) #timeout= 10

	if event == sg.WIN_CLOSED:
		break
	# if event == "Event": # On commençait à faire l'ajustement des elem au rezide de la fenetre... :
		# print(window.size)
		# window["-STACK_A-"].update(silent_on_error=True,  window.size)
		# window["-STACK_B-"].update(window.size)
	if event == '-SPIN-': # Ajuste la vitesse de lecture
		readSpeed = values["-SPIN-"]
		print("readSpeed x", readSpeed)
	if event == '-SLIDER-':
		stacks[1] = [int(numeric_string) for numeric_string in sys.argv[1:]]
		stacks[2].clear()
		window['-ACTIONSTABLE-'].set_vscroll_position(values["-SLIDER-"]/ len(actions))
		for i in range(int(values["-SLIDER-"])):
			manip(actions[i][0])
	if event == '-RW_BTN-':
		stacks[1] = [int(numeric_string) for numeric_string in sys.argv[1:]]
		stacks[2].clear()
		refreshStackState(-1)
		for i in range(int(values["-SLIDER-"])):
			manip(actions[i][0])
	if event == '-FD_BTN-':
		if values["-SLIDER-"] + 1 > len(actions):
			continue
		stacks[1] = [int(numeric_string) for numeric_string in sys.argv[1:]]
		stacks[2].clear()
		refreshStackState(1)
		for i in range(int(values["-SLIDER-"])):
			manip(actions[i][0])
	if event == '-PLAY_BTN-':
		reading = not reading
	if reading and values["-SLIDER-"] != len(actions):
		manip(actions[int(values["-SLIDER-"])][0])
		refreshStackState(1)
# draw Stack_A & Stack_B
	drawStack(stack_A, stacks[1])
	drawStack(stack_B, stacks[2])

window.close()