# OS/2-NMAKE makefile for INFIDX
#
# uses IBM C/C++ Set/2
#

# compiler & flags
CC=icc
CFLAGS=-Wcnd -Wcnv -Wdcl -Weff -Wenu -Word -Wpar -Wpro -Wrea -Wret -Wtrd -Wund -Wuse -Ti -DIBMCPP

# linker & flags (I use the compiler driver here too)
LINK=$(CC)
LINKFLAGS=$(CFLAGS)

# assumptions
# .SUFFIXES is right
# environment variable INCLUDE holds all dirs with the include files
# environment variable LIB     holds all dirs with the lib     files

# basename of the main programm without any suffix
PRG=infidx

# as there is only one C-source-file all other names are made by substituions
SOURCE=$(PRG).c
OBJECTS=$(SOURCE:.c=.obj)
RESOURCE=$(PRG).res
HEADER=$(PRG).h
ICONFILE=$(PRG).ico
MODULDEF=$(PRG).def
MAKEFILE=$(PRG).mak



# rule to compile a c-module in an object file
.c.obj:
        $(CC) $(CFLAGS) -c $<

# rule to compile a resource-script in a binary resource file
.rc.res:
        rc -r $<

# default target (build the program)
all: $(PRG)

# remove all make results but the executable file
clean:
        - del $(OBJECTS) $(RESOURCE) $(PRG)

# remove all make results including the executable file
rasa: CLEAN
        - del $(PRG).exe 

# dependencies

$(OBJECTS): $(SOURCE) $(HEADER) $(MAKEFILE)

$(RESOURCE): $(RESOURCE:.res=.rc) $(HEADER) $(ICONFILE) $(MAKEFILE)


# link objects and lib to .exe
$(PRG).exe: $(OBJECTS)
        $(LINK) $(LINKFLAGS) $(OBJECTS) $(LIBS) $(MODULDEF)

# .exe + .res -> .exe and mark-file
$(PRG): $(PRG).exe $(RESOURCE) $(MODULDEF)
        rc $(PRG).res $(PRG).exe
        touch $(PRG)

