MEMORY
{
    rom (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

EXTERN(vector_table);
ENTRY(reset_handler);

SECTIONS
{
    .text : {
        *(.vectors)
        *(.text*)
        . = ALIGN(4);
    } >rom
}
