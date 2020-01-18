#ifndef INCLUDE_CANTP_CBK_H_
#define INCLUDE_CANTP_CBK_H_

void CanTp_RxIndication(PduIdType rxPduId, const PduInfoType *pPduInfo);

void CanTp_TxConfirmation(PduIdType txPduId, Std_ReturnType result);


#endif /* INCLUDE_CANTP_CBK_H_ */
