//#include <msp430.h>
#include <stdio.h>
#include <stdint.h>

#define eUSCI_A_BASE        0x0000
#define USCA_CTLW0_OFFSET   0x00
#define USCA_CTL0_OFFSET    0x00
#define USCA_CTL1_OFFSET    0x01
#define UCS_BRW_OFFSET      0x06
#define UCA_BR0_OFFSET      0x06
#define UCA_BR1_OFFSET      0x07
#define UCA_STATW_OFFET     0x0A
#define UCA_RXBUF_OFFSET    0x0C
#define UCA_TXBUF_OFFSET    0x0E
#define UCA_IE_OFFSET       0x1A
#define UCA_IFG_OFFSET      0x1C
#define UCA_IV_OFFET        0x1E

typedef struct {
    uint16_t UCCKPH :1;
    uint16_t UCCKPL :1;
    uint16_t UCMSB :1;
    uint16_t UC7BIT :1;
    uint16_t UCMST :1;
    uint16_t UCMODEx :2;
    uint16_t UCSYNC :1;
    uint16_t UCSSELx :2;
    const uint16_t  :4;
    uint16_t UCSTEM :1;
    uint16_t UCSWRST :1;
}SCI_Control;


typedef struct {
    uint16_t UCBRx;
}SCI_BitRate_Control;

typedef struct {
    uint16_t :8;
    uint16_t UCLISTEN :1;
    uint16_t UCFE :1;
    uint16_t UCOE :1;
    uint16_t :5;
    const uint16_t UCBUSY :1;
}SCI_Status;

typedef struct {
    const uint16_t  :8;
    const uint16_t  UCRXBUFx :8;
}SCI_RX;

typedef struct {
    const uint16_t  :8;
    uint16_t UCTXBUF :8;
}SCI_TX;

typedef struct {
    const uint16_t  :14;
    uint16_t UCTX :1;
    uint16_t UCRX :1;
}SCI_Interrupt;

typedef struct {
    const uint16_t  UCIVx;
}SCI_Interrupt_Vector;

static volatile SCI_Control * const SPI_A_WORD_CONTROL = (SCI_Control*)(eUSCI_A_BASE + USCA_CTLW0_OFFSET);
static volatile SCI_BitRate_Control * const SPI_A_BIT_RATE_WORD_CONTROL = (SCI_BitRate_Control*)(eUSCI_A_BASE + UCS_BRW_OFFSET);
static volatile SCI_Status * const SPI_A_STATUS = (SCI_Status*)(eUSCI_A_BASE + UCA_STATW_OFFET);
static volatile SCI_RX * const SPI_A_RX_BUFFER = (SCI_RX*)(eUSCI_A_BASE + UCA_RXBUF_OFFSET);
static volatile SCI_TX * const SPI_A_TX_BUFFER = (SCI_TX*)(eUSCI_A_BASE + UCA_TXBUF_OFFSET);
static volatile SCI_Interrupt * const SPI_A_INTERRUPT_ENABLE = (SCI_Interrupt*)(eUSCI_A_BASE + UCA_IE_OFFSET);
static volatile SCI_Interrupt * const SPI_A_INTERRUPT_FLAG = (SCI_Interrupt*)(eUSCI_A_BASE + UCA_IFG_OFFSET);
static volatile SCI_Interrupt_Vector * const SPI_A_INTERRUPT_VECTOR = (SCI_Interrupt_Vector*)(eUSCI_A_BASE + UCA_IV_OFFET);

/**
 * main.c
 */
int main(void)
{
	//WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    SPI_A_WORD_CONTROL->UCMODEx = 0x00;
    SPI_A_BIT_RATE_WORD_CONTROL->UCBRx = 0x00;
    SPI_A_STATUS->UCFE = 0x00;
    uint16_t temp = SPI_A_RX_BUFFER->UCRXBUFx;
    SPI_A_TX_BUFFER->UCTXBUF = 0x00;
    SPI_A_INTERRUPT_ENABLE->UCTX = 0x01;
    SPI_A_INTERRUPT_FLAG->UCRX = 0x01;
    uint16_t test = SPI_A_INTERRUPT_VECTOR->UCIVx;

	return 0;
}
