extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL1 0x20200004
#define GPFSEL2 0x20200008
#define GPFSEL3 0x2020000C
#define GPFSEL4 0x20200010
#define GPSET0  0x2020001C
#define GPSET1  0x20200020
#define GPCLR0  0x20200028
#define GPCLR1  0x2020002C

int notmain ( void )
{
    unsigned int ra;

    ra=GET32(GPFSEL1);
    ra&=~(7<<6);
    ra|=1<<6;
    PUT32(GPFSEL1,ra);

    while(1)
    {
        PUT32(GPSET0,1<<12);
        for (int i=0; i<50; i++) dummy(ra);
        PUT32(GPCLR0,1<<12);
        for (int i=0; i<50; i++) dummy(ra);
    }

    return(0);
}
