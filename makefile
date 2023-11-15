SRC_DIR := src
OBJ_DIR := obj
DLL_DIR := dll
OUT_DIR := bin
OUT_STATIC_DIR := bin/static
#BASELIB_STATIC_DIR := ../BaseLib/bin

current_path := $(shell pwd)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
REM_FILES := $(wildcard $(OBJ_DIR)/*.o) $(wildcard $(OBJ_DIR)/*/*.o) $(wildcard $(OBJ_DIR)/*/*/*.o) $(wildcard $(OBJ_DIR)/*/*/*/*.o)
DLL_FILES := $(wildcard $(DLL_DIR)/*.dll)

# create sub dir structure to create it in the ../obj directory
DIR_STRUCTUR := $(sort $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.cpp,$(SRC_FILES)))

DIRS := $(sort $(dir $(DIR_STRUCTUR)))


LDFLAGS := -ggdb -pthread 
CPPFLAGS := -ggdb -pthread -O0

CXXFLAGS := _DEBUG 

LIBRARIES := -lstdc++fs -ldl -lpthread -lm -laudiohelper #link libraries
LIB_FOLDER_STATIC := ../audio/bin/static
LIB_INCLUDE := 

.PHONY: touch src/main.cpp clean


all_debug: create_dirs createAudiolib_debug main.run 

new: create_dirs clean main.run 

Debug_Main: clean create_dirs debugBuild_Insert main.run 
Debug_Main_noClean: create_dirs debugBuild_Insert main.run 
Realse_Static: clean createAudiolib_release_static create_dirs releaseBuild static_main.run 

# create static BaseLib library			
createAudiolib_release_static:
	$(MAKE) -C ../audiohelper release_static

createAudiolib_debug:
	$(MAKE) -C ../audiohelper debug_shared


## set compiler flags for release #CPPFLAGS := $(CPPFLAGS) -O2 
releaseBuild:
	make CPPFLAGS="-ggdb -pthread -O2"
	$(info --RELEASE-- compile with $(CXXFLAGS) and $(CPPFLAGS))

## set DEFINES inserts for debug build
debugBuild_Insert:
#	make CPPFLAGS="-ggdb -pthread -O0 -D$(CXXFLAGS)"
#	make CPPFLAGS="-ggdb -pthread -O0 -D_DEBUG"
	$(info --DEBUG-- compile with $(CPPFLAGS))

# link with static library ------------------------
#static_main.run: $(OBJ_STATIC_FILES)
static_main.run: $(OBJ_FILES)
	$(info ---- link static with $(LDFLAGS))
	g++ $(LDFLAGS) -static -o $(OUT_STATIC_DIR)/$@ $^ -L$(LIB_FOLDER_STATIC) $(LIBRARIES)
	cp $(OUT_STATIC_DIR)/$@ ../cernelio/glass/raytrace_binary/main.run
	

# shared library -----------------------------------
main.run: $(OBJ_FILES)
	$(info ---- link with $(LDFLAGS))
	g++ $(LDFLAGS) -o $(OUT_DIR)/$@ $^ $(LIBRARIES)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -D$(CXXFLAGS) -c -o $@ $< $(LIBRARIES)

#	$(info ---- compile with $(CPPFLAGS) and $(CXXFLAGS))
#	g++ $(CPPFLAGS) -D$(CXXFLAGS) -c -o $@ $< $(LIBRARIES)
# $(info ---- compile with $(CPPFLAGS) and $(DEBUG_INSERT_DEFINES))
# g++ $(CPPFLAGS) $(DEBUG_INSERT_DEFINES) -c -o $@ $< $(LIBRARIES)  <-- WARUM GEHT DAS NICHT ??

# remove all previously generated files	
clean:
	$(info ---- clean)
ifneq ($(REM_FILES),)
	$(info ---- remove files $(REM_FILES))
	-rm $(REM_FILES)
else
	@echo 'Nothing to clean!'
endif

# create sub dir structure to create it in the ../obj directory			
create_dirs:
	$(info ---- create_dirs)

	@echo 'create dirs: $(DIRS)' 

ifneq ($(DIRS),)
	mkdir $(DIRS) -p	
	mkdir $(OUT_STATIC_DIR) -p
	mkdir $(OUT_DIR) -p
	mkdir $(OBJ_DIR) -p
	@echo '.' 		
else
    # VARIABLE is not empty
	@echo 'no dirs' 
endif


#Automatic Variables

#Automatic variables are set by make after a rule is matched. There include:

# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.
# '%' matches filename.


# g++: [infile -> $^] for linking
# -m64[Generate code for a 32-bit or 64-bit environment.] 
# -ggdb[Produce debugging information for use by GDB .] 
# -DNAME defines a NAME like in .h
# -shared[Produce a shared object which can then be linked with other objects to form an executable.] 
# -static links libs statically
# -o [outfilename]
# -l [Search the library named library when linking.]

# g++: [infile -> $<] for compiling
# -Wall[enables all the warnings] 
# -ansi[Specify the standard to which the code should conform] 
# -DNAME defines a NAME like in .h
# -static links libs statically
# -pthread[Add support for multithreading using the POSIX threads library] 
# -std=c++0x[The working draft of the upcoming ISO C ++ 0x standard. This option enables experimental features that are likely to be included in C ++ 0x.] 
# -c [no linking] 
# -o [outfilename]	
# -O2 optimization flag for a faster code you may also try -O3 or -Ofast
# -D adds a define into the code like #define A_DEFINE_VALUE for usage with  #ifdef A_DEFINE_VALUE