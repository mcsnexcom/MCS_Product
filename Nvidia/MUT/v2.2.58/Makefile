SUBARCH := $(shell uname -m | sed -e s/i.86/x86/ -e s/x86_64/x86/ \
				  -e s/sun4u/sparc64/ \
				  -e s/arm.*/arm/ -e s/sa110/arm/ \
				  -e s/s390x/s390/ -e s/parisc64/parisc/ \
				  -e s/ppc.*/powerpc/ -e s/mips.*/mips/ \
				  -e s/sh[234].*/sh/ -e s/aarch64.*/arm64/ )

ARCH		?= $(SUBARCH)

LIB_FOLDER=LIB_x86_64
HEAD_FOLDER=include
BUILD_MCUSRC1=src/demoMCU_AP.c
BUILD_MCUSRC2=src/demoMDI_AP.c
BUILD_MCUSRC3=src/demoG_sensor_AP.c
BUILD_MCUSRC4=src/demoPowerButton.c
BUILD_CANSRC=src/demoCAN_AP.c
BUILD_MCUSRC5=src/demoEvent_AP.c
BUILD_MCUSRC6=src/demoMCU_version.c
CC = gcc
#CC = aarch64-linux-gnu-gcc
CFLAGS = 
#CFLAGS += -DREENTRANT -O1 -w
LIBS += -L ${LIB_FOLDER}
INCLUDES += -I ${HEAD_FOLDER}
#SOURCES  += ${BUILD_SRC}
CFLAGS += -DALL

.PHONY: client clean
	
client:
	${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC1}
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoMCU_AP.o -g -o demoMCU_AP -lMUT -lpthread 
	${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC6}
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoMCU_version.o -g -o demoMCU_version -lMUT -lpthread 
	@cp "${PWD}"/demoMCU_version "${PWD}/bin"
	@cp "${PWD}"/demoMCU_AP "${PWD}/bin"
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC5}
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoEvent_AP.o -g -o demoEvent_AP -lMUT -lpthread 
		@cp "${PWD}"/demoEvent_AP "${PWD}/bin"
    ifeq ($(ARCH),x86_64)
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC2}
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC3}
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC4}
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_MCUSRC6}
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoMDI_AP.o -g -o demoMDI_AP -lMUT -lpthread 
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoPowerButton.o -g -o demoPowerButton -lMUT -lpthread 
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoG_sensor_AP.o -g -o demoG_sensor_AP -lMUT -lpthread 
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoMCU_version.o -g -o demoMCU_version -lMUT -lpthread 
		@cp "${PWD}"/demoMDI_AP "${PWD}/bin"
		@cp "${PWD}"/demoPowerButton "${PWD}/bin"
		@cp "${PWD}"/demoG_sensor_AP "${PWD}/bin"
		${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} ${BUILD_CANSRC}
		${CC} ${CFLAGS} ${INCLUDES} ${LIBS} demoCAN_AP.o -g -o demoCAN_AP -lMUT -lpthread 
		@cp "${PWD}"/demoCAN_AP "${PWD}/bin"
		@cp "${PWD}"/demoMCU_version "${PWD}/bin"
    endif
	
	@echo "build AP based on shared library ..."

clean:
	@# option -f : ignore nonexistent files and arguments, never prompt
	rm -f demoMCU_AP demoMDI_AP demoG_sensor_AP demoPowerButton demoCAN_AP demoMCU_version *.o

test:
	${CC} -c -fPIC -g ${CFLAGS} ${INCLUDES} ${LIBS} src/testdemoG_sensor_AP.c
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} testdemoG_sensor_AP.o -g -o testdemoG_sensor_AP -lMUT -lpthread 
	@cp "${PWD}"/testdemoG_sensor_AP "${PWD}/bin"
	# export LD_LIBRARY_PATH=./LIB_x86_64/
	# ./bin/testdemoG_sensor_AP
