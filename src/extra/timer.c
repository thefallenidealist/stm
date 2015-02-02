#define __GPTIMER_INIT_C
/****************************************************************************/
/*    FILE: GPTIMER_init.c                                                  */
/*                                                                          */
/*    A general purpose C/C++ timer object                                  */
/*                                                                          */
/*    BY:   Ken Wada                                                        */
/*          12-January-2003                                                 */
/*                                                                          */
/****************************************************************************/
#include  "timer.h"
#include "delay.h"

/****************************************************************************/
void GPTIMER_init (GPTIMER *_this, const unsigned long tics)
{
    _this->timeOut    = tics;
    _this->lastCount  = get_uptime_ms();
    _this->timedOut   = 0;
}

/****************************************************************************/
int GPTIMER_isTimedOut (GPTIMER *_this)
{
    if (!(_this->timedOut))
    {
      _this->timedOut = ( get_uptime_ms()-_this->lastCount >= _this->timeOut );
    }
    return (0!=_this->timedOut);
}

/****************************************************************************/
void  GPTIMER_reTrigger (GPTIMER *_this)
{
    _this->lastCount  = get_uptime_ms();
    _this->timedOut   = 0;
}

static GPTIMER my_1second_timer;

extern void do_1second_update (void);
extern void initialize_hw_timerService (void);  // initialize system tick

/****************************************************************************/
void update_process (void)
{
    if (GPTIMER_isTimedOut(&my_1second_timer))  // is it timed out?
    {
      GPTIMER_reTrigger (&my_1second_timer);    // retrigger the timer
      do_1second_update ();                     // do some update
    }
}


/****************************************************************************/
void timer_example(void)	// main
{
    initialize_hw_timerService ();   // initialize system tick
    GPTIMER_init (&my_1second_timer, 1000);  // initialize for 1 second

    while (1)
    {
      update_process ();
    }
}
