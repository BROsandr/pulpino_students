#ifndef _KUZNECHIK_H_
#define _KUZNECHIK_H_

#include <pulpino.h>

#define KUZNECHIK_REG_RST                   ( KUZNECHIK_BASE_ADDR + 0x00 )
#define KUZNECHIK_REG_CLKDIV                ( KUZNECHIK_BASE_ADDR + 0x04 )
#define KUZNECHIK_REG_SPICMD                ( KUZNECHIK_BASE_ADDR + 0x08 )
#define KUZNECHIK_REG_SPIADR                ( KUZNECHIK_BASE_ADDR + 0x0C )
#define KUZNECHIK_REG_SPILEN                ( KUZNECHIK_BASE_ADDR + 0x10 )
#define KUZNECHIK_REG_SPIDUM                ( KUZNECHIK_BASE_ADDR + 0x14 )
#define KUZNECHIK_REG_TXFIFO                ( KUZNECHIK_BASE_ADDR + 0x18 )
#define KUZNECHIK_REG_RXFIFO                ( KUZNECHIK_BASE_ADDR + 0x20 )
#define KUZNECHIK_REG_INTCFG                ( KUZNECHIK_BASE_ADDR + 0x24 )
#define KUZNECHIK_REG_INTSTA                ( KUZNECHIK_BASE_ADDR + 0x28 )

#endif // _KUZNECHIK_H_
