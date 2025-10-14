LIB_FOLDER=LIB_x86_64
HEAD_FOLDER=include
#BUILD_SRC=src/mcu_service.c

#CC = aarch64-linux-gnu-gcc
CC = gcc
CFLAGS += -DREENTRANT -O1 -w
LIBS = -L ${LIB_FOLDER}
INCLUDES += -I ${HEAD_FOLDER}
#SOURCES  += ${BUILD_SRC}

.PHONY: service-A service-M service-C service mcu_ap-A mcu_ap-M mcu_ap-C mcu_ap mcu_menu_ap-A mcu_menu_ap-M mcu_menu_ap-C mcu_menu_ap mcu_upd-A mcu_upd-M mcu_upd-C mcu_upd clean

service-A: CFLAGS += -DALL
service-A: service

service-M: CFLAGS += -DMCU
service-M: service

service-C: CFLAGS += -DCAN
service-C: service

service:
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_service.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_service.o -g -o mcu_service -lMCU -lGenericMCU -lUART -lpthread
	@cp "${PWD}"/mcu_service "${PWD}/bin"
	@echo "build service based on shared library ..."

mcu_ap-A: CFLAGS += -DALL
mcu_ap-A: mcu_ap

mcu_ap-M: CFLAGS += -DMCU
mcu_ap-M: mcu_ap

mcu_ap-C: CFLAGS += -DCAN
mcu_ap-C: mcu_ap

mcu_ap:
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_ap.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_ap.o -g -o mcu_ap -lMCU -lGenericMCU -lUART -lpthread
	@cp "${PWD}"/mcu_ap "${PWD}/bin"
	@echo "build AP based on shared library ..."
	
mcu_menu_ap-A: CFLAGS += -DALL
mcu_menu_ap-A: mcu_menu_ap

mcu_menu_ap-M: CFLAGS += -DMCU
mcu_menu_ap-M: mcu_menu_ap

mcu_menu_ap-C: CFLAGS += -DCAN
mcu_menu_ap-C: mcu_menu_ap

mcu_menu_ap:
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_menu_ap.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_menu_ap.o -g -o mcu_menu_ap -lMCU -lGenericMCU -lAP_MENU -lUART -lpthread
	@cp "${PWD}"/mcu_menu_ap "${PWD}/bin"
	@echo "build MENU AP based on shared library ..."

mcu_upd-M: CFLAGS += -DMCU
mcu_upd-M: mcu_upd

mcu_upd-C: CFLAGS += -DCAN
mcu_upd-C: mcu_upd

mcu_upd:
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_update.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_get_NVRAM.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_update.o -g -o mcu_upd -lMCU -lGenericMCU -lUART -lpthread
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_get_NVRAM.o -g -o mcu_get_NVRAM -lMCU -lGenericMCU -lUART -lpthread
	@cp "${PWD}"/mcu_upd "${PWD}/bin"
	@cp "${PWD}"/mcu_get_NVRAM "${PWD}/bin"
	@echo "build update AP based on shared library ..."
		


mcu_system_cmd-A: CFLAGS += -DALL
mcu_system_cmd-A: mcu_system_cmd

mcu_system_cmd-M: CFLAGS += -DMCU
mcu_system_cmd-M: mcu_system_cmd

mcu_system_cmd-C: CFLAGS += -DCAN
mcu_system_cmd-C: mcu_system_cmd

mcu_system_cmd:
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c -fPIC src/mcu_system_cmd.c -g
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} mcu_system_cmd.o -g -o mcu_system_cmd -lMCU -lGenericMCU -lUART -lpthread
	@cp "${PWD}"/mcu_system_cmd "${PWD}/bin"
	@echo "build AP based on shared library ..."

clean:
	@# option -f : ignore nonexistent files and arguments, never prompt
	rm -f mcu_service mcu_menu_ap mcu_ap mcu_upd mcu_get_NVRAM mcu_system_cmd *.o *.so
