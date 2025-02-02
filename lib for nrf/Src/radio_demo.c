#include <memory.h>
#include "support.h"
#include "nrf24.h"
#include "stdint.h"
#include "stdio.h"
#include "frame_uart.h"
#define RX_SINGLE 0
#define TX_SINGLE 1
uint8_t data[FRAME_DATA_TX];
uint8_t pdest[FRAME_DATA_TX_HANDLE];
uint16_t len;
extern uint32_t value[5];
extern UART_HandleTypeDef huart1;

void Toggle_LED()
{
    //HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
}

NRF_Packet payload_packet;
uint8_t payload_length = sizeof(payload_packet);

uint32_t convert_to_us(uint32_t val, uint32_t min, uint32_t middle, uint32_t max)
{
    if (val > max)
        val = max;
    if (val < min)
        val = min;
    if (val < middle)
        return (val - min) * (1500 - 1000) / (middle - min) + 1000;
    else
        return (val - middle) * (2000 - 1500) / (max - middle) + 1500;
}

// Kinda foolproof :)
#if ((RX_SINGLE + TX_SINGLE) != 1)
#error "Define only one DEMO_xx, use the '1' value"
#endif

#if ((TX_SINGLE))

// Helpers for transmit mode demo

// Timeout counter (depends on the CPU speed)
// Used for not stuck waiting for IRQ
#define nRF24_WAIT_TIMEOUT (uint32_t)0x000FFFFF

// Result of packet transmission
typedef enum
{
    nRF24_TX_ERROR = (uint8_t)0x00,
    nRF24_TX_SUCCESS,
    nRF24_TX_TIMEOUT,
    nRF24_TX_MAXRT
} nRF24_TXResult;

// Length of received payload

nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length)
{
    volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
    uint8_t status;
    nRF24_CE_L();
    nRF24_WritePayload(pBuf, length);
    nRF24_CE_H();

    do
    {
        status = nRF24_GetStatus();
        if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT))
        {
            break;
        }
    } while (wait--);
    nRF24_CE_L();

    if (!wait)
        return nRF24_TX_TIMEOUT;

    nRF24_ClearIRQFlags();

    if (status & nRF24_FLAG_MAX_RT)
        return nRF24_TX_MAXRT;

    if (status & nRF24_FLAG_TX_DS)
        return nRF24_TX_SUCCESS;

    nRF24_FlushTX();

    return nRF24_TX_ERROR;
}
void reset_controller(void)
{
    payload_packet.throttle = 0;
    payload_packet.yaw = 127;
    payload_packet.pitch = 127;
    payload_packet.roll = 127;
    payload_packet.button = 0;
    payload_packet.button_1 = 0;
}

#endif // DEMO_TX_

int runRadio(void)
{
#if (DEBUG_FC)
    printf("\r\nSTM32 is online.\r\n");
#endif // debug
    nRF24_CE_L();
#if (DEBUG_FC)
    printf("nRF24L01+ check: ");
#endif
        while (!nRF24_Check())
        {
            Toggle_LED();
            Delay_ms(50);
#if (DEBUG_FC)
            printf("FAIL\r\n");
#endif
        }
    nRF24_Init();
#if (DEBUG_FC)
    printf("OK\r\n");
#endif

    // nRF24_CE_L();

/***************************************************************************/
#if (RX_SINGLE)

    nRF24_SetRFChannel(40);
    nRF24_SetDataRate(nRF24_DR_2Mbps);
    nRF24_SetCRCScheme(nRF24_CRC_2byte);
    nRF24_SetAddrWidth(3);
    static const uint8_t nRF24_ADDR[] = {'E', 'S', 'B'};
    nRF24_SetAddr(nRF24_PIPE1, nRF24_ADDR);
    nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 24);
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);
    nRF24_SetOperationalMode(nRF24_MODE_RX);
    nRF24_ClearIRQFlags();
    nRF24_SetPowerMode(nRF24_PWR_UP);
    nRF24_CE_H();
    // payload_length = sizeof(payload_packet);

    // The main loop

#endif // RX_SINGLE

    /***************************************************************************/

#if (TX_SINGLE)

    nRF24_SetRFChannel(40);
    nRF24_SetDataRate(nRF24_DR_2Mbps);
    nRF24_SetCRCScheme(nRF24_CRC_2byte);
    nRF24_SetAddrWidth(3);
    static const uint8_t nRF24_ADDR[] = {'E', 'S', 'B'};
    nRF24_SetAddr(nRF24_PIPETX, nRF24_ADDR);
    nRF24_SetAddr(nRF24_PIPE0, nRF24_ADDR);
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);
    nRF24_SetAutoRetr(nRF24_ARD_2500us, 10);
    nRF24_EnableAA(nRF24_PIPE0);
    nRF24_SetOperationalMode(nRF24_MODE_TX);
    nRF24_ClearIRQFlags();
    nRF24_SetPowerMode(nRF24_PWR_UP);

    // payload_length = sizeof(payload_packet);
    reset_controller();
    while (1)
    {

        payload_packet.throttle = convert_to_us(value[0], 700, 1697, 4095);
        payload_packet.roll = convert_to_us(value[1], 800, 2530, 4095);
        payload_packet.pitch = convert_to_us(value[2], 250, 2370, 4095);
        payload_packet.yaw = convert_to_us(value[3], 0, 2570, 4095);
#if (DEBUG_FC)
        printf("value: %ld  %ld  %ld  %ld\n", payload_packet.throttle, payload_packet.roll, payload_packet.pitch, payload_packet.yaw);
        printf("value: %ld  %ld  %ld  %ld\n", value[0], value[1], value[2], value[3]);
#endif // debug

        nRF24_TXResult result = nRF24_TransmitPacket((uint8_t *)&payload_packet, payload_length);

        switch (result)
        {
        case nRF24_TX_SUCCESS:
            // todo: đã truyền thành công
            break;
        case nRF24_TX_MAXRT:
            nRF24_ResetPLOS();
            break;
        case nRF24_TX_TIMEOUT:
        default:
            // todo: Bị lỗi khi truyền đi
            break;
        }

//        sprintf((char*)data,"%d%d", (uint16_t)payload_packet.throttle, (uint16_t)payload_packet.roll);
//        SendFrameData(data, FRAME_DATA_TX, pdest,&len );
//        HAL_UART_Transmit(&huart1, pdest, len, 1000);

        //Toggle_LED();
        ////Delay_ms(100);
    }

#endif // TX_SINGLE
}

void RX_data(void)
{

    if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
    {
        nRF24_RXResult pipe = nRF24_ReadPayload((uint8_t *)&payload_packet, &payload_length);
        // Clear all pending IRQ flags
        nRF24_ClearIRQFlags();
        Toggle_LED();
#if DEBUG_FC
        printf("Pipe: %d\n", pipe);
        printf("value: %ld  %ld  %ld  %ld\n", payload_packet.throttle, payload_packet.roll, payload_packet.pitch, payload_packet.yaw);
#endif // debug
    }
    else
    {
        // todo:
    }
}
