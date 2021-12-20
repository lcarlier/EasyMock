#ifndef STRUCTBITFIELDFUNSTRUCTBITFIELD_H
#define STRUCTBITFIELDFUNSTRUCTBITFIELD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int t_uint;

//From https://en.wikipedia.org/wiki/Bit_field
struct BoxProps
{
  unsigned int  opaque       : 1;
  unsigned int  fill_color   : 3;
  unsigned int               : 4; // fill to 8 bits
  unsigned int  show_border  : 1;
  t_uint        border_color : 3;
  unsigned int  border_style : 2;
  unsigned char              : 0; // fill to nearest byte (16 bits)
  unsigned char width        : 4, // Split a byte into 2 fields of 4 bits
                height       : 4;
  uint64_t      bit64_0      : 1;
  uint64_t      bit64_1      : 1;
  uint64_t      rest64       : 62;
  uint32_t      bit32_0      : 1;
  uint32_t      bit32_1      : 1;
  uint32_t      rest32       : 30;
  uint16_t      bit16_0      : 1;
  uint16_t      bit16_1      : 1;
  uint16_t      rest16       : 14;
  uint8_t       bit8_0       : 1;
  uint8_t       bit8_1       : 1;
  uint8_t       rest8        : 6;
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
