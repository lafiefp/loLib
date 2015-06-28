/**
 * @file   UartIf.c
 * @author Thomas Pfeiffer
 * @date   Jun 28, 2015
 * @brief
 */
#include "UartIf.h"
#include "../Debug.h"

void uart_init(TUart const * pUart,
      TUartConfiguration const * const pConfiguration)
{
   ASSERT(pUart != 0);
   ASSERT(pConfiguration != 0);

   ASSERT(pUart->pDevInit(pUart->channel, &pUart->config));
}

TUartBufferSize uart_put_data(TUart const * pUart, TUartDataType const * pData,
      TUartBufferSize length)
{
   ASSERT(pUart != 0);
   ASSERT(pUart->tx.buffer != 0);
   ASSERT(pData != 0);
   ASSERT(length > 0);

   TUartBufferSize i;
   TUartBufferType * tx = &pUart->tx;

   for (i = 0; (i < length) && (tx->space > 0); i++, pData++)
   {
      tx->buffer[tx->wrIdx] = *pData;
      tx->wrIdx = (tx->wrIdx + 1) % tx->size;
      tx->space--;
   }

   pUart->fpIoCtl(pUart->channel, eEnableTx, 0);

   return i;
}

TUartBufferSize uart_get_data(TUart const * pUart,
      TUartDataType const * const pData, TUartBufferSize length)
{
   ASSERT(pUart != 0);
   ASSERT(pUart->rx.buffer != 0);
   ASSERT(pData != 0);
   ASSERT(length > 0);

   TUartBufferSize i;
   TUartBufferType * rx = &pUart->rx;

   for (i = 0; (i < length) && (rx->space < rx->size); i++, pData++)
   {
      *pData = rx->buffer[rx->rdIdx];
      rx->rdIdx = (rx->rdIdx + 1) % rx->size;
      rx->space++;
   }

   return i;
}
