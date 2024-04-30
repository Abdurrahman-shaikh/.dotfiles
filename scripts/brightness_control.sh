#!/bin/bash

# Get current brightness level
current_brightness=$(cat /sys/class/backlight/*/brightness)

# Define brightness adjustment value
brightness_adjustment=10 # Adjust as needed

# Check which key was pressed and adjust brightness accordingly
case "$1" in
"down")
	new_brightness=$((current_brightness - brightness_adjustment))
	;;
"up")
	new_brightness=$((current_brightness + brightness_adjustment))
	;;
*)
	echo "Usage: $0 [down|up]"
	exit 1
	;;
esac

# Check if new brightness level is within the valid range (0 to 265)
if ((new_brightness >= 0 && new_brightness <= 265)); then
	# Set new brightness level
	echo "$new_brightness" | sudo tee /sys/class/backlight/*/brightness >/dev/null
	echo "Brightness set to $new_brightness"
else
	echo "Invalid brightness level. Please specify a value between 0 and 265"
fi
