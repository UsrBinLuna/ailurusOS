.global irq0_stub
.extern timer_handler
.intel_syntax noprefix

irq0_stub:
    push rax
    call timer_handler
    pop rax
    iretq