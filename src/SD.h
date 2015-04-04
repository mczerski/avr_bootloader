#ifndef SD_H
#define SD_H

#define CARD_A_DETECT ((PINB & 0x08) >> PB3)
#define CARD_B_DETECT ((PINB & 0x04) >> PB2)

void initSD(void);

#endif
