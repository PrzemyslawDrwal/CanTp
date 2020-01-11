#ifndef INCLUDE_CANTP_H_
#define INCLUDE_CANTP_H_

typedef enum {
	CANTP_MODE_FULL_DUPLEX,
	CANTP_MODE_HALF_DUPLEX
	/* This container contains the configuration parameters of the CanTp channel. */
} CanTpChannelMode;

typedef enum {
    CANTP_EXTENDED, 	/* Extended addressing format */
    CANTP_MIXED,		/* Mixed 11 bit addressing format */
    CANTP_MIXED29BIT,	/* Mixed 29 bit addressing format */
    CANTP_NORMALFIXED,	/* Normal fixed addressing format */
    CANTP_STANDARD		/* Normal addressing format */
	/* Declares which communication addressing models supported for this RxNSdu. */
} CanTpRxAddressingFormat;

typedef enum {
    CANTP_OFF,
    CANTP_ON
	/* Defines if the receive frame uses padding or not. This parameter is restricted to 8 byte N-PDUs */
} CanTpRxPaddingActivation;

typedef enum {
    CANTP_OFF,
    CANTP_ON
} CanTpTxPaddingActivation;

typedef enum {
    CANTP_FUNCTIONAL,
    CANTP_PHYSICAL /* Declares the communication type of this TxNsdu */
} CanTpTxTaType;

typedef struct {
    uint8 nSa;
} CanTpNSa;

typedef struct {
    uint8 nTa;
} CanTpNTa;

typedef struct {
    uint8 nAe;
} CanTpNAe;

typedef struct{
    const uint32 rxFcNPduRef;
    const uint16 rxFcNPduId;
} CanTpRxFcNPdu;

typedef struct{
    const uint32 fcNPduRef;
    const uint16 fcNPduId; /* Used for grouping of the ID of a PDU and the Reference to a PDU */
} CanTpTxFcNPdu;

typedef struct {

    const uint16 nSduId;
    const CanTpNSa *pNSa;
    const CanTpNTa *pNTa;
    const CanTpNAe *pNAe;
    const uint8 bs;
    const uint32 nar;
    const uint32 nbr;
    const uint32 ncr;
    const uint16 wftMax;
    const uint32 sTMin;
    const CanTpRxAddressingFormat af;
    const CanTpRxPaddingActivation padding;
    const CanTpTxTaType taType;
    const PduIdType rxNSduRef;
    /* The following parameters needs to be configured for each CAN N-SDU that the CanTp module receives via the CanTpChannel */
} CanTpRxNSdu;

typedef struct {

    const uint16 nSduId;
    const CanTpNSa *pNSa;
    const CanTpNTa *pNTa;
    const CanTpNAe *pNAe;
    const uint32 nas;
    const uint32 nbs;
    const uint32 ncs;
    const boolean tc;
    const CanTpRxAddressingFormat af;
    const CanTpTxPaddingActivation padding;
    const CanTpTxTaType taType;
    const uint32 txNSduRef;
    /* The following parameters needs to be configured for each CAN N-SDU that the CanTp module transmits via the CanTpChannel */
} CanTpTxNSdu;

typedef struct {
    const uint16 id;
    const uint32 rxNPduId; /* Used for grouping of the ID of a PDU and the Reference to a PDU. */
} CanTpRxNPdu;

typedef struct {
    const uint32 pduRef;
    const uint16 pduConfirmationPduId; /* Used for grouping of the ID of a PDU and the Reference to a PDU. */
} CanTpTxNPdu;

typedef struct {
    struct {
        const CanTpRxNSdu *rx;
        const uint32 rxNSduCnt;
        const CanTpTxNSdu *tx;
        const uint32 txNSduCnt;
    } nSdu;
    const CanTpChannelMode channelMode;
    /* This container contains the configuration parameters of the CanTp channel. */
} CanTpChannel;


typedef struct {
    const uint32 mainFunctionPeriod;
    const uint32 maxChannelCnt;
    const CanTpChannel *pChannel;
    const uint8 paddingByte;
    /* This container contains the configuration parameters and sub containers of the AUTOSAR CanTp module */
} CanTpConfig;

#endif /* INCLUDE_CANTP_H_ */
