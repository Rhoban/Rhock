#include <stdio.h>
#include <stdlib.h>
#include "native.h"
#include "config.h"

uint8_t rhock_native_nop(struct rhock_context *context, uint8_t op, uint32_t elapsed)
{
    return RHOCK_NATIVE_CONTINUE;
}


#ifdef RHOCK_NATIVE_MAX_16
#define RHOCK_NATIVE_MAX 16
extern rhock_native rhock_native0 __attribute__((weak));
rhock_native rhock_native0 = rhock_native_nop;
extern rhock_native rhock_native1 __attribute__((weak));
rhock_native rhock_native1 = rhock_native_nop;
extern rhock_native rhock_native2 __attribute__((weak));
rhock_native rhock_native2 = rhock_native_nop;
extern rhock_native rhock_native3 __attribute__((weak));
rhock_native rhock_native3 = rhock_native_nop;
extern rhock_native rhock_native4 __attribute__((weak));
rhock_native rhock_native4 = rhock_native_nop;
extern rhock_native rhock_native5 __attribute__((weak));
rhock_native rhock_native5 = rhock_native_nop;
extern rhock_native rhock_native6 __attribute__((weak));
rhock_native rhock_native6 = rhock_native_nop;
extern rhock_native rhock_native7 __attribute__((weak));
rhock_native rhock_native7 = rhock_native_nop;
extern rhock_native rhock_native8 __attribute__((weak));
rhock_native rhock_native8 = rhock_native_nop;
extern rhock_native rhock_native9 __attribute__((weak));
rhock_native rhock_native9 = rhock_native_nop;
extern rhock_native rhock_native10 __attribute__((weak));
rhock_native rhock_native10 = rhock_native_nop;
extern rhock_native rhock_native11 __attribute__((weak));
rhock_native rhock_native11 = rhock_native_nop;
extern rhock_native rhock_native12 __attribute__((weak));
rhock_native rhock_native12 = rhock_native_nop;
extern rhock_native rhock_native13 __attribute__((weak));
rhock_native rhock_native13 = rhock_native_nop;
extern rhock_native rhock_native14 __attribute__((weak));
rhock_native rhock_native14 = rhock_native_nop;
extern rhock_native rhock_native15 __attribute__((weak));
rhock_native rhock_native15 = rhock_native_nop;
rhock_native rhock_native_get(uint8_t id)
{
switch (id) {
case 0:
return rhock_native0;
case 1:
return rhock_native1;
case 2:
return rhock_native2;
case 3:
return rhock_native3;
case 4:
return rhock_native4;
case 5:
return rhock_native5;
case 6:
return rhock_native6;
case 7:
return rhock_native7;
case 8:
return rhock_native8;
case 9:
return rhock_native9;
case 10:
return rhock_native10;
case 11:
return rhock_native11;
case 12:
return rhock_native12;
case 13:
return rhock_native13;
case 14:
return rhock_native14;
case 15:
return rhock_native15;
default:
return NULL;
}
};
#endif

#ifdef RHOCK_NATIVE_MAX_32
#define RHOCK_NATIVE_MAX 32
extern rhock_native rhock_native0 __attribute__((weak));
rhock_native rhock_native0 = rhock_native_nop;
extern rhock_native rhock_native1 __attribute__((weak));
rhock_native rhock_native1 = rhock_native_nop;
extern rhock_native rhock_native2 __attribute__((weak));
rhock_native rhock_native2 = rhock_native_nop;
extern rhock_native rhock_native3 __attribute__((weak));
rhock_native rhock_native3 = rhock_native_nop;
extern rhock_native rhock_native4 __attribute__((weak));
rhock_native rhock_native4 = rhock_native_nop;
extern rhock_native rhock_native5 __attribute__((weak));
rhock_native rhock_native5 = rhock_native_nop;
extern rhock_native rhock_native6 __attribute__((weak));
rhock_native rhock_native6 = rhock_native_nop;
extern rhock_native rhock_native7 __attribute__((weak));
rhock_native rhock_native7 = rhock_native_nop;
extern rhock_native rhock_native8 __attribute__((weak));
rhock_native rhock_native8 = rhock_native_nop;
extern rhock_native rhock_native9 __attribute__((weak));
rhock_native rhock_native9 = rhock_native_nop;
extern rhock_native rhock_native10 __attribute__((weak));
rhock_native rhock_native10 = rhock_native_nop;
extern rhock_native rhock_native11 __attribute__((weak));
rhock_native rhock_native11 = rhock_native_nop;
extern rhock_native rhock_native12 __attribute__((weak));
rhock_native rhock_native12 = rhock_native_nop;
extern rhock_native rhock_native13 __attribute__((weak));
rhock_native rhock_native13 = rhock_native_nop;
extern rhock_native rhock_native14 __attribute__((weak));
rhock_native rhock_native14 = rhock_native_nop;
extern rhock_native rhock_native15 __attribute__((weak));
rhock_native rhock_native15 = rhock_native_nop;
extern rhock_native rhock_native16 __attribute__((weak));
rhock_native rhock_native16 = rhock_native_nop;
extern rhock_native rhock_native17 __attribute__((weak));
rhock_native rhock_native17 = rhock_native_nop;
extern rhock_native rhock_native18 __attribute__((weak));
rhock_native rhock_native18 = rhock_native_nop;
extern rhock_native rhock_native19 __attribute__((weak));
rhock_native rhock_native19 = rhock_native_nop;
extern rhock_native rhock_native20 __attribute__((weak));
rhock_native rhock_native20 = rhock_native_nop;
extern rhock_native rhock_native21 __attribute__((weak));
rhock_native rhock_native21 = rhock_native_nop;
extern rhock_native rhock_native22 __attribute__((weak));
rhock_native rhock_native22 = rhock_native_nop;
extern rhock_native rhock_native23 __attribute__((weak));
rhock_native rhock_native23 = rhock_native_nop;
extern rhock_native rhock_native24 __attribute__((weak));
rhock_native rhock_native24 = rhock_native_nop;
extern rhock_native rhock_native25 __attribute__((weak));
rhock_native rhock_native25 = rhock_native_nop;
extern rhock_native rhock_native26 __attribute__((weak));
rhock_native rhock_native26 = rhock_native_nop;
extern rhock_native rhock_native27 __attribute__((weak));
rhock_native rhock_native27 = rhock_native_nop;
extern rhock_native rhock_native28 __attribute__((weak));
rhock_native rhock_native28 = rhock_native_nop;
extern rhock_native rhock_native29 __attribute__((weak));
rhock_native rhock_native29 = rhock_native_nop;
extern rhock_native rhock_native30 __attribute__((weak));
rhock_native rhock_native30 = rhock_native_nop;
extern rhock_native rhock_native31 __attribute__((weak));
rhock_native rhock_native31 = rhock_native_nop;
rhock_native rhock_native_get(uint8_t id)
{
switch (id) {
case 0:
return rhock_native0;
case 1:
return rhock_native1;
case 2:
return rhock_native2;
case 3:
return rhock_native3;
case 4:
return rhock_native4;
case 5:
return rhock_native5;
case 6:
return rhock_native6;
case 7:
return rhock_native7;
case 8:
return rhock_native8;
case 9:
return rhock_native9;
case 10:
return rhock_native10;
case 11:
return rhock_native11;
case 12:
return rhock_native12;
case 13:
return rhock_native13;
case 14:
return rhock_native14;
case 15:
return rhock_native15;
case 16:
return rhock_native16;
case 17:
return rhock_native17;
case 18:
return rhock_native18;
case 19:
return rhock_native19;
case 20:
return rhock_native20;
case 21:
return rhock_native21;
case 22:
return rhock_native22;
case 23:
return rhock_native23;
case 24:
return rhock_native24;
case 25:
return rhock_native25;
case 26:
return rhock_native26;
case 27:
return rhock_native27;
case 28:
return rhock_native28;
case 29:
return rhock_native29;
case 30:
return rhock_native30;
case 31:
return rhock_native31;
default:
return NULL;
}
};
#endif

#ifdef RHOCK_NATIVE_MAX_64
#define RHOCK_NATIVE_MAX 64
extern rhock_native rhock_native0 __attribute__((weak));
rhock_native rhock_native0 = rhock_native_nop;
extern rhock_native rhock_native1 __attribute__((weak));
rhock_native rhock_native1 = rhock_native_nop;
extern rhock_native rhock_native2 __attribute__((weak));
rhock_native rhock_native2 = rhock_native_nop;
extern rhock_native rhock_native3 __attribute__((weak));
rhock_native rhock_native3 = rhock_native_nop;
extern rhock_native rhock_native4 __attribute__((weak));
rhock_native rhock_native4 = rhock_native_nop;
extern rhock_native rhock_native5 __attribute__((weak));
rhock_native rhock_native5 = rhock_native_nop;
extern rhock_native rhock_native6 __attribute__((weak));
rhock_native rhock_native6 = rhock_native_nop;
extern rhock_native rhock_native7 __attribute__((weak));
rhock_native rhock_native7 = rhock_native_nop;
extern rhock_native rhock_native8 __attribute__((weak));
rhock_native rhock_native8 = rhock_native_nop;
extern rhock_native rhock_native9 __attribute__((weak));
rhock_native rhock_native9 = rhock_native_nop;
extern rhock_native rhock_native10 __attribute__((weak));
rhock_native rhock_native10 = rhock_native_nop;
extern rhock_native rhock_native11 __attribute__((weak));
rhock_native rhock_native11 = rhock_native_nop;
extern rhock_native rhock_native12 __attribute__((weak));
rhock_native rhock_native12 = rhock_native_nop;
extern rhock_native rhock_native13 __attribute__((weak));
rhock_native rhock_native13 = rhock_native_nop;
extern rhock_native rhock_native14 __attribute__((weak));
rhock_native rhock_native14 = rhock_native_nop;
extern rhock_native rhock_native15 __attribute__((weak));
rhock_native rhock_native15 = rhock_native_nop;
extern rhock_native rhock_native16 __attribute__((weak));
rhock_native rhock_native16 = rhock_native_nop;
extern rhock_native rhock_native17 __attribute__((weak));
rhock_native rhock_native17 = rhock_native_nop;
extern rhock_native rhock_native18 __attribute__((weak));
rhock_native rhock_native18 = rhock_native_nop;
extern rhock_native rhock_native19 __attribute__((weak));
rhock_native rhock_native19 = rhock_native_nop;
extern rhock_native rhock_native20 __attribute__((weak));
rhock_native rhock_native20 = rhock_native_nop;
extern rhock_native rhock_native21 __attribute__((weak));
rhock_native rhock_native21 = rhock_native_nop;
extern rhock_native rhock_native22 __attribute__((weak));
rhock_native rhock_native22 = rhock_native_nop;
extern rhock_native rhock_native23 __attribute__((weak));
rhock_native rhock_native23 = rhock_native_nop;
extern rhock_native rhock_native24 __attribute__((weak));
rhock_native rhock_native24 = rhock_native_nop;
extern rhock_native rhock_native25 __attribute__((weak));
rhock_native rhock_native25 = rhock_native_nop;
extern rhock_native rhock_native26 __attribute__((weak));
rhock_native rhock_native26 = rhock_native_nop;
extern rhock_native rhock_native27 __attribute__((weak));
rhock_native rhock_native27 = rhock_native_nop;
extern rhock_native rhock_native28 __attribute__((weak));
rhock_native rhock_native28 = rhock_native_nop;
extern rhock_native rhock_native29 __attribute__((weak));
rhock_native rhock_native29 = rhock_native_nop;
extern rhock_native rhock_native30 __attribute__((weak));
rhock_native rhock_native30 = rhock_native_nop;
extern rhock_native rhock_native31 __attribute__((weak));
rhock_native rhock_native31 = rhock_native_nop;
extern rhock_native rhock_native32 __attribute__((weak));
rhock_native rhock_native32 = rhock_native_nop;
extern rhock_native rhock_native33 __attribute__((weak));
rhock_native rhock_native33 = rhock_native_nop;
extern rhock_native rhock_native34 __attribute__((weak));
rhock_native rhock_native34 = rhock_native_nop;
extern rhock_native rhock_native35 __attribute__((weak));
rhock_native rhock_native35 = rhock_native_nop;
extern rhock_native rhock_native36 __attribute__((weak));
rhock_native rhock_native36 = rhock_native_nop;
extern rhock_native rhock_native37 __attribute__((weak));
rhock_native rhock_native37 = rhock_native_nop;
extern rhock_native rhock_native38 __attribute__((weak));
rhock_native rhock_native38 = rhock_native_nop;
extern rhock_native rhock_native39 __attribute__((weak));
rhock_native rhock_native39 = rhock_native_nop;
extern rhock_native rhock_native40 __attribute__((weak));
rhock_native rhock_native40 = rhock_native_nop;
extern rhock_native rhock_native41 __attribute__((weak));
rhock_native rhock_native41 = rhock_native_nop;
extern rhock_native rhock_native42 __attribute__((weak));
rhock_native rhock_native42 = rhock_native_nop;
extern rhock_native rhock_native43 __attribute__((weak));
rhock_native rhock_native43 = rhock_native_nop;
extern rhock_native rhock_native44 __attribute__((weak));
rhock_native rhock_native44 = rhock_native_nop;
extern rhock_native rhock_native45 __attribute__((weak));
rhock_native rhock_native45 = rhock_native_nop;
extern rhock_native rhock_native46 __attribute__((weak));
rhock_native rhock_native46 = rhock_native_nop;
extern rhock_native rhock_native47 __attribute__((weak));
rhock_native rhock_native47 = rhock_native_nop;
extern rhock_native rhock_native48 __attribute__((weak));
rhock_native rhock_native48 = rhock_native_nop;
extern rhock_native rhock_native49 __attribute__((weak));
rhock_native rhock_native49 = rhock_native_nop;
extern rhock_native rhock_native50 __attribute__((weak));
rhock_native rhock_native50 = rhock_native_nop;
extern rhock_native rhock_native51 __attribute__((weak));
rhock_native rhock_native51 = rhock_native_nop;
extern rhock_native rhock_native52 __attribute__((weak));
rhock_native rhock_native52 = rhock_native_nop;
extern rhock_native rhock_native53 __attribute__((weak));
rhock_native rhock_native53 = rhock_native_nop;
extern rhock_native rhock_native54 __attribute__((weak));
rhock_native rhock_native54 = rhock_native_nop;
extern rhock_native rhock_native55 __attribute__((weak));
rhock_native rhock_native55 = rhock_native_nop;
extern rhock_native rhock_native56 __attribute__((weak));
rhock_native rhock_native56 = rhock_native_nop;
extern rhock_native rhock_native57 __attribute__((weak));
rhock_native rhock_native57 = rhock_native_nop;
extern rhock_native rhock_native58 __attribute__((weak));
rhock_native rhock_native58 = rhock_native_nop;
extern rhock_native rhock_native59 __attribute__((weak));
rhock_native rhock_native59 = rhock_native_nop;
extern rhock_native rhock_native60 __attribute__((weak));
rhock_native rhock_native60 = rhock_native_nop;
extern rhock_native rhock_native61 __attribute__((weak));
rhock_native rhock_native61 = rhock_native_nop;
extern rhock_native rhock_native62 __attribute__((weak));
rhock_native rhock_native62 = rhock_native_nop;
extern rhock_native rhock_native63 __attribute__((weak));
rhock_native rhock_native63 = rhock_native_nop;
rhock_native rhock_native_get(uint8_t id)
{
switch (id) {
case 0:
return rhock_native0;
case 1:
return rhock_native1;
case 2:
return rhock_native2;
case 3:
return rhock_native3;
case 4:
return rhock_native4;
case 5:
return rhock_native5;
case 6:
return rhock_native6;
case 7:
return rhock_native7;
case 8:
return rhock_native8;
case 9:
return rhock_native9;
case 10:
return rhock_native10;
case 11:
return rhock_native11;
case 12:
return rhock_native12;
case 13:
return rhock_native13;
case 14:
return rhock_native14;
case 15:
return rhock_native15;
case 16:
return rhock_native16;
case 17:
return rhock_native17;
case 18:
return rhock_native18;
case 19:
return rhock_native19;
case 20:
return rhock_native20;
case 21:
return rhock_native21;
case 22:
return rhock_native22;
case 23:
return rhock_native23;
case 24:
return rhock_native24;
case 25:
return rhock_native25;
case 26:
return rhock_native26;
case 27:
return rhock_native27;
case 28:
return rhock_native28;
case 29:
return rhock_native29;
case 30:
return rhock_native30;
case 31:
return rhock_native31;
case 32:
return rhock_native32;
case 33:
return rhock_native33;
case 34:
return rhock_native34;
case 35:
return rhock_native35;
case 36:
return rhock_native36;
case 37:
return rhock_native37;
case 38:
return rhock_native38;
case 39:
return rhock_native39;
case 40:
return rhock_native40;
case 41:
return rhock_native41;
case 42:
return rhock_native42;
case 43:
return rhock_native43;
case 44:
return rhock_native44;
case 45:
return rhock_native45;
case 46:
return rhock_native46;
case 47:
return rhock_native47;
case 48:
return rhock_native48;
case 49:
return rhock_native49;
case 50:
return rhock_native50;
case 51:
return rhock_native51;
case 52:
return rhock_native52;
case 53:
return rhock_native53;
case 54:
return rhock_native54;
case 55:
return rhock_native55;
case 56:
return rhock_native56;
case 57:
return rhock_native57;
case 58:
return rhock_native58;
case 59:
return rhock_native59;
case 60:
return rhock_native60;
case 61:
return rhock_native61;
case 62:
return rhock_native62;
case 63:
return rhock_native63;
default:
return NULL;
}
};
#endif

#ifdef RHOCK_NATIVE_MAX_128
#define RHOCK_NATIVE_MAX 128
extern rhock_native rhock_native0 __attribute__((weak));
rhock_native rhock_native0 = rhock_native_nop;
extern rhock_native rhock_native1 __attribute__((weak));
rhock_native rhock_native1 = rhock_native_nop;
extern rhock_native rhock_native2 __attribute__((weak));
rhock_native rhock_native2 = rhock_native_nop;
extern rhock_native rhock_native3 __attribute__((weak));
rhock_native rhock_native3 = rhock_native_nop;
extern rhock_native rhock_native4 __attribute__((weak));
rhock_native rhock_native4 = rhock_native_nop;
extern rhock_native rhock_native5 __attribute__((weak));
rhock_native rhock_native5 = rhock_native_nop;
extern rhock_native rhock_native6 __attribute__((weak));
rhock_native rhock_native6 = rhock_native_nop;
extern rhock_native rhock_native7 __attribute__((weak));
rhock_native rhock_native7 = rhock_native_nop;
extern rhock_native rhock_native8 __attribute__((weak));
rhock_native rhock_native8 = rhock_native_nop;
extern rhock_native rhock_native9 __attribute__((weak));
rhock_native rhock_native9 = rhock_native_nop;
extern rhock_native rhock_native10 __attribute__((weak));
rhock_native rhock_native10 = rhock_native_nop;
extern rhock_native rhock_native11 __attribute__((weak));
rhock_native rhock_native11 = rhock_native_nop;
extern rhock_native rhock_native12 __attribute__((weak));
rhock_native rhock_native12 = rhock_native_nop;
extern rhock_native rhock_native13 __attribute__((weak));
rhock_native rhock_native13 = rhock_native_nop;
extern rhock_native rhock_native14 __attribute__((weak));
rhock_native rhock_native14 = rhock_native_nop;
extern rhock_native rhock_native15 __attribute__((weak));
rhock_native rhock_native15 = rhock_native_nop;
extern rhock_native rhock_native16 __attribute__((weak));
rhock_native rhock_native16 = rhock_native_nop;
extern rhock_native rhock_native17 __attribute__((weak));
rhock_native rhock_native17 = rhock_native_nop;
extern rhock_native rhock_native18 __attribute__((weak));
rhock_native rhock_native18 = rhock_native_nop;
extern rhock_native rhock_native19 __attribute__((weak));
rhock_native rhock_native19 = rhock_native_nop;
extern rhock_native rhock_native20 __attribute__((weak));
rhock_native rhock_native20 = rhock_native_nop;
extern rhock_native rhock_native21 __attribute__((weak));
rhock_native rhock_native21 = rhock_native_nop;
extern rhock_native rhock_native22 __attribute__((weak));
rhock_native rhock_native22 = rhock_native_nop;
extern rhock_native rhock_native23 __attribute__((weak));
rhock_native rhock_native23 = rhock_native_nop;
extern rhock_native rhock_native24 __attribute__((weak));
rhock_native rhock_native24 = rhock_native_nop;
extern rhock_native rhock_native25 __attribute__((weak));
rhock_native rhock_native25 = rhock_native_nop;
extern rhock_native rhock_native26 __attribute__((weak));
rhock_native rhock_native26 = rhock_native_nop;
extern rhock_native rhock_native27 __attribute__((weak));
rhock_native rhock_native27 = rhock_native_nop;
extern rhock_native rhock_native28 __attribute__((weak));
rhock_native rhock_native28 = rhock_native_nop;
extern rhock_native rhock_native29 __attribute__((weak));
rhock_native rhock_native29 = rhock_native_nop;
extern rhock_native rhock_native30 __attribute__((weak));
rhock_native rhock_native30 = rhock_native_nop;
extern rhock_native rhock_native31 __attribute__((weak));
rhock_native rhock_native31 = rhock_native_nop;
extern rhock_native rhock_native32 __attribute__((weak));
rhock_native rhock_native32 = rhock_native_nop;
extern rhock_native rhock_native33 __attribute__((weak));
rhock_native rhock_native33 = rhock_native_nop;
extern rhock_native rhock_native34 __attribute__((weak));
rhock_native rhock_native34 = rhock_native_nop;
extern rhock_native rhock_native35 __attribute__((weak));
rhock_native rhock_native35 = rhock_native_nop;
extern rhock_native rhock_native36 __attribute__((weak));
rhock_native rhock_native36 = rhock_native_nop;
extern rhock_native rhock_native37 __attribute__((weak));
rhock_native rhock_native37 = rhock_native_nop;
extern rhock_native rhock_native38 __attribute__((weak));
rhock_native rhock_native38 = rhock_native_nop;
extern rhock_native rhock_native39 __attribute__((weak));
rhock_native rhock_native39 = rhock_native_nop;
extern rhock_native rhock_native40 __attribute__((weak));
rhock_native rhock_native40 = rhock_native_nop;
extern rhock_native rhock_native41 __attribute__((weak));
rhock_native rhock_native41 = rhock_native_nop;
extern rhock_native rhock_native42 __attribute__((weak));
rhock_native rhock_native42 = rhock_native_nop;
extern rhock_native rhock_native43 __attribute__((weak));
rhock_native rhock_native43 = rhock_native_nop;
extern rhock_native rhock_native44 __attribute__((weak));
rhock_native rhock_native44 = rhock_native_nop;
extern rhock_native rhock_native45 __attribute__((weak));
rhock_native rhock_native45 = rhock_native_nop;
extern rhock_native rhock_native46 __attribute__((weak));
rhock_native rhock_native46 = rhock_native_nop;
extern rhock_native rhock_native47 __attribute__((weak));
rhock_native rhock_native47 = rhock_native_nop;
extern rhock_native rhock_native48 __attribute__((weak));
rhock_native rhock_native48 = rhock_native_nop;
extern rhock_native rhock_native49 __attribute__((weak));
rhock_native rhock_native49 = rhock_native_nop;
extern rhock_native rhock_native50 __attribute__((weak));
rhock_native rhock_native50 = rhock_native_nop;
extern rhock_native rhock_native51 __attribute__((weak));
rhock_native rhock_native51 = rhock_native_nop;
extern rhock_native rhock_native52 __attribute__((weak));
rhock_native rhock_native52 = rhock_native_nop;
extern rhock_native rhock_native53 __attribute__((weak));
rhock_native rhock_native53 = rhock_native_nop;
extern rhock_native rhock_native54 __attribute__((weak));
rhock_native rhock_native54 = rhock_native_nop;
extern rhock_native rhock_native55 __attribute__((weak));
rhock_native rhock_native55 = rhock_native_nop;
extern rhock_native rhock_native56 __attribute__((weak));
rhock_native rhock_native56 = rhock_native_nop;
extern rhock_native rhock_native57 __attribute__((weak));
rhock_native rhock_native57 = rhock_native_nop;
extern rhock_native rhock_native58 __attribute__((weak));
rhock_native rhock_native58 = rhock_native_nop;
extern rhock_native rhock_native59 __attribute__((weak));
rhock_native rhock_native59 = rhock_native_nop;
extern rhock_native rhock_native60 __attribute__((weak));
rhock_native rhock_native60 = rhock_native_nop;
extern rhock_native rhock_native61 __attribute__((weak));
rhock_native rhock_native61 = rhock_native_nop;
extern rhock_native rhock_native62 __attribute__((weak));
rhock_native rhock_native62 = rhock_native_nop;
extern rhock_native rhock_native63 __attribute__((weak));
rhock_native rhock_native63 = rhock_native_nop;
extern rhock_native rhock_native64 __attribute__((weak));
rhock_native rhock_native64 = rhock_native_nop;
extern rhock_native rhock_native65 __attribute__((weak));
rhock_native rhock_native65 = rhock_native_nop;
extern rhock_native rhock_native66 __attribute__((weak));
rhock_native rhock_native66 = rhock_native_nop;
extern rhock_native rhock_native67 __attribute__((weak));
rhock_native rhock_native67 = rhock_native_nop;
extern rhock_native rhock_native68 __attribute__((weak));
rhock_native rhock_native68 = rhock_native_nop;
extern rhock_native rhock_native69 __attribute__((weak));
rhock_native rhock_native69 = rhock_native_nop;
extern rhock_native rhock_native70 __attribute__((weak));
rhock_native rhock_native70 = rhock_native_nop;
extern rhock_native rhock_native71 __attribute__((weak));
rhock_native rhock_native71 = rhock_native_nop;
extern rhock_native rhock_native72 __attribute__((weak));
rhock_native rhock_native72 = rhock_native_nop;
extern rhock_native rhock_native73 __attribute__((weak));
rhock_native rhock_native73 = rhock_native_nop;
extern rhock_native rhock_native74 __attribute__((weak));
rhock_native rhock_native74 = rhock_native_nop;
extern rhock_native rhock_native75 __attribute__((weak));
rhock_native rhock_native75 = rhock_native_nop;
extern rhock_native rhock_native76 __attribute__((weak));
rhock_native rhock_native76 = rhock_native_nop;
extern rhock_native rhock_native77 __attribute__((weak));
rhock_native rhock_native77 = rhock_native_nop;
extern rhock_native rhock_native78 __attribute__((weak));
rhock_native rhock_native78 = rhock_native_nop;
extern rhock_native rhock_native79 __attribute__((weak));
rhock_native rhock_native79 = rhock_native_nop;
extern rhock_native rhock_native80 __attribute__((weak));
rhock_native rhock_native80 = rhock_native_nop;
extern rhock_native rhock_native81 __attribute__((weak));
rhock_native rhock_native81 = rhock_native_nop;
extern rhock_native rhock_native82 __attribute__((weak));
rhock_native rhock_native82 = rhock_native_nop;
extern rhock_native rhock_native83 __attribute__((weak));
rhock_native rhock_native83 = rhock_native_nop;
extern rhock_native rhock_native84 __attribute__((weak));
rhock_native rhock_native84 = rhock_native_nop;
extern rhock_native rhock_native85 __attribute__((weak));
rhock_native rhock_native85 = rhock_native_nop;
extern rhock_native rhock_native86 __attribute__((weak));
rhock_native rhock_native86 = rhock_native_nop;
extern rhock_native rhock_native87 __attribute__((weak));
rhock_native rhock_native87 = rhock_native_nop;
extern rhock_native rhock_native88 __attribute__((weak));
rhock_native rhock_native88 = rhock_native_nop;
extern rhock_native rhock_native89 __attribute__((weak));
rhock_native rhock_native89 = rhock_native_nop;
extern rhock_native rhock_native90 __attribute__((weak));
rhock_native rhock_native90 = rhock_native_nop;
extern rhock_native rhock_native91 __attribute__((weak));
rhock_native rhock_native91 = rhock_native_nop;
extern rhock_native rhock_native92 __attribute__((weak));
rhock_native rhock_native92 = rhock_native_nop;
extern rhock_native rhock_native93 __attribute__((weak));
rhock_native rhock_native93 = rhock_native_nop;
extern rhock_native rhock_native94 __attribute__((weak));
rhock_native rhock_native94 = rhock_native_nop;
extern rhock_native rhock_native95 __attribute__((weak));
rhock_native rhock_native95 = rhock_native_nop;
extern rhock_native rhock_native96 __attribute__((weak));
rhock_native rhock_native96 = rhock_native_nop;
extern rhock_native rhock_native97 __attribute__((weak));
rhock_native rhock_native97 = rhock_native_nop;
extern rhock_native rhock_native98 __attribute__((weak));
rhock_native rhock_native98 = rhock_native_nop;
extern rhock_native rhock_native99 __attribute__((weak));
rhock_native rhock_native99 = rhock_native_nop;
extern rhock_native rhock_native100 __attribute__((weak));
rhock_native rhock_native100 = rhock_native_nop;
extern rhock_native rhock_native101 __attribute__((weak));
rhock_native rhock_native101 = rhock_native_nop;
extern rhock_native rhock_native102 __attribute__((weak));
rhock_native rhock_native102 = rhock_native_nop;
extern rhock_native rhock_native103 __attribute__((weak));
rhock_native rhock_native103 = rhock_native_nop;
extern rhock_native rhock_native104 __attribute__((weak));
rhock_native rhock_native104 = rhock_native_nop;
extern rhock_native rhock_native105 __attribute__((weak));
rhock_native rhock_native105 = rhock_native_nop;
extern rhock_native rhock_native106 __attribute__((weak));
rhock_native rhock_native106 = rhock_native_nop;
extern rhock_native rhock_native107 __attribute__((weak));
rhock_native rhock_native107 = rhock_native_nop;
extern rhock_native rhock_native108 __attribute__((weak));
rhock_native rhock_native108 = rhock_native_nop;
extern rhock_native rhock_native109 __attribute__((weak));
rhock_native rhock_native109 = rhock_native_nop;
extern rhock_native rhock_native110 __attribute__((weak));
rhock_native rhock_native110 = rhock_native_nop;
extern rhock_native rhock_native111 __attribute__((weak));
rhock_native rhock_native111 = rhock_native_nop;
extern rhock_native rhock_native112 __attribute__((weak));
rhock_native rhock_native112 = rhock_native_nop;
extern rhock_native rhock_native113 __attribute__((weak));
rhock_native rhock_native113 = rhock_native_nop;
extern rhock_native rhock_native114 __attribute__((weak));
rhock_native rhock_native114 = rhock_native_nop;
extern rhock_native rhock_native115 __attribute__((weak));
rhock_native rhock_native115 = rhock_native_nop;
extern rhock_native rhock_native116 __attribute__((weak));
rhock_native rhock_native116 = rhock_native_nop;
extern rhock_native rhock_native117 __attribute__((weak));
rhock_native rhock_native117 = rhock_native_nop;
extern rhock_native rhock_native118 __attribute__((weak));
rhock_native rhock_native118 = rhock_native_nop;
extern rhock_native rhock_native119 __attribute__((weak));
rhock_native rhock_native119 = rhock_native_nop;
extern rhock_native rhock_native120 __attribute__((weak));
rhock_native rhock_native120 = rhock_native_nop;
extern rhock_native rhock_native121 __attribute__((weak));
rhock_native rhock_native121 = rhock_native_nop;
extern rhock_native rhock_native122 __attribute__((weak));
rhock_native rhock_native122 = rhock_native_nop;
extern rhock_native rhock_native123 __attribute__((weak));
rhock_native rhock_native123 = rhock_native_nop;
extern rhock_native rhock_native124 __attribute__((weak));
rhock_native rhock_native124 = rhock_native_nop;
extern rhock_native rhock_native125 __attribute__((weak));
rhock_native rhock_native125 = rhock_native_nop;
extern rhock_native rhock_native126 __attribute__((weak));
rhock_native rhock_native126 = rhock_native_nop;
extern rhock_native rhock_native127 __attribute__((weak));
rhock_native rhock_native127 = rhock_native_nop;
rhock_native rhock_native_get(uint8_t id)
{
switch (id) {
case 0:
return rhock_native0;
case 1:
return rhock_native1;
case 2:
return rhock_native2;
case 3:
return rhock_native3;
case 4:
return rhock_native4;
case 5:
return rhock_native5;
case 6:
return rhock_native6;
case 7:
return rhock_native7;
case 8:
return rhock_native8;
case 9:
return rhock_native9;
case 10:
return rhock_native10;
case 11:
return rhock_native11;
case 12:
return rhock_native12;
case 13:
return rhock_native13;
case 14:
return rhock_native14;
case 15:
return rhock_native15;
case 16:
return rhock_native16;
case 17:
return rhock_native17;
case 18:
return rhock_native18;
case 19:
return rhock_native19;
case 20:
return rhock_native20;
case 21:
return rhock_native21;
case 22:
return rhock_native22;
case 23:
return rhock_native23;
case 24:
return rhock_native24;
case 25:
return rhock_native25;
case 26:
return rhock_native26;
case 27:
return rhock_native27;
case 28:
return rhock_native28;
case 29:
return rhock_native29;
case 30:
return rhock_native30;
case 31:
return rhock_native31;
case 32:
return rhock_native32;
case 33:
return rhock_native33;
case 34:
return rhock_native34;
case 35:
return rhock_native35;
case 36:
return rhock_native36;
case 37:
return rhock_native37;
case 38:
return rhock_native38;
case 39:
return rhock_native39;
case 40:
return rhock_native40;
case 41:
return rhock_native41;
case 42:
return rhock_native42;
case 43:
return rhock_native43;
case 44:
return rhock_native44;
case 45:
return rhock_native45;
case 46:
return rhock_native46;
case 47:
return rhock_native47;
case 48:
return rhock_native48;
case 49:
return rhock_native49;
case 50:
return rhock_native50;
case 51:
return rhock_native51;
case 52:
return rhock_native52;
case 53:
return rhock_native53;
case 54:
return rhock_native54;
case 55:
return rhock_native55;
case 56:
return rhock_native56;
case 57:
return rhock_native57;
case 58:
return rhock_native58;
case 59:
return rhock_native59;
case 60:
return rhock_native60;
case 61:
return rhock_native61;
case 62:
return rhock_native62;
case 63:
return rhock_native63;
case 64:
return rhock_native64;
case 65:
return rhock_native65;
case 66:
return rhock_native66;
case 67:
return rhock_native67;
case 68:
return rhock_native68;
case 69:
return rhock_native69;
case 70:
return rhock_native70;
case 71:
return rhock_native71;
case 72:
return rhock_native72;
case 73:
return rhock_native73;
case 74:
return rhock_native74;
case 75:
return rhock_native75;
case 76:
return rhock_native76;
case 77:
return rhock_native77;
case 78:
return rhock_native78;
case 79:
return rhock_native79;
case 80:
return rhock_native80;
case 81:
return rhock_native81;
case 82:
return rhock_native82;
case 83:
return rhock_native83;
case 84:
return rhock_native84;
case 85:
return rhock_native85;
case 86:
return rhock_native86;
case 87:
return rhock_native87;
case 88:
return rhock_native88;
case 89:
return rhock_native89;
case 90:
return rhock_native90;
case 91:
return rhock_native91;
case 92:
return rhock_native92;
case 93:
return rhock_native93;
case 94:
return rhock_native94;
case 95:
return rhock_native95;
case 96:
return rhock_native96;
case 97:
return rhock_native97;
case 98:
return rhock_native98;
case 99:
return rhock_native99;
case 100:
return rhock_native100;
case 101:
return rhock_native101;
case 102:
return rhock_native102;
case 103:
return rhock_native103;
case 104:
return rhock_native104;
case 105:
return rhock_native105;
case 106:
return rhock_native106;
case 107:
return rhock_native107;
case 108:
return rhock_native108;
case 109:
return rhock_native109;
case 110:
return rhock_native110;
case 111:
return rhock_native111;
case 112:
return rhock_native112;
case 113:
return rhock_native113;
case 114:
return rhock_native114;
case 115:
return rhock_native115;
case 116:
return rhock_native116;
case 117:
return rhock_native117;
case 118:
return rhock_native118;
case 119:
return rhock_native119;
case 120:
return rhock_native120;
case 121:
return rhock_native121;
case 122:
return rhock_native122;
case 123:
return rhock_native123;
case 124:
return rhock_native124;
case 125:
return rhock_native125;
case 126:
return rhock_native126;
case 127:
return rhock_native127;
default:
return NULL;
}
};
#endif

#ifdef RHOCK_NATIVE_MAX_256
#define RHOCK_NATIVE_MAX 256
extern rhock_native rhock_native0 __attribute__((weak));
rhock_native rhock_native0 = rhock_native_nop;
extern rhock_native rhock_native1 __attribute__((weak));
rhock_native rhock_native1 = rhock_native_nop;
extern rhock_native rhock_native2 __attribute__((weak));
rhock_native rhock_native2 = rhock_native_nop;
extern rhock_native rhock_native3 __attribute__((weak));
rhock_native rhock_native3 = rhock_native_nop;
extern rhock_native rhock_native4 __attribute__((weak));
rhock_native rhock_native4 = rhock_native_nop;
extern rhock_native rhock_native5 __attribute__((weak));
rhock_native rhock_native5 = rhock_native_nop;
extern rhock_native rhock_native6 __attribute__((weak));
rhock_native rhock_native6 = rhock_native_nop;
extern rhock_native rhock_native7 __attribute__((weak));
rhock_native rhock_native7 = rhock_native_nop;
extern rhock_native rhock_native8 __attribute__((weak));
rhock_native rhock_native8 = rhock_native_nop;
extern rhock_native rhock_native9 __attribute__((weak));
rhock_native rhock_native9 = rhock_native_nop;
extern rhock_native rhock_native10 __attribute__((weak));
rhock_native rhock_native10 = rhock_native_nop;
extern rhock_native rhock_native11 __attribute__((weak));
rhock_native rhock_native11 = rhock_native_nop;
extern rhock_native rhock_native12 __attribute__((weak));
rhock_native rhock_native12 = rhock_native_nop;
extern rhock_native rhock_native13 __attribute__((weak));
rhock_native rhock_native13 = rhock_native_nop;
extern rhock_native rhock_native14 __attribute__((weak));
rhock_native rhock_native14 = rhock_native_nop;
extern rhock_native rhock_native15 __attribute__((weak));
rhock_native rhock_native15 = rhock_native_nop;
extern rhock_native rhock_native16 __attribute__((weak));
rhock_native rhock_native16 = rhock_native_nop;
extern rhock_native rhock_native17 __attribute__((weak));
rhock_native rhock_native17 = rhock_native_nop;
extern rhock_native rhock_native18 __attribute__((weak));
rhock_native rhock_native18 = rhock_native_nop;
extern rhock_native rhock_native19 __attribute__((weak));
rhock_native rhock_native19 = rhock_native_nop;
extern rhock_native rhock_native20 __attribute__((weak));
rhock_native rhock_native20 = rhock_native_nop;
extern rhock_native rhock_native21 __attribute__((weak));
rhock_native rhock_native21 = rhock_native_nop;
extern rhock_native rhock_native22 __attribute__((weak));
rhock_native rhock_native22 = rhock_native_nop;
extern rhock_native rhock_native23 __attribute__((weak));
rhock_native rhock_native23 = rhock_native_nop;
extern rhock_native rhock_native24 __attribute__((weak));
rhock_native rhock_native24 = rhock_native_nop;
extern rhock_native rhock_native25 __attribute__((weak));
rhock_native rhock_native25 = rhock_native_nop;
extern rhock_native rhock_native26 __attribute__((weak));
rhock_native rhock_native26 = rhock_native_nop;
extern rhock_native rhock_native27 __attribute__((weak));
rhock_native rhock_native27 = rhock_native_nop;
extern rhock_native rhock_native28 __attribute__((weak));
rhock_native rhock_native28 = rhock_native_nop;
extern rhock_native rhock_native29 __attribute__((weak));
rhock_native rhock_native29 = rhock_native_nop;
extern rhock_native rhock_native30 __attribute__((weak));
rhock_native rhock_native30 = rhock_native_nop;
extern rhock_native rhock_native31 __attribute__((weak));
rhock_native rhock_native31 = rhock_native_nop;
extern rhock_native rhock_native32 __attribute__((weak));
rhock_native rhock_native32 = rhock_native_nop;
extern rhock_native rhock_native33 __attribute__((weak));
rhock_native rhock_native33 = rhock_native_nop;
extern rhock_native rhock_native34 __attribute__((weak));
rhock_native rhock_native34 = rhock_native_nop;
extern rhock_native rhock_native35 __attribute__((weak));
rhock_native rhock_native35 = rhock_native_nop;
extern rhock_native rhock_native36 __attribute__((weak));
rhock_native rhock_native36 = rhock_native_nop;
extern rhock_native rhock_native37 __attribute__((weak));
rhock_native rhock_native37 = rhock_native_nop;
extern rhock_native rhock_native38 __attribute__((weak));
rhock_native rhock_native38 = rhock_native_nop;
extern rhock_native rhock_native39 __attribute__((weak));
rhock_native rhock_native39 = rhock_native_nop;
extern rhock_native rhock_native40 __attribute__((weak));
rhock_native rhock_native40 = rhock_native_nop;
extern rhock_native rhock_native41 __attribute__((weak));
rhock_native rhock_native41 = rhock_native_nop;
extern rhock_native rhock_native42 __attribute__((weak));
rhock_native rhock_native42 = rhock_native_nop;
extern rhock_native rhock_native43 __attribute__((weak));
rhock_native rhock_native43 = rhock_native_nop;
extern rhock_native rhock_native44 __attribute__((weak));
rhock_native rhock_native44 = rhock_native_nop;
extern rhock_native rhock_native45 __attribute__((weak));
rhock_native rhock_native45 = rhock_native_nop;
extern rhock_native rhock_native46 __attribute__((weak));
rhock_native rhock_native46 = rhock_native_nop;
extern rhock_native rhock_native47 __attribute__((weak));
rhock_native rhock_native47 = rhock_native_nop;
extern rhock_native rhock_native48 __attribute__((weak));
rhock_native rhock_native48 = rhock_native_nop;
extern rhock_native rhock_native49 __attribute__((weak));
rhock_native rhock_native49 = rhock_native_nop;
extern rhock_native rhock_native50 __attribute__((weak));
rhock_native rhock_native50 = rhock_native_nop;
extern rhock_native rhock_native51 __attribute__((weak));
rhock_native rhock_native51 = rhock_native_nop;
extern rhock_native rhock_native52 __attribute__((weak));
rhock_native rhock_native52 = rhock_native_nop;
extern rhock_native rhock_native53 __attribute__((weak));
rhock_native rhock_native53 = rhock_native_nop;
extern rhock_native rhock_native54 __attribute__((weak));
rhock_native rhock_native54 = rhock_native_nop;
extern rhock_native rhock_native55 __attribute__((weak));
rhock_native rhock_native55 = rhock_native_nop;
extern rhock_native rhock_native56 __attribute__((weak));
rhock_native rhock_native56 = rhock_native_nop;
extern rhock_native rhock_native57 __attribute__((weak));
rhock_native rhock_native57 = rhock_native_nop;
extern rhock_native rhock_native58 __attribute__((weak));
rhock_native rhock_native58 = rhock_native_nop;
extern rhock_native rhock_native59 __attribute__((weak));
rhock_native rhock_native59 = rhock_native_nop;
extern rhock_native rhock_native60 __attribute__((weak));
rhock_native rhock_native60 = rhock_native_nop;
extern rhock_native rhock_native61 __attribute__((weak));
rhock_native rhock_native61 = rhock_native_nop;
extern rhock_native rhock_native62 __attribute__((weak));
rhock_native rhock_native62 = rhock_native_nop;
extern rhock_native rhock_native63 __attribute__((weak));
rhock_native rhock_native63 = rhock_native_nop;
extern rhock_native rhock_native64 __attribute__((weak));
rhock_native rhock_native64 = rhock_native_nop;
extern rhock_native rhock_native65 __attribute__((weak));
rhock_native rhock_native65 = rhock_native_nop;
extern rhock_native rhock_native66 __attribute__((weak));
rhock_native rhock_native66 = rhock_native_nop;
extern rhock_native rhock_native67 __attribute__((weak));
rhock_native rhock_native67 = rhock_native_nop;
extern rhock_native rhock_native68 __attribute__((weak));
rhock_native rhock_native68 = rhock_native_nop;
extern rhock_native rhock_native69 __attribute__((weak));
rhock_native rhock_native69 = rhock_native_nop;
extern rhock_native rhock_native70 __attribute__((weak));
rhock_native rhock_native70 = rhock_native_nop;
extern rhock_native rhock_native71 __attribute__((weak));
rhock_native rhock_native71 = rhock_native_nop;
extern rhock_native rhock_native72 __attribute__((weak));
rhock_native rhock_native72 = rhock_native_nop;
extern rhock_native rhock_native73 __attribute__((weak));
rhock_native rhock_native73 = rhock_native_nop;
extern rhock_native rhock_native74 __attribute__((weak));
rhock_native rhock_native74 = rhock_native_nop;
extern rhock_native rhock_native75 __attribute__((weak));
rhock_native rhock_native75 = rhock_native_nop;
extern rhock_native rhock_native76 __attribute__((weak));
rhock_native rhock_native76 = rhock_native_nop;
extern rhock_native rhock_native77 __attribute__((weak));
rhock_native rhock_native77 = rhock_native_nop;
extern rhock_native rhock_native78 __attribute__((weak));
rhock_native rhock_native78 = rhock_native_nop;
extern rhock_native rhock_native79 __attribute__((weak));
rhock_native rhock_native79 = rhock_native_nop;
extern rhock_native rhock_native80 __attribute__((weak));
rhock_native rhock_native80 = rhock_native_nop;
extern rhock_native rhock_native81 __attribute__((weak));
rhock_native rhock_native81 = rhock_native_nop;
extern rhock_native rhock_native82 __attribute__((weak));
rhock_native rhock_native82 = rhock_native_nop;
extern rhock_native rhock_native83 __attribute__((weak));
rhock_native rhock_native83 = rhock_native_nop;
extern rhock_native rhock_native84 __attribute__((weak));
rhock_native rhock_native84 = rhock_native_nop;
extern rhock_native rhock_native85 __attribute__((weak));
rhock_native rhock_native85 = rhock_native_nop;
extern rhock_native rhock_native86 __attribute__((weak));
rhock_native rhock_native86 = rhock_native_nop;
extern rhock_native rhock_native87 __attribute__((weak));
rhock_native rhock_native87 = rhock_native_nop;
extern rhock_native rhock_native88 __attribute__((weak));
rhock_native rhock_native88 = rhock_native_nop;
extern rhock_native rhock_native89 __attribute__((weak));
rhock_native rhock_native89 = rhock_native_nop;
extern rhock_native rhock_native90 __attribute__((weak));
rhock_native rhock_native90 = rhock_native_nop;
extern rhock_native rhock_native91 __attribute__((weak));
rhock_native rhock_native91 = rhock_native_nop;
extern rhock_native rhock_native92 __attribute__((weak));
rhock_native rhock_native92 = rhock_native_nop;
extern rhock_native rhock_native93 __attribute__((weak));
rhock_native rhock_native93 = rhock_native_nop;
extern rhock_native rhock_native94 __attribute__((weak));
rhock_native rhock_native94 = rhock_native_nop;
extern rhock_native rhock_native95 __attribute__((weak));
rhock_native rhock_native95 = rhock_native_nop;
extern rhock_native rhock_native96 __attribute__((weak));
rhock_native rhock_native96 = rhock_native_nop;
extern rhock_native rhock_native97 __attribute__((weak));
rhock_native rhock_native97 = rhock_native_nop;
extern rhock_native rhock_native98 __attribute__((weak));
rhock_native rhock_native98 = rhock_native_nop;
extern rhock_native rhock_native99 __attribute__((weak));
rhock_native rhock_native99 = rhock_native_nop;
extern rhock_native rhock_native100 __attribute__((weak));
rhock_native rhock_native100 = rhock_native_nop;
extern rhock_native rhock_native101 __attribute__((weak));
rhock_native rhock_native101 = rhock_native_nop;
extern rhock_native rhock_native102 __attribute__((weak));
rhock_native rhock_native102 = rhock_native_nop;
extern rhock_native rhock_native103 __attribute__((weak));
rhock_native rhock_native103 = rhock_native_nop;
extern rhock_native rhock_native104 __attribute__((weak));
rhock_native rhock_native104 = rhock_native_nop;
extern rhock_native rhock_native105 __attribute__((weak));
rhock_native rhock_native105 = rhock_native_nop;
extern rhock_native rhock_native106 __attribute__((weak));
rhock_native rhock_native106 = rhock_native_nop;
extern rhock_native rhock_native107 __attribute__((weak));
rhock_native rhock_native107 = rhock_native_nop;
extern rhock_native rhock_native108 __attribute__((weak));
rhock_native rhock_native108 = rhock_native_nop;
extern rhock_native rhock_native109 __attribute__((weak));
rhock_native rhock_native109 = rhock_native_nop;
extern rhock_native rhock_native110 __attribute__((weak));
rhock_native rhock_native110 = rhock_native_nop;
extern rhock_native rhock_native111 __attribute__((weak));
rhock_native rhock_native111 = rhock_native_nop;
extern rhock_native rhock_native112 __attribute__((weak));
rhock_native rhock_native112 = rhock_native_nop;
extern rhock_native rhock_native113 __attribute__((weak));
rhock_native rhock_native113 = rhock_native_nop;
extern rhock_native rhock_native114 __attribute__((weak));
rhock_native rhock_native114 = rhock_native_nop;
extern rhock_native rhock_native115 __attribute__((weak));
rhock_native rhock_native115 = rhock_native_nop;
extern rhock_native rhock_native116 __attribute__((weak));
rhock_native rhock_native116 = rhock_native_nop;
extern rhock_native rhock_native117 __attribute__((weak));
rhock_native rhock_native117 = rhock_native_nop;
extern rhock_native rhock_native118 __attribute__((weak));
rhock_native rhock_native118 = rhock_native_nop;
extern rhock_native rhock_native119 __attribute__((weak));
rhock_native rhock_native119 = rhock_native_nop;
extern rhock_native rhock_native120 __attribute__((weak));
rhock_native rhock_native120 = rhock_native_nop;
extern rhock_native rhock_native121 __attribute__((weak));
rhock_native rhock_native121 = rhock_native_nop;
extern rhock_native rhock_native122 __attribute__((weak));
rhock_native rhock_native122 = rhock_native_nop;
extern rhock_native rhock_native123 __attribute__((weak));
rhock_native rhock_native123 = rhock_native_nop;
extern rhock_native rhock_native124 __attribute__((weak));
rhock_native rhock_native124 = rhock_native_nop;
extern rhock_native rhock_native125 __attribute__((weak));
rhock_native rhock_native125 = rhock_native_nop;
extern rhock_native rhock_native126 __attribute__((weak));
rhock_native rhock_native126 = rhock_native_nop;
extern rhock_native rhock_native127 __attribute__((weak));
rhock_native rhock_native127 = rhock_native_nop;
extern rhock_native rhock_native128 __attribute__((weak));
rhock_native rhock_native128 = rhock_native_nop;
extern rhock_native rhock_native129 __attribute__((weak));
rhock_native rhock_native129 = rhock_native_nop;
extern rhock_native rhock_native130 __attribute__((weak));
rhock_native rhock_native130 = rhock_native_nop;
extern rhock_native rhock_native131 __attribute__((weak));
rhock_native rhock_native131 = rhock_native_nop;
extern rhock_native rhock_native132 __attribute__((weak));
rhock_native rhock_native132 = rhock_native_nop;
extern rhock_native rhock_native133 __attribute__((weak));
rhock_native rhock_native133 = rhock_native_nop;
extern rhock_native rhock_native134 __attribute__((weak));
rhock_native rhock_native134 = rhock_native_nop;
extern rhock_native rhock_native135 __attribute__((weak));
rhock_native rhock_native135 = rhock_native_nop;
extern rhock_native rhock_native136 __attribute__((weak));
rhock_native rhock_native136 = rhock_native_nop;
extern rhock_native rhock_native137 __attribute__((weak));
rhock_native rhock_native137 = rhock_native_nop;
extern rhock_native rhock_native138 __attribute__((weak));
rhock_native rhock_native138 = rhock_native_nop;
extern rhock_native rhock_native139 __attribute__((weak));
rhock_native rhock_native139 = rhock_native_nop;
extern rhock_native rhock_native140 __attribute__((weak));
rhock_native rhock_native140 = rhock_native_nop;
extern rhock_native rhock_native141 __attribute__((weak));
rhock_native rhock_native141 = rhock_native_nop;
extern rhock_native rhock_native142 __attribute__((weak));
rhock_native rhock_native142 = rhock_native_nop;
extern rhock_native rhock_native143 __attribute__((weak));
rhock_native rhock_native143 = rhock_native_nop;
extern rhock_native rhock_native144 __attribute__((weak));
rhock_native rhock_native144 = rhock_native_nop;
extern rhock_native rhock_native145 __attribute__((weak));
rhock_native rhock_native145 = rhock_native_nop;
extern rhock_native rhock_native146 __attribute__((weak));
rhock_native rhock_native146 = rhock_native_nop;
extern rhock_native rhock_native147 __attribute__((weak));
rhock_native rhock_native147 = rhock_native_nop;
extern rhock_native rhock_native148 __attribute__((weak));
rhock_native rhock_native148 = rhock_native_nop;
extern rhock_native rhock_native149 __attribute__((weak));
rhock_native rhock_native149 = rhock_native_nop;
extern rhock_native rhock_native150 __attribute__((weak));
rhock_native rhock_native150 = rhock_native_nop;
extern rhock_native rhock_native151 __attribute__((weak));
rhock_native rhock_native151 = rhock_native_nop;
extern rhock_native rhock_native152 __attribute__((weak));
rhock_native rhock_native152 = rhock_native_nop;
extern rhock_native rhock_native153 __attribute__((weak));
rhock_native rhock_native153 = rhock_native_nop;
extern rhock_native rhock_native154 __attribute__((weak));
rhock_native rhock_native154 = rhock_native_nop;
extern rhock_native rhock_native155 __attribute__((weak));
rhock_native rhock_native155 = rhock_native_nop;
extern rhock_native rhock_native156 __attribute__((weak));
rhock_native rhock_native156 = rhock_native_nop;
extern rhock_native rhock_native157 __attribute__((weak));
rhock_native rhock_native157 = rhock_native_nop;
extern rhock_native rhock_native158 __attribute__((weak));
rhock_native rhock_native158 = rhock_native_nop;
extern rhock_native rhock_native159 __attribute__((weak));
rhock_native rhock_native159 = rhock_native_nop;
extern rhock_native rhock_native160 __attribute__((weak));
rhock_native rhock_native160 = rhock_native_nop;
extern rhock_native rhock_native161 __attribute__((weak));
rhock_native rhock_native161 = rhock_native_nop;
extern rhock_native rhock_native162 __attribute__((weak));
rhock_native rhock_native162 = rhock_native_nop;
extern rhock_native rhock_native163 __attribute__((weak));
rhock_native rhock_native163 = rhock_native_nop;
extern rhock_native rhock_native164 __attribute__((weak));
rhock_native rhock_native164 = rhock_native_nop;
extern rhock_native rhock_native165 __attribute__((weak));
rhock_native rhock_native165 = rhock_native_nop;
extern rhock_native rhock_native166 __attribute__((weak));
rhock_native rhock_native166 = rhock_native_nop;
extern rhock_native rhock_native167 __attribute__((weak));
rhock_native rhock_native167 = rhock_native_nop;
extern rhock_native rhock_native168 __attribute__((weak));
rhock_native rhock_native168 = rhock_native_nop;
extern rhock_native rhock_native169 __attribute__((weak));
rhock_native rhock_native169 = rhock_native_nop;
extern rhock_native rhock_native170 __attribute__((weak));
rhock_native rhock_native170 = rhock_native_nop;
extern rhock_native rhock_native171 __attribute__((weak));
rhock_native rhock_native171 = rhock_native_nop;
extern rhock_native rhock_native172 __attribute__((weak));
rhock_native rhock_native172 = rhock_native_nop;
extern rhock_native rhock_native173 __attribute__((weak));
rhock_native rhock_native173 = rhock_native_nop;
extern rhock_native rhock_native174 __attribute__((weak));
rhock_native rhock_native174 = rhock_native_nop;
extern rhock_native rhock_native175 __attribute__((weak));
rhock_native rhock_native175 = rhock_native_nop;
extern rhock_native rhock_native176 __attribute__((weak));
rhock_native rhock_native176 = rhock_native_nop;
extern rhock_native rhock_native177 __attribute__((weak));
rhock_native rhock_native177 = rhock_native_nop;
extern rhock_native rhock_native178 __attribute__((weak));
rhock_native rhock_native178 = rhock_native_nop;
extern rhock_native rhock_native179 __attribute__((weak));
rhock_native rhock_native179 = rhock_native_nop;
extern rhock_native rhock_native180 __attribute__((weak));
rhock_native rhock_native180 = rhock_native_nop;
extern rhock_native rhock_native181 __attribute__((weak));
rhock_native rhock_native181 = rhock_native_nop;
extern rhock_native rhock_native182 __attribute__((weak));
rhock_native rhock_native182 = rhock_native_nop;
extern rhock_native rhock_native183 __attribute__((weak));
rhock_native rhock_native183 = rhock_native_nop;
extern rhock_native rhock_native184 __attribute__((weak));
rhock_native rhock_native184 = rhock_native_nop;
extern rhock_native rhock_native185 __attribute__((weak));
rhock_native rhock_native185 = rhock_native_nop;
extern rhock_native rhock_native186 __attribute__((weak));
rhock_native rhock_native186 = rhock_native_nop;
extern rhock_native rhock_native187 __attribute__((weak));
rhock_native rhock_native187 = rhock_native_nop;
extern rhock_native rhock_native188 __attribute__((weak));
rhock_native rhock_native188 = rhock_native_nop;
extern rhock_native rhock_native189 __attribute__((weak));
rhock_native rhock_native189 = rhock_native_nop;
extern rhock_native rhock_native190 __attribute__((weak));
rhock_native rhock_native190 = rhock_native_nop;
extern rhock_native rhock_native191 __attribute__((weak));
rhock_native rhock_native191 = rhock_native_nop;
extern rhock_native rhock_native192 __attribute__((weak));
rhock_native rhock_native192 = rhock_native_nop;
extern rhock_native rhock_native193 __attribute__((weak));
rhock_native rhock_native193 = rhock_native_nop;
extern rhock_native rhock_native194 __attribute__((weak));
rhock_native rhock_native194 = rhock_native_nop;
extern rhock_native rhock_native195 __attribute__((weak));
rhock_native rhock_native195 = rhock_native_nop;
extern rhock_native rhock_native196 __attribute__((weak));
rhock_native rhock_native196 = rhock_native_nop;
extern rhock_native rhock_native197 __attribute__((weak));
rhock_native rhock_native197 = rhock_native_nop;
extern rhock_native rhock_native198 __attribute__((weak));
rhock_native rhock_native198 = rhock_native_nop;
extern rhock_native rhock_native199 __attribute__((weak));
rhock_native rhock_native199 = rhock_native_nop;
extern rhock_native rhock_native200 __attribute__((weak));
rhock_native rhock_native200 = rhock_native_nop;
extern rhock_native rhock_native201 __attribute__((weak));
rhock_native rhock_native201 = rhock_native_nop;
extern rhock_native rhock_native202 __attribute__((weak));
rhock_native rhock_native202 = rhock_native_nop;
extern rhock_native rhock_native203 __attribute__((weak));
rhock_native rhock_native203 = rhock_native_nop;
extern rhock_native rhock_native204 __attribute__((weak));
rhock_native rhock_native204 = rhock_native_nop;
extern rhock_native rhock_native205 __attribute__((weak));
rhock_native rhock_native205 = rhock_native_nop;
extern rhock_native rhock_native206 __attribute__((weak));
rhock_native rhock_native206 = rhock_native_nop;
extern rhock_native rhock_native207 __attribute__((weak));
rhock_native rhock_native207 = rhock_native_nop;
extern rhock_native rhock_native208 __attribute__((weak));
rhock_native rhock_native208 = rhock_native_nop;
extern rhock_native rhock_native209 __attribute__((weak));
rhock_native rhock_native209 = rhock_native_nop;
extern rhock_native rhock_native210 __attribute__((weak));
rhock_native rhock_native210 = rhock_native_nop;
extern rhock_native rhock_native211 __attribute__((weak));
rhock_native rhock_native211 = rhock_native_nop;
extern rhock_native rhock_native212 __attribute__((weak));
rhock_native rhock_native212 = rhock_native_nop;
extern rhock_native rhock_native213 __attribute__((weak));
rhock_native rhock_native213 = rhock_native_nop;
extern rhock_native rhock_native214 __attribute__((weak));
rhock_native rhock_native214 = rhock_native_nop;
extern rhock_native rhock_native215 __attribute__((weak));
rhock_native rhock_native215 = rhock_native_nop;
extern rhock_native rhock_native216 __attribute__((weak));
rhock_native rhock_native216 = rhock_native_nop;
extern rhock_native rhock_native217 __attribute__((weak));
rhock_native rhock_native217 = rhock_native_nop;
extern rhock_native rhock_native218 __attribute__((weak));
rhock_native rhock_native218 = rhock_native_nop;
extern rhock_native rhock_native219 __attribute__((weak));
rhock_native rhock_native219 = rhock_native_nop;
extern rhock_native rhock_native220 __attribute__((weak));
rhock_native rhock_native220 = rhock_native_nop;
extern rhock_native rhock_native221 __attribute__((weak));
rhock_native rhock_native221 = rhock_native_nop;
extern rhock_native rhock_native222 __attribute__((weak));
rhock_native rhock_native222 = rhock_native_nop;
extern rhock_native rhock_native223 __attribute__((weak));
rhock_native rhock_native223 = rhock_native_nop;
extern rhock_native rhock_native224 __attribute__((weak));
rhock_native rhock_native224 = rhock_native_nop;
extern rhock_native rhock_native225 __attribute__((weak));
rhock_native rhock_native225 = rhock_native_nop;
extern rhock_native rhock_native226 __attribute__((weak));
rhock_native rhock_native226 = rhock_native_nop;
extern rhock_native rhock_native227 __attribute__((weak));
rhock_native rhock_native227 = rhock_native_nop;
extern rhock_native rhock_native228 __attribute__((weak));
rhock_native rhock_native228 = rhock_native_nop;
extern rhock_native rhock_native229 __attribute__((weak));
rhock_native rhock_native229 = rhock_native_nop;
extern rhock_native rhock_native230 __attribute__((weak));
rhock_native rhock_native230 = rhock_native_nop;
extern rhock_native rhock_native231 __attribute__((weak));
rhock_native rhock_native231 = rhock_native_nop;
extern rhock_native rhock_native232 __attribute__((weak));
rhock_native rhock_native232 = rhock_native_nop;
extern rhock_native rhock_native233 __attribute__((weak));
rhock_native rhock_native233 = rhock_native_nop;
extern rhock_native rhock_native234 __attribute__((weak));
rhock_native rhock_native234 = rhock_native_nop;
extern rhock_native rhock_native235 __attribute__((weak));
rhock_native rhock_native235 = rhock_native_nop;
extern rhock_native rhock_native236 __attribute__((weak));
rhock_native rhock_native236 = rhock_native_nop;
extern rhock_native rhock_native237 __attribute__((weak));
rhock_native rhock_native237 = rhock_native_nop;
extern rhock_native rhock_native238 __attribute__((weak));
rhock_native rhock_native238 = rhock_native_nop;
extern rhock_native rhock_native239 __attribute__((weak));
rhock_native rhock_native239 = rhock_native_nop;
extern rhock_native rhock_native240 __attribute__((weak));
rhock_native rhock_native240 = rhock_native_nop;
extern rhock_native rhock_native241 __attribute__((weak));
rhock_native rhock_native241 = rhock_native_nop;
extern rhock_native rhock_native242 __attribute__((weak));
rhock_native rhock_native242 = rhock_native_nop;
extern rhock_native rhock_native243 __attribute__((weak));
rhock_native rhock_native243 = rhock_native_nop;
extern rhock_native rhock_native244 __attribute__((weak));
rhock_native rhock_native244 = rhock_native_nop;
extern rhock_native rhock_native245 __attribute__((weak));
rhock_native rhock_native245 = rhock_native_nop;
extern rhock_native rhock_native246 __attribute__((weak));
rhock_native rhock_native246 = rhock_native_nop;
extern rhock_native rhock_native247 __attribute__((weak));
rhock_native rhock_native247 = rhock_native_nop;
extern rhock_native rhock_native248 __attribute__((weak));
rhock_native rhock_native248 = rhock_native_nop;
extern rhock_native rhock_native249 __attribute__((weak));
rhock_native rhock_native249 = rhock_native_nop;
extern rhock_native rhock_native250 __attribute__((weak));
rhock_native rhock_native250 = rhock_native_nop;
extern rhock_native rhock_native251 __attribute__((weak));
rhock_native rhock_native251 = rhock_native_nop;
extern rhock_native rhock_native252 __attribute__((weak));
rhock_native rhock_native252 = rhock_native_nop;
extern rhock_native rhock_native253 __attribute__((weak));
rhock_native rhock_native253 = rhock_native_nop;
extern rhock_native rhock_native254 __attribute__((weak));
rhock_native rhock_native254 = rhock_native_nop;
extern rhock_native rhock_native255 __attribute__((weak));
rhock_native rhock_native255 = rhock_native_nop;
rhock_native rhock_native_get(uint8_t id)
{
switch (id) {
case 0:
return rhock_native0;
case 1:
return rhock_native1;
case 2:
return rhock_native2;
case 3:
return rhock_native3;
case 4:
return rhock_native4;
case 5:
return rhock_native5;
case 6:
return rhock_native6;
case 7:
return rhock_native7;
case 8:
return rhock_native8;
case 9:
return rhock_native9;
case 10:
return rhock_native10;
case 11:
return rhock_native11;
case 12:
return rhock_native12;
case 13:
return rhock_native13;
case 14:
return rhock_native14;
case 15:
return rhock_native15;
case 16:
return rhock_native16;
case 17:
return rhock_native17;
case 18:
return rhock_native18;
case 19:
return rhock_native19;
case 20:
return rhock_native20;
case 21:
return rhock_native21;
case 22:
return rhock_native22;
case 23:
return rhock_native23;
case 24:
return rhock_native24;
case 25:
return rhock_native25;
case 26:
return rhock_native26;
case 27:
return rhock_native27;
case 28:
return rhock_native28;
case 29:
return rhock_native29;
case 30:
return rhock_native30;
case 31:
return rhock_native31;
case 32:
return rhock_native32;
case 33:
return rhock_native33;
case 34:
return rhock_native34;
case 35:
return rhock_native35;
case 36:
return rhock_native36;
case 37:
return rhock_native37;
case 38:
return rhock_native38;
case 39:
return rhock_native39;
case 40:
return rhock_native40;
case 41:
return rhock_native41;
case 42:
return rhock_native42;
case 43:
return rhock_native43;
case 44:
return rhock_native44;
case 45:
return rhock_native45;
case 46:
return rhock_native46;
case 47:
return rhock_native47;
case 48:
return rhock_native48;
case 49:
return rhock_native49;
case 50:
return rhock_native50;
case 51:
return rhock_native51;
case 52:
return rhock_native52;
case 53:
return rhock_native53;
case 54:
return rhock_native54;
case 55:
return rhock_native55;
case 56:
return rhock_native56;
case 57:
return rhock_native57;
case 58:
return rhock_native58;
case 59:
return rhock_native59;
case 60:
return rhock_native60;
case 61:
return rhock_native61;
case 62:
return rhock_native62;
case 63:
return rhock_native63;
case 64:
return rhock_native64;
case 65:
return rhock_native65;
case 66:
return rhock_native66;
case 67:
return rhock_native67;
case 68:
return rhock_native68;
case 69:
return rhock_native69;
case 70:
return rhock_native70;
case 71:
return rhock_native71;
case 72:
return rhock_native72;
case 73:
return rhock_native73;
case 74:
return rhock_native74;
case 75:
return rhock_native75;
case 76:
return rhock_native76;
case 77:
return rhock_native77;
case 78:
return rhock_native78;
case 79:
return rhock_native79;
case 80:
return rhock_native80;
case 81:
return rhock_native81;
case 82:
return rhock_native82;
case 83:
return rhock_native83;
case 84:
return rhock_native84;
case 85:
return rhock_native85;
case 86:
return rhock_native86;
case 87:
return rhock_native87;
case 88:
return rhock_native88;
case 89:
return rhock_native89;
case 90:
return rhock_native90;
case 91:
return rhock_native91;
case 92:
return rhock_native92;
case 93:
return rhock_native93;
case 94:
return rhock_native94;
case 95:
return rhock_native95;
case 96:
return rhock_native96;
case 97:
return rhock_native97;
case 98:
return rhock_native98;
case 99:
return rhock_native99;
case 100:
return rhock_native100;
case 101:
return rhock_native101;
case 102:
return rhock_native102;
case 103:
return rhock_native103;
case 104:
return rhock_native104;
case 105:
return rhock_native105;
case 106:
return rhock_native106;
case 107:
return rhock_native107;
case 108:
return rhock_native108;
case 109:
return rhock_native109;
case 110:
return rhock_native110;
case 111:
return rhock_native111;
case 112:
return rhock_native112;
case 113:
return rhock_native113;
case 114:
return rhock_native114;
case 115:
return rhock_native115;
case 116:
return rhock_native116;
case 117:
return rhock_native117;
case 118:
return rhock_native118;
case 119:
return rhock_native119;
case 120:
return rhock_native120;
case 121:
return rhock_native121;
case 122:
return rhock_native122;
case 123:
return rhock_native123;
case 124:
return rhock_native124;
case 125:
return rhock_native125;
case 126:
return rhock_native126;
case 127:
return rhock_native127;
case 128:
return rhock_native128;
case 129:
return rhock_native129;
case 130:
return rhock_native130;
case 131:
return rhock_native131;
case 132:
return rhock_native132;
case 133:
return rhock_native133;
case 134:
return rhock_native134;
case 135:
return rhock_native135;
case 136:
return rhock_native136;
case 137:
return rhock_native137;
case 138:
return rhock_native138;
case 139:
return rhock_native139;
case 140:
return rhock_native140;
case 141:
return rhock_native141;
case 142:
return rhock_native142;
case 143:
return rhock_native143;
case 144:
return rhock_native144;
case 145:
return rhock_native145;
case 146:
return rhock_native146;
case 147:
return rhock_native147;
case 148:
return rhock_native148;
case 149:
return rhock_native149;
case 150:
return rhock_native150;
case 151:
return rhock_native151;
case 152:
return rhock_native152;
case 153:
return rhock_native153;
case 154:
return rhock_native154;
case 155:
return rhock_native155;
case 156:
return rhock_native156;
case 157:
return rhock_native157;
case 158:
return rhock_native158;
case 159:
return rhock_native159;
case 160:
return rhock_native160;
case 161:
return rhock_native161;
case 162:
return rhock_native162;
case 163:
return rhock_native163;
case 164:
return rhock_native164;
case 165:
return rhock_native165;
case 166:
return rhock_native166;
case 167:
return rhock_native167;
case 168:
return rhock_native168;
case 169:
return rhock_native169;
case 170:
return rhock_native170;
case 171:
return rhock_native171;
case 172:
return rhock_native172;
case 173:
return rhock_native173;
case 174:
return rhock_native174;
case 175:
return rhock_native175;
case 176:
return rhock_native176;
case 177:
return rhock_native177;
case 178:
return rhock_native178;
case 179:
return rhock_native179;
case 180:
return rhock_native180;
case 181:
return rhock_native181;
case 182:
return rhock_native182;
case 183:
return rhock_native183;
case 184:
return rhock_native184;
case 185:
return rhock_native185;
case 186:
return rhock_native186;
case 187:
return rhock_native187;
case 188:
return rhock_native188;
case 189:
return rhock_native189;
case 190:
return rhock_native190;
case 191:
return rhock_native191;
case 192:
return rhock_native192;
case 193:
return rhock_native193;
case 194:
return rhock_native194;
case 195:
return rhock_native195;
case 196:
return rhock_native196;
case 197:
return rhock_native197;
case 198:
return rhock_native198;
case 199:
return rhock_native199;
case 200:
return rhock_native200;
case 201:
return rhock_native201;
case 202:
return rhock_native202;
case 203:
return rhock_native203;
case 204:
return rhock_native204;
case 205:
return rhock_native205;
case 206:
return rhock_native206;
case 207:
return rhock_native207;
case 208:
return rhock_native208;
case 209:
return rhock_native209;
case 210:
return rhock_native210;
case 211:
return rhock_native211;
case 212:
return rhock_native212;
case 213:
return rhock_native213;
case 214:
return rhock_native214;
case 215:
return rhock_native215;
case 216:
return rhock_native216;
case 217:
return rhock_native217;
case 218:
return rhock_native218;
case 219:
return rhock_native219;
case 220:
return rhock_native220;
case 221:
return rhock_native221;
case 222:
return rhock_native222;
case 223:
return rhock_native223;
case 224:
return rhock_native224;
case 225:
return rhock_native225;
case 226:
return rhock_native226;
case 227:
return rhock_native227;
case 228:
return rhock_native228;
case 229:
return rhock_native229;
case 230:
return rhock_native230;
case 231:
return rhock_native231;
case 232:
return rhock_native232;
case 233:
return rhock_native233;
case 234:
return rhock_native234;
case 235:
return rhock_native235;
case 236:
return rhock_native236;
case 237:
return rhock_native237;
case 238:
return rhock_native238;
case 239:
return rhock_native239;
case 240:
return rhock_native240;
case 241:
return rhock_native241;
case 242:
return rhock_native242;
case 243:
return rhock_native243;
case 244:
return rhock_native244;
case 245:
return rhock_native245;
case 246:
return rhock_native246;
case 247:
return rhock_native247;
case 248:
return rhock_native248;
case 249:
return rhock_native249;
case 250:
return rhock_native250;
case 251:
return rhock_native251;
case 252:
return rhock_native252;
case 253:
return rhock_native253;
case 254:
return rhock_native254;
case 255:
return rhock_native255;
default:
return NULL;
}
};
#endif
#include "native_symbols.inc"