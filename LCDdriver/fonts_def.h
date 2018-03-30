#ifndef _FONTS_DEF
#define _FONTS_DEF

#include <inttypes.h>

#define uint_8 uint8_t

////////////////////////////////////////////////////////////////////////////////
typedef struct// _font_char_info
{
   uint_8 CharWidth;
   int Offset;
}FONT_CHAR_INFO;
////////////////////////////////////////////////////////////////////////////////
typedef struct// _font_info
{
   uint_8 CharacterHeight;
   char StartCharacter;
   char EndCharacter;
   FONT_CHAR_INFO *Descriptors;
   uint_8 *Bitmaps;
}FONT_INFO;
////////////////////////////////////////////////////////////////////////////////
#endif//FONTS_DEF
