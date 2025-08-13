OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY
{
  flash    (rx)  : ORIGIN = 0x08000000, LENGTH = 1024k
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 128k
}

PROVIDE(_stack_top = ORIGIN(ram) + LENGTH(ram));
ENTRY(Reset_Handler)
SECTIONS
{
    .vector :
    {
        . = ALIGN(4);
        _svector = .;
        KEEP(*(.vectors))
        . = ALIGN(4);
        _evector = .;
    } > flash

    .text :
    {
        . = ALIGN(4);
        _stext = .;
        *(.text .text.*)
        *(.rodata .rodata.*)
        . = ALIGN(4);
        _etext = .;
    } > flash

    .data :
    {
        . = ALIGN(4);
        _srelocate = .;
        *(.data .data.*);
        . = ALIGN(4);
        _erelocate = .;
    } > ram AT > flash

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = . ;
        *(.bss .bss.*)
        . = ALIGN(4);
        _ebss = . ;
    } > ram

    . = ALIGN(4);
    _end = . ;
}
