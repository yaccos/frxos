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
OBJS := $(patsubst src/%.s,obj/%.asm.o,$(ASM_SRCS)) $(patsubst src/%.c,obj/%.o,$(C_SRCS)) $(patsubst src/%.cc,obj/%.o,$(CXX_SRCS))

CRTI_OBJ:=obj/crti.asm.o
CRTBEGIN_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell ${CC} $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ:=obj/crtn.asm.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(filter-out ${CRTI_OBJ} ${CRTN_OBJ},$(OBJS)) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: all clean

all: frxos.iso

print:
	@echo "ASM_SRCS=" $(ASM_SRCS)
	@echo "C_SRCS=  " $(C_SRCS)
	@echo "CXX_SRCS=" $(CXX_SRCS)

clean:
	@rm -f frxos.elf $(OBJS) $(wildcard obj/*.d)
	@rm -rf obj isodir

frxos.iso: frxos.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp frxos.elf isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o $@ isodir

frxos.elf: linker.ld $(OBJ_LINK_LIST)
	$(CC) -ffreestanding -nostdlib -T linker.ld $(OBJ_LINK_LIST) -o $@ -lgcc

obj/%.asm.o: src/%.s
	@mkdir -p obj
	${CC} -ffreestanding ${CFLAGS} -MMD -MF $(patsubst %.o,%.d,$@) -c $< -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	${CC} -ffreestanding ${CFLAGS} -MMD -MF $(patsubst %.o,%.d,$@) -c $< -o $@

obj/%.o: src/%.cc
	@mkdir -p obj
	${CXX} -ffreestanding ${CXXFLAGS} -MMD -MF $(patsubst %.o,%.d,$@) -c $< -o $@

-include obj/*.d
