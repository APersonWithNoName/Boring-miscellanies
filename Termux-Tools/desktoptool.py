#!/usr/bin/env python3
# coding=utf-8

import os
import sys
import re

START_ARGS = sys.argv
#RUN_DATA = []

class CommandData:
    def __init__(self):
        self.desktop = "startxfce4"
        self.port = "1"
        self.geometry = "1200x800"
        self.if_novnc = False
        self.depth = "32"
        self.killport = "all"
    def setdesktop(self, _desktop):
        self.desktop = _desktop
    def setport(self, _port):
        self.port = _port
    def setnovnc(self, _if_novnc):
        self.if_novnc = _if_novnc
    def setgeometry(self, _geometry):
        self.geometry = _geometry
    def setdepth(self, _depth):
        self.depth = _depth
    def setkillport(self, _killport):
        self.killport = _killport

RUN_DATA = CommandData()

HELP_INFO = '''
Usage:
    dt [option] [args] ...
'''

def ErrInfo(msg):
    print("\033[031mVncTool_error: \033[0m{}".format(msg))
    sys.exit(-1)

def read_args():
    i = 1
    while i < len(START_ARGS):
        match START_ARGS[i]:
            case "-d" | "--display":
                match START_ARGS[i + 1]:
                    case "x":
                        RUN_DATA.setdesktop("startx")
                    case "kde":
                        RUN_DATA.setdesktop("startplasma-x11")
                    case "xfce" | "xfce4":
                        RUN_DATA.setdesktop("startxfce4")
                    case _:
                        ErrInfo("Unknown display!")
                i += 2
            case "-p" | "--port":
                if START_ARGS[i + 1].isdigit():
                    RUN_DATA.setport(START_ARGS[i + 1])
                else:
                    ErrInfo("The port must be numbers!")
                i += 2
            case "-g" | "--geometry":
                if re.match(r"^\d+x\d+$", RUN_DATA.geometry) != None:
                    RUN_DATA.setgeometry(START_ARGS[i + 1])
                else:
                    ErrInfo("Unknown format!")
                i += 2
            case "-k" | "--kill":
                #if (i + 1) <= len(START_ARGS):
                #    if START_ARGS[i + 1].isdigit():
                #        RUN_DATA.setkillport(START_ARGS[i + 1])
                #        os.system("vncserver -kill {}".format(RUN_DATA.killport))
                #    else:
                #        os.system("vncservet -kill")
                #else:
                #    os.system("vncservet -kill")
                os.system("vncserver -kill")
                os.system("rm -f /tmp/.X11-unix/X* /tmp/.X*-lock")
                sys.exit(0)
            case "--depth" :
                if START_ARGS[i + 1].isdigit():
                    RUN_DATA.setdepth(START_ARGS[i + 1])
                else:
                    ErrInfo("Unknown format!")
                i += 2
            case "-h":
                print(HELP_INFO)
                i += 1
            case _:
                ErrInfo("Unknown command!")
                sys.exit(-1)
            
def main():
    read_args()
    os.system("vncserver :{} -xstartup /usr/bin/{} -geometry {} -depth {}".format(RUN_DATA.port, RUN_DATA.desktop, RUN_DATA.geometry, RUN_DATA.depth))
    
main()
