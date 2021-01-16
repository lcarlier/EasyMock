#ifndef STRUCTBITFIELDFUNSTRUCTBITFIELD_H
#define STRUCTBITFIELDFUNSTRUCTBITFIELD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//From https://en.wikipedia.org/wiki/Bit_field
struct BoxProps
{
  unsigned int  opaque       : 1;
  unsigned int  fill_color   : 3;
  unsigned int               : 4; // fill to 8 bits
  unsigned int  show_border  : 1;
  unsigned int  border_color : 3;
  unsigned int  border_style : 2;
  unsigned char              : 0; // fill to nearest byte (16 bits)
  unsigned char width        : 4, // Split a byte into 2 fields of 4 bits
                height       : 4;
};

struct BoxPropsContainer
{
  struct BoxProps b;
};

void voidFunStructBitfield(struct BoxPropsContainer s);

#ifdef __cplusplus
}
#endif

#endif /* STRUCTBITFIELDFUNSTRUCTBITFIELD_H */

