/* FastEmbedded Microcontroller Library
 * Copyright (c) 2018 Gene Kong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "osTimer.h"

#ifndef FE_PARENT_OBJECT
//  type:   father object type.
// sitem:   child name in father object type.
//   obj:   child object pointer
#define FE_PARENT_OBJECT(type, sitem, obj) \
    (type *)(((size_t)obj) - ((size_t) &(((type *)NULL)->sitem)))
#endif

namespace FEmbed {

static void TimerCallback(TimerHandle_t timer)
{
    OSTimer *os_timer = FE_PARENT_OBJECT(OSTimer, m_timer, timer);
    os_timer->expired();
}

OSTimer::OSTimer(OSTimerCallback *cb, bool reload, const char *name)
{
    uint32_t timer_id;
    TimerHandle_t timer = xTimerCreateStatic(
            name,
            1,
            reload? pdTRUE : pdFALSE,
            &timer_id,
            TimerCallback,
            &this->m_timer);
    assert((TimerHandle_t) &this->m_timer == timer);
    assert(this == FE_PARENT_OBJECT(OSTimer, m_timer, timer));
    m_cb = cb;
    m_runnig = false;
}

OSTimer::~OSTimer()
{
	this->stop();
	//xTimerDelete((TimerHandle_t) &this->m_timer, 0);
}

bool OSTimer::start(uint32_t ms)
{
    portTickType ticks = ms / portTICK_RATE_MS;
    if(FE_IS_IN_ISR())
    {
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        if (xTimerChangePeriodFromISR((TimerHandle_t) &this->m_timer, ticks, &xHigherPriorityTaskWoken) != pdPASS)
            return false;
        else
        {
            if (xTimerStartFromISR((TimerHandle_t) &this->m_timer, &xHigherPriorityTaskWoken) != pdPASS)
                return false;
        }
    }
    else
    {
        if (xTimerChangePeriod((TimerHandle_t) &this->m_timer, ticks, portMAX_DELAY) != pdPASS)
            return false;
        else
        {
            if (xTimerStart((TimerHandle_t) &this->m_timer, portMAX_DELAY) != pdPASS)
                return false;
        }
    }
    m_runnig = true;
    return true;
}

bool OSTimer::stop()
{
    if(FE_IS_IN_ISR())
    {
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        if (xTimerStopFromISR((TimerHandle_t) &this->m_timer, &xHigherPriorityTaskWoken) != pdPASS) {
            return false;
        }
    }
    else
    {
        if (xTimerStop((TimerHandle_t) &this->m_timer, portMAX_DELAY) != pdPASS) {
            return false;
        }
    }
    m_runnig = false;
    return true;
}

bool OSTimer::isRun()
{
    return xTimerIsTimerActive((TimerHandle_t) &this->m_timer) == pdTRUE?true:false;
}

uint32_t OSTimer::period()
{
    return xTimerGetPeriod((TimerHandle_t) &this->m_timer);
}

uint32_t OSTimer::expiryTime()
{
    if(m_runnig)
        return xTimerGetExpiryTime((TimerHandle_t) &this->m_timer);
    return 0;
}


bool OSTimer::reset()
{
    bool ret = true;
    if(FE_IS_IN_ISR())
    {
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        if(xTimerResetFromISR((TimerHandle_t) &this->m_timer, &xHigherPriorityTaskWoken ) != pdPASS)
            ret = false;
    }
    else
    {
        if(xTimerReset((TimerHandle_t) &this->m_timer, portMAX_DELAY) != pdPASS)
            ret = false;
    }
    return ret;
}

void OSTimer::expired()
{
    if(this->m_cb != NULL)
        this->m_cb->expired(this);
}

} /* namespace FEmbed */
