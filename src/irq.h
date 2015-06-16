// created 150628
/*
  * IRQ priority order (sorted by highest to lowest priority):
  *         - Lowest pre-emption priority
  *         - Lowest subpriority
  *         - Lowest hardware priority (IRQ number)
*/

// PRIORITY: koliko je vazan medju svim interruptovima
// SUBPRIORITY: Koliko je vazan medju slicnim IRQovima (npr USART1, USART2, ...)			INFO mozda i nije istina

// STM32 default priority group: 2 (2 bits for preemption, 2 bits for subpriority)
// 4 bits: b3b2b1b0		b3b2: priority	b1b0: subpriority
//
/*
 *
 *  NVIC_PriorityGroup
    NVIC_IRQChannelPreemptionPriority
    NVIC_IRQChannelSubPriority
 *
 */

#define USART1_IRQ_PRIORITY		1
#define USART1_IRQ_SUBPRIORITY	0

#define SYSTICK_IRQ_PRIORITY	0
