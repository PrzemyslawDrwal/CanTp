#ifndef INCLUDE_PDUR_H_
#define INCLUDE_PDUR_H_

extern void PduR_CanTpRxIndication(PduIdType rxPduId, Std_ReturnType result);

extern void PduR_CanTpTxConfirmation(PduIdType txPduId, Std_ReturnType result);

extern BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType rxPduId,
                                              const PduInfoType *pPduInfo,
                                              PduLengthType *pBuffer);

extern BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType txPduId,
                                              const PduInfoType *pPduInfo,
                                              const RetryInfoType *pRetryInfo,
                                              PduLengthType *pAvailableData);

extern BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType pduId,
                                                    const PduInfoType *pPduInfo,
                                                    PduLengthType tpSduLength,
                                                    PduLengthType *pBufferSize);


#endif /* INCLUDE_PDUR_H_ */
