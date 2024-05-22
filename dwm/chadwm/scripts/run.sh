#!/bin/sh

xrdb merge ~/.Xresources 
xbacklight -set 10 &feh --bg-fill ~/.config/.dotfiles/wallpapers/10.png &
feh --bg-fill ~/.config/.dotfiles/wallpapers/8.png &
picom &

dash ~/.config/chadwm/scripts/bar.sh &
while type chadwm >/dev/null; do chadwm && continue || break; done
