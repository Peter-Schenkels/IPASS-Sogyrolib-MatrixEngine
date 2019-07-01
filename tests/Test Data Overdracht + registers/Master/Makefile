#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES :=field.cpp object.cpp window.cpp movement.cpp render.cpp physics.cpp

# header files in this project
HEADERS :=l3g4_master.hpp 
# set RELATIVE to the next higher directory 
RELATIVE := ..

# other places to look for files for this project
SEARCH  := $(RELATIVE)/MatrixEngine $(RELATIVE)/Sogyrolib/Master

# and defer to the appropriate Makefile.* there
include $(RELATIVE)/Makefile.due
