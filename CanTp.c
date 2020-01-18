#include "CanTp.h"
#include "CanTp_Cfg.h"

#ifndef CANTP_CBK_H
#include "CanTp_Cbk.h"
#endif /* #ifndef CANTP_CBK_H */

#ifndef COMSTACK_TYPES_H
#include "ComStack_Types.h"
#endif /* #ifndef COMSTACK_TYPES_H */

#ifndef PDUR_H
#include "PduR.h"
#endif /* #ifndef PDUR_H */

typedef enum
{
    CANTP_WAIT = 0x00u,
    CANTP_PROCESSING
} CanTp_TaskStateType;

typedef struct
{
    uint8 can[0x08u];
    PduLengthType size;
    PduLengthType rmng;
} CanTp_NSduBufferType;

typedef enum
{
    CANTP_FRAME_STATE_INVALID = 0x00u,
    CANTP_RX_FRAME_STATE_FC_TX_REQUEST,
    CANTP_RX_FRAME_STATE_FC_TX_CONFIRMATION,
    CANTP_RX_FRAME_STATE_FC_OVFLW_TX_CONFIRMATION,
    CANTP_RX_FRAME_STATE_CF_RX_INDICATION,
    CANTP_TX_FRAME_STATE_SF_TX_REQUEST,
    CANTP_TX_FRAME_STATE_SF_TX_CONFIRMATION,
    CANTP_TX_FRAME_STATE_FF_TX_REQUEST,
    CANTP_TX_FRAME_STATE_FF_TX_CONFIRMATION,
    CANTP_TX_FRAME_STATE_CF_TX_REQUEST,
    CANTP_TX_FRAME_STATE_CF_TX_CONFIRMATION,
    CANTP_TX_FRAME_STATE_FC_RX_INDICATION,
    CANTP_FRAME_STATE_OK,
    CANTP_FRAME_STATE_ABORT
} CanTp_FrameStateType;

typedef struct
{
    const CanTpRxNSdu *cfg;
    CanTp_NSduBufferType buf;
    uint8 meta_data_lower[0x04u];
    uint8 meta_data_upper[0x04u];
    CanTpNSa saved_n_sa;
    CanTpNTa saved_n_ta;
    CanTpNAe saved_n_ae;
    boolean has_meta_data;
    uint8  fs;
    uint32 st_min;
    uint8 bs;
    uint8 sn;
    uint16 wft_max;
    PduInfoType can_if_pdu_info;
    PduInfoType pdu_r_pdu_info;
    struct
    {
        CanTp_TaskStateType taskState;
        CanTp_FrameStateType state;
        struct
        {
            uint32 st_min;
            uint8 bs;
        } m_param;
    } shared;
} CanTpRxConnection;

typedef struct
{
    const CanTpTxNSdu *cfg;
    CanTp_NSduBufferType buf;
    uint8 meta_data[0x04u];
    CanTpNSa saved_n_sa;
    CanTpNTa saved_n_ta;
    CanTpNAe saved_n_ae;
    boolean has_meta_data;
    uint8  fs;
    uint32 target_st_min;
    uint32 st_min;
    uint16 bs;
    uint8 sn;
    PduInfoType can_if_pdu_info;
    CanTp_TaskStateType taskState;
    struct
    {
        CanTp_FrameStateType state;
        uint32 flag;
    } shared;
} CanTpTxConnection;

typedef struct
{
	CanTpRxConnection rx;
	CanTpTxConnection tx;
    uint32 n[0x06u];
    uint8_least dir;
    uint32 t_flag;
} CanTp_NSduType;

typedef struct
{
	CanTp_NSduType sdu[CANTP_MAX_NUM_OF_N_SDU];
} CanTp_ChannelRtType;

typedef struct
{
	CanTpRxConnection rx;
	CanTpTxConnection tx;
    uint32 n[0x06u];
    uint8_least dir;
    uint32 t_flag;
} CanTp_NSduType;

CanTp_StateType CanTpState = CANTP_OFF;
static const CanTpConfig *CanTpConfigPtr = NULL_PTR;
static CanTp_ChannelRtType CanTpRt[CANTP_MAX_NUM_OF_CHANNEL];

void CanTp_Init(const CanTpConfig *CfgPtr)
{
	uint32_least counter;
    uint32_least channel_counter;
    uint32_least rt_sdu_counter;
    uint32_least cfg_sdu_counter;
    const CanTpChannel *p_cfg_cha;
    const CanTpRxNSdu *p_cfg_rx_sdu;
    const CanTpTxNSdu *p_cfg_tx_sdu;
    CanTp_ChannelRtType *p_rt_cha;
    CanTp_NSduType *p_rt_sdu;
    uint8 *p_cleared_data = (uint8 *)&CanTpRt[0x00u];
    uint32_least temp = sizeof(CanTpRt);

    if (CfgPtr != NULL_PTR) {
        CanTpConfigPtr = CfgPtr;

        for (counter = 0x00u; counter < temp; counter++) {
            p_cleared_data[counter] = 0x00u;
        }
        for ( channel_counter = 0x00u; channel_counter < CfgPtr->maxChannelCnt; channel_counter++) {
            p_rt_cha = &CanTpRt[channel_counter];
            p_cfg_cha = &CfgPtr->pChannel[channel_counter];

            for (rt_sdu_counter = 0x00u; rt_sdu_counter < CANTP_MAX_NUM_OF_N_SDU; rt_sdu_counter++) {
                for (cfg_sdu_counter = 0x00u; cfg_sdu_counter < p_cfg_cha->nSdu.txNSduCnt; cfg_sdu_counter++) {
                    p_cfg_tx_sdu = &p_cfg_cha->nSdu.tx[cfg_sdu_counter];
                    if (p_cfg_tx_sdu->nSduId == rt_sdu_counter) {
                        p_rt_sdu->tx.taskState = CANTP_WAIT;
                        p_rt_sdu->dir |= CANTP_TX;
                        p_rt_sdu = &p_rt_cha->sdu[p_cfg_tx_sdu->nSduId];
                        p_rt_sdu->tx.cfg = p_cfg_tx_sdu;
                    }
                }
                for (cfg_sdu_counter = 0x00u; cfg_sdu_counter < p_cfg_cha->nSdu.rxNSduCnt; cfg_sdu_counter++) {
                    p_cfg_rx_sdu = &p_cfg_cha->nSdu.rx[cfg_sdu_counter];
                    if (p_cfg_rx_sdu->nSduId == rt_sdu_counter) {
                        p_rt_sdu = &p_rt_cha->sdu[p_cfg_rx_sdu->nSduId];
                        p_rt_sdu->rx.shared.taskState = CANTP_WAIT;
                        p_rt_sdu->dir |= CANTP_RX;
                        p_rt_sdu->rx.cfg = p_cfg_rx_sdu;
                        p_rt_sdu->rx.shared.m_param.st_min = p_cfg_rx_sdu->sTMin;
                        p_rt_sdu->rx.shared.m_param.bs = p_cfg_rx_sdu->bs;
                    }
                }
            }
        }

        CanTpState = CANTP_ON;
    }
}
