#ifndef MENUSTUFF_H
#define MENUSTUFF_H
typedef enum cool_idle_animations {
	spinning_line,
	flashing_box,
	fading_box,
	up_wipe,
	down_wipe,
	left_wipe,
	right_wipe,
	clockwise_spin,
	counterclockwise_spin
} idle_types;
//Awesome idle animations
void animate_idle(idle_types idle_type, int delay);
#endif
