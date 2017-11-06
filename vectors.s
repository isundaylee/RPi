vec_table:
vec_reset:
    ldr pc, reset_handler
vec_undef_inst:
    ldr pc, undef_inst_handler
vec_svc:
    ldr pc, svc_handler
vec_prefetch_abort:
    ldr pc, prefetch_abort_handler
vec_data_abort:
    ldr pc, data_abort_handler
vec_reserved:
    ldr pc, reserved_handler
vec_irq:
    ldr pc, irq_handler
vec_fiq:
    ldr pc, fiq_handler

reset_handler:
    .word reset
undef_inst_handler:
    .word reset
svc_handler:
    .word hang
prefetch_abort_handler:
    .word hang
data_abort_handler:
    .word hang
reserved_handler:
    .word hang
irq_handler:
    .word irq
fiq_handler:
    .word hang

reset:
    mov r0, #0x8000
    mov r1, #0x0000

    ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

    msr cpsr_c, #0xD2
    mov sp, #0x8000

    msr cpsr_c, #0xD1
    mov sp, #0x4000

    msr cpsr_c, #0xD3
    mov sp, #0x800000

    b notmain

irq:
    push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    bl intr_entry
    pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    subs pc, lr, #0x4

hang:
    b hang
