NAME				=	berry-spi

#
#	INI directories
#
PHP_MAJOR_VERSION  := $(shell php -v | grep -i 'PHP [57]' | sed s/'PHP '//g | cut -c1-1)
PHP_SUB_VERSION    := $(shell php -v | grep -i 'PHP [57]' | cut -c1-8 | sed s/'PHP '//g | cut -c1-3)

ifeq (${PHP_MAJOR_VERSION}, 7)
    INI_DIR     :=   /etc/php/${PHP_SUB_VERSION}/mods-available/
else
    INI_DIR     :=   /etc/php5/mods-available/
endif

#
#	The extension dirs
#

EXTENSION_DIR		=	$(shell php-config --extension-dir)


#
#	The include dirs
#

INCLUDE_DIR			=	$(shell php-config --include-dir)


#
#	The name of the extension and the name of the .ini file
#

EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini


#
#	Compiler
#

COMPILER			=	g++
LINKER				=	g++


#
#	Compiler and linker flags
#

COMPILER_FLAGS		=	-Wall -I${INCLUDE_DIR} -I${INCLUDE_DIR}/main -I${INCLUDE_DIR}/Zend -I${INCLUDE_DIR}/TSRM -c -O2 -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared
LINKER_DEPENDENCIES	=	-lpigpio -lphpcpp


#
#	Command to remove files, copy files and create directories.
#

RM					=	rm -f
CP					=	cp -f
MKDIR				=	mkdir -p


#
#	All source files are simply all *.cpp files found in the current directory
#

SOURCES				=	$(wildcard src/*.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)


#
#	From here the build instructions start
#

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR}
				
clean:
						${RM} ${EXTENSION} ${OBJECTS}

