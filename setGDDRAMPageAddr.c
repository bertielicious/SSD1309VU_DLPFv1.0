#include "constVar.h"
#include "writeSPIcommand.h"
void setGDDRAMPageAddr(uint8_t page)
{
    uint8_t pageAddr = 0;
    uint8_t pageOffset = 0xb0;
    pageAddr =  pageOffset|page;
    writeSPIcommand(pageAddr);
}
