import curses
import paths
import math
import curses.wrapper
from paths import *

W = 119
S = 115
A = 97
D = 100

I = 105
K = 107
J = 108
L = 106

ESC = 27

increment = paths.increment
decrement = paths.decrement

file = open("matt.txt",'w')


class CursesController:
    def __init__(self,vehicle):
        self.stdscr = curses.initscr()
        self.vehicle = vehicle
        self.thrusters = vehicle.thrusters
        curses.noecho()    #Dont show keypresses
        curses.cbreak()    #Allow instantaneous Key Processing
        self.stdscr.keypad(1)    #Enable the keypad
        
    def print_string(self,x,y,str,mode):
        self.stdscr.addstr(x,y,str,mode)
        
    def print_thrusters(self,thrusters):
        self.print_string(2,10,"Fore: " + str((thrusters[0].power*100)),curses.A_STANDOUT)
        self.print_string(22,10,"Aft: " + str((thrusters[1].power*100)),curses.A_STANDOUT)
        self.print_string(11,30,"Starboard: " + str((thrusters[2].power*100)),curses.A_STANDOUT)
        self.print_string(11,0,"Port: " + str((thrusters[3].power*100)),curses.A_STANDOUT)
        
    def run(self):
        quit = 0
        self.print_string(0,0,"Thruster Information",curses.A_UNDERLINE)
        self.print_thrusters(self.thrusters)
        depth = self.vehicle.depth()
        self.print_string(8,57,"Depth",curses.A_REVERSE)
        self.print_string(9,60,str(depth),curses.A_BOLD)
        while(quit != 1):
            char = self.stdscr.getch()
            quit = self.handle_input(char)
            self.print_thrusters(self.thrusters)
            self.print_string(0,0,"Thruster Information",curses.A_UNDERLINE)
            depth = self.vehicle.depth()
            self.print_string(8,57,"Depth",curses.A_REVERSE)
            self.print_string(9,60,str(depth),curses.A_BOLD)
        self.close()
            
                
    def handle_input(self,c):
        if c == ESC:
                return 1
        elif c == W:
            self.thrusters[aft].power_up(increment)
	    self.vehicle.update_thruster(self.thrusters[aft])
        elif c == S:
            self.thrusters[aft].power_up(decrement)
	    self.vehicle.update_thruster(self.thrusters[aft])
        elif c == A:
            self.thrusters[port].power_up(increment)
	    self.vehicle.update_thruster(self.thrusters[port])
        elif c == D:
            self.thrusters[port].power_up(decrement)
	    self.vehicle.update_thruster(self.thrusters[port])
        elif c == I:
            self.thrusters[fore].power_up(increment)
	    self.vehicle.update_thruster(self.thrusters[fore])
        elif c == K:
            self.thrusters[fore].power_up(decrement)
	    self.vehicle.update_thruster(self.thrusters[fore])
        elif c == J:
            self.thrusters[starboard].power_up(increment)
   	    self.vehicle.update_thruster(self.thrusters[starboard])
        elif c == L:
            self.thrusters[starboard].power_up(decrement)
	    self.vehicle.update_thruster(self.thrusters[starboard])
        return 0
            
    def close(self):
        curses.nocbreak()
        self.stdscr.keypad(0)
        curses.echo()
        curses.endwin()