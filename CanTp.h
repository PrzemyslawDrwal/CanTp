#ifndef INCLUDE_CANTP_H_
#define INCLUDE_CANTP_H_

typedef enum {
	CANTP_MODE_FULL_DUPLEX,
	CANTP_MODE_HALF_DUPLEX
} CanTpChannelMode;

typedef enum{
    CANTP_EXTENDED,
    CANTP_MIXED,
    CANTP_MIXED29BIT,
    CANTP_NORMALFIXED,
    CANTP_STANDARD
} CanTpRxAddressingFormat;

typedef enum
{
    CANTP_OFF,
    CANTP_ON
} CanTpRxPaddingActivation;

typedef enum
{
    CANTP_OFF,
    CANTP_ON
} CanTpTxPaddingActivation;

#endif /* INCLUDE_CANTP_H_ */
