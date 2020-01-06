#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_
//AUTOSAR_SWS_CommunicationStackTypes.pdf

#ifndef STD_TYPES_H
#include "Std_Types.h"
#endif

typedef uint16 PduIdType;
typedef uint32 PduLengthType;
typedef uint8 NetworkHandleType;
typedef uint8 IcomConfigIdType;

typedef enum {
    TP_DATACONF = 0x00u,
    TP_DATARETRY = 0x01u,
    TP_CONFPENDING = 0x02u
} TpDataStateType;

typedef struct {
    uint8 *SduDataPtr;
    uint8 *MetaDataPtr;
    PduLengthType SduLength;
} PduInfoType;

typedef struct {
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef enum {
    ICOM_SWITCH_E_OK = 0x00u,
    ICOM_SWITCH_E_FAILED = 0x01u
} IcomSwitch_ErrorType;

typedef enum {
    TP_STMIN = 0x00u,
    TP_BS = 0x01u,
    TP_BC = 0x02u
} TPParameterType;

typedef enum {
    BUFREQ_OK = 0x00u,
    BUFREQ_E_NOT_OK = 0x01u,
    BUFREQ_E_BUSY = 0x02u,
    BUFREQ_E_OVFL = 0x03u
} BufReq_ReturnType;

#endif /* COMSTACK_TYPES_H_ */
