#ifndef INCLUDE_CANTP_H_
#define INCLUDE_CANTP_H_

typedef enum {
	CANTP_MODE_FULL_DUPLEX,
	CANTP_MODE_HALF_DUPLEX
} CanTpChannelMode;

typedef enum {
    CANTP_EXTENDED,
    CANTP_MIXED,
    CANTP_MIXED29BIT,
    CANTP_NORMALFIXED,
    CANTP_STANDARD
} CanTpRxAddressingFormat;

typedef enum {
    CANTP_OFF,
    CANTP_ON
} CanTpRxPaddingActivation;

typedef enum {
    CANTP_OFF,
    CANTP_ON
} CanTpTxPaddingActivation;

typedef enum {
    CANTP_FUNCTIONAL,
    CANTP_PHYSICAL
} CanTpTxTa;

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
    const uint16 fcNPduId;
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
    const CanTpTxTa taType;
    const PduIdType rxNSduRef;

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
    const CanTpTxTa taType;
    const uint32 txNSduRef;

} CanTpTxNSdu;

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
    const CanTpTxTa taType;
    const uint32 txNSduRef;

} CanTpTxNSdu;

typedef struct {
    const uint16 id;
    const uint32 rxNPduId;
} CanTpRxNPdu;

typedef struct {
    const uint32 pduRef;
    const uint16 pduConfirmationPduId;
} CanTpTxNPdu;

typedef struct {
    struct {
        const CanTpRxNSdu *rx;
        const uint32 rxNSduCnt;
        const CanTpTxNSdu *tx;
        const uint32 txNSduCnt;
    } nSdu;
    const CanTpChannelMode channelMode;
} CanTpChannel;


typedef struct {
    const uint32 mainFunctionPeriod;
    const uint32 maxChannelCnt;
    const CanTpChannel *pChannel;
    const uint8 paddingByte;
} CanTp_ConfigType;

#endif /* INCLUDE_CANTP_H_ */
