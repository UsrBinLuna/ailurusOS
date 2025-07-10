void exception_handler() {
    __asm__ volatile ("cli; hlt"); // hang
}