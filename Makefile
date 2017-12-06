TARGET = i686-elf

CC  := ${TARGET}-gcc
CXX := ${TARGET}-g++

FLAGS    := -g -O3 -fno-omit-frame-pointer
ASMFLAGS := $(FLAGS)
CFLAGS   := $(FLAGS) -std=gnu11
CXXFLAGS := $(FLAGS) -std=gnu++11

ASM_SRCS := $(filter-out %.inc.s,$(wildcard src/*.s))
C_SRCS   := $(filter-out %.inc.c,$(wildcard src/*.c))
CXX_SRCS := $(filter-out %.inc.cc,$(wildcard src/*.cc))

SRCS := $(ASM_SRCS) $(C_SRCS) $(CXX_SRCS)
OBJS := $(patsubst src/%.s,obj/%.o,$(ASM_SRCS)) $(patsubst src/%.c,obj/%.o,$(C_SRCS)) $(patsubst src/%.cc,obj/%.o,$(CXX_SRCS))

CRTI_OBJ:=obj/crti.o
CRTBEGIN_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=obj/crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(filter-out ${CRTI_OBJ} ${CRTN_OBJ},$(OBJS)) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: all clean

all: frxos.elf

print:
	@echo "ASM_SRCS=" $(ASM_SRCS)
	@echo "C_SRCS=  " $(C_SRCS)
	@echo "CXX_SRCS=" $(CXX_SRCS)

clean:
	@rm -f frxos.elf $(OBJS) $(wildcard src/*.d)

frxos.elf: linker.ld $(OBJ_LINK_LIST)
	$(CC) -ffreestanding -nostdlib -T linker.ld $(OBJ_LINK_LIST) -o $@ -lgcc

obj/%.o: src/%.s
	@mkdir -p obj
	${CC} -ffreestanding ${CFLAGS} -MMD -MF $(patsubst %.s,%.d,$<) -c $< -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	${CC} -ffreestanding ${CFLAGS} -MMD -MF $(patsubst %.c,%.d,$<) -c $< -o $@

obj/%.o: src/%.cc
	@mkdir -p obj
	${CXX} -ffreestanding ${CFLAGS} -MMD -MF $(patsubst %.cc,%.d,$<) -c $< -o $@

-include src/*.d
