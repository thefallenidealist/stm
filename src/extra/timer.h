// http://www.embedded.com/electronics-blogs/embedded-round-table/4405060/2/Soft-timers-in-object-oriented-C
#ifndef __GPTIMER_H
    #define   __GPTIMER_H
/****************************************************************************/
/*    FILE: gpTimer.h                                                       */
/*                                                                          */
/*    A general purpose C/C++ timer object                                  */
/*                                                                          */
/*    BY:   Ken Wada                                                        */
/*          12-January-2013                                                 */
/*                                                                          */
/****************************************************************************/
    #define   GP_MSEC_PER_TIC     1     /* Each TIC == 1 millisecond        */
    #define   TIC_PER_SEC         (1000/GP_MSEC_PER_TIC)
    typedef unsigned char (*TMR_IDLEFN)(void);
/****************************************************************************/
/*    A structure that defines a generic timer type.                        */
/****************************************************************************/
typedef struct general_purpose_timer_object  
{
	unsigned long lastCount;          /* Last saved count for this timer  */
	unsigned long timeOut;            /* Number of tics to timeout        */
	unsigned char timedOut;           /* time-out status                  */
} GPTIMER;

void  GPTIMER_init            (GPTIMER *_this, const unsigned long tics);
void  GPTIMER_reTrigger       (GPTIMER *_this);
int   GPTIMER_isTimedOut      (GPTIMER *_this);
//      void  GPTIMER_waitForTick   (GPTIMER *_this);
//      long  GPTIMER_timeLeft      (GPTIMER *_this);
//      void  GPTIMER_waitForTick_fn(GPTIMER *_this, TMR_IDLEFN idle_fn);

/*****
The following are the system call-backs needed for this library
***/
//unsigned long sysRetrieveClock    (void);

void update_process (void);


#endif

