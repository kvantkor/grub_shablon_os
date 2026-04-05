#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>

// Структура состояния процессора при прерывании
typedef struct {
    uint32_t ds;                                     // Сегмент данных
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushad
    uint32_t int_no, err_code;                       // push byte X
    uint32_t eip, cs, eflags, useresp, ss;           // Автоматически процессором
} registers_t;

// Прототипы функций ввода-вывода
extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);
extern void io_wait(void);

// Обработчик, вызываемый из ассемблера
void exception_handler(registers_t *regs) {
    if (regs->int_no == 32) {
        // Таймер: шлем EOI
        outb(0x20, 0x20);
    } else {
        // Ошибка (например, 0 - деление на ноль)
        // Тут можно вывести "Kernel Panic"
    }
}

// 8-бит (стандарт: контроллеры, клавиатура, таймер)
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

// 16-бит (часто: ATA/IDE диски, старые сетевухи)
void outw(uint16_t port, uint16_t val);
uint16_t inw(uint16_t port);

// 32-бит (часто: шина PCI, современные контроллеры)
void outl(uint16_t port, uint32_t val);
uint32_t inl(uint16_t port);

// Пауза для медленных портов (запись в "пустой" порт 0x80)
static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif
