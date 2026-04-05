# Настройки компилятора
CC = gcc
AS = nasm
LD = ld

# Флаги: 32 бита, без стандартных библиотек C, без стековых проверок
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -nostdlib
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# Файлы проекта
OBJ = kernel.o main.o

all: my_os.bin

# Сборка бинарника
my_os.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o my_os.bin $(OBJ)

# Компиляция C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция ASM
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Очистка
clean:
	rm -f *.o my_os.bin

# Быстрая проверка в QEMU
run: my_os.bin
	qemu-system-i386 -kernel my_os.bin
