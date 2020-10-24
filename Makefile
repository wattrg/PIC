# executable base name
EXE         := PIC

#Compiler and Linker
CC          := g++

#The Target Binary Program
TARGET      := $(EXE)

# debugging mode
DEBUG            := TRUE

# parrallel
OMP := FALSE

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
TARGETDIR   := bin
BUILDDIR    := $(TARGETDIR)/obj
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -Wall 
LIB         := -L$(INCDIR)/lua-5.3.5/src/ -llua -ldl 
INC         := -I$(INCDIR) -I/usr/local/include
INC         += -I$(INCDIR)/lua-5.3.5/src/
INC         += -I$(INCDIR)/LuaBridge/Source/LuaBridge/
INC         += -I$(INCDIR)/LuaBridge/Source/
INCDEP      := -I$(INCDIR)




#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------

# set debugging info
ifeq ($(DEBUG), TRUE)
	CFLAGS   += -g
	TARGET   := $(TARGET)db
	BUILDDIR := $(TARGETDIR)/obj_debug
endif

ifeq ($(OMP), TRUE)
	CFLAGS += -fopenmp
	TARGET := $(TARGET)omp
endif

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: directories $(TARGET)

#Remake
remake: cleaner all


#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB) $(CFLAGS)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp



#Non-File Targets
.PHONY: all remake clean cleaner resources
