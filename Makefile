TARGET = i686-elf

CC  := ${TARGET}-gcc
CXX := ${TARGET}-g++

FLAGS    := -g -O3 -fno-omit-frame-pointer
ASMFLAGS := $(FLAGS)
CFLAGS   := $(FLAGS) -std=gnu11
CXXFLAGS := $(FLAGS) -std=gnu++11

ASM_SRCS := $(wildcard src/*.s)
C_SRCS   := $(wildcard src/*.c)
CXX_SRCS := $(wildcard src/*.cc)

SRCS := $(ASM_SRCS) $(C_SRCS) $(CXX_SRCS)
OBJS := $(patsubst src/%.s,%.o,$(ASM_SRCS)) $(patsubst src/%.c,%.o,$(C_SRCS)) $(patsubst src/%.cc,%.o,$(CXX_SRCS))

CRTI_OBJ:=crti.o
CRTBEGIN_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(filter-out ${CRTI_OBJ} ${CRTN_OBJ},$(OBJS)) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: all clean depend

all: frxos.elf depend

clean:
	@rm -f frxos.elf $(OBJS) .depend

depend: .depend
.depend: $(SRCS)
	@rm -f ./.depend
	@$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;
-include .depend

frxos.elf: depend linker.ld $(OBJ_LINK_LIST)
	$(CC) -ffreestanding -nostdlib -T linker.ld $(OBJ_LINK_LIST) -o $@ -lgcc

%.o: src/%.s
	${CC} -ffreestanding ${CFLAGS} -c $< -o $@

%.o: src/%.c
	${CC} -ffreestanding ${CFLAGS} -c $< -o $@

%.o: src/%.cc
	${CXX} -ffreestanding ${CFLAGS} -c $< -o $@

