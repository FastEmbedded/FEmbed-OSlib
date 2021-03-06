/*
    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#ifndef USE_ARDUINO
#include "app.h"        //< For 
#endif
#include <stdint.h>

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
/* -------------------------------------------------------------------- */
/* Macros to identify the compiler used: */
#define configCOMPILER_ARM_GCC                    1 /* GNU ARM gcc compiler */
#define configCOMPILER_ARM_IAR                    2 /* IAR ARM compiler */
#define configCOMPILER_ARM_FSL                    3 /* Legacy Freescale ARM compiler */
#define configCOMPILER_ARM_KEIL                   4 /* ARM/Keil compiler */
#define configCOMPILER_S08_FSL                    5 /* Freescale HCS08 compiler */
#define configCOMPILER_S12_FSL                    6 /* Freescale HCS12(X) compiler */
#define configCOMPILER_CF1_FSL                    7 /* Freescale ColdFire V1 compiler */
#define configCOMPILER_CF2_FSL                    8 /* Freescale ColdFire V2 compiler */
#define configCOMPILER_DSC_FSL                    9 /* Freescale DSC compiler */

#define configCOMPILER                            configCOMPILER_ARM_GCC
/* USER CODE END Includes */ 

/* Ensure stdint is only used by the compiler, and not the assembler. */
#ifdef CONFIG_VENDOR_ST
    extern uint32_t SystemCoreClock;
    #define configCPU_CLOCK_HZ                       ( SystemCoreClock )
#else
    #define configCPU_CLOCK_HZ                       ( 120000000 )
#endif

#ifdef CONFIG_CCMRAM
#define __ccm  __attribute__ ((section(".data_CCMRAM")))
#else
#define __ccm
#endif

#define configUSE_PREEMPTION                     1
#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0
#define configUSE_MALLOC_FAILED_HOOK             1
#define configCHECK_FOR_STACK_OVERFLOW_NAME      vApplicationStackOverflowHook

#define configTICK_RATE_HZ                       ((portTickType)CONFIG_FREERTOS_TICKS)
#define configMAX_PRIORITIES                     ( 7 )
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)
#define configMAX_TASK_NAME_LEN                  ( 32 )

#define configRECORD_STACK_HIGH_ADDRESS          1

#ifdef DEBUG
#define configUSE_TRACE_FACILITY                 1
#define configUSE_STATS_FORMATTING_FUNCTIONS     1
#define configGENERATE_RUN_TIME_STATS            1
#else
#define configUSE_TRACE_FACILITY                 0
#define configUSE_STATS_FORMATTING_FUNCTIONS     0
#define configGENERATE_RUN_TIME_STATS            0
#endif

#define configUSE_16_BIT_TICKS                   0
#define configUSE_MUTEXES                        1
#define configQUEUE_REGISTRY_SIZE                8
#define configUSE_RECURSIVE_MUTEXES              1
#define configUSE_COUNTING_SEMAPHORES            1
#define configSUPPORT_STATIC_ALLOCATION          1

#ifdef CONFIG_ENABLE_PTHREAD
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     3
#else
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     2
#endif
#define configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS 1

#ifndef configGENERATE_RUN_TIME_STATS
  #define configGENERATE_RUN_TIME_STATS           1 /* 1: generate runtime statistics; 0: no runtime statistics */
#endif
#if configGENERATE_RUN_TIME_STATS
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   /* nothing */ /* default: use Tick counter as runtime counter */
    #define portGET_RUN_TIME_COUNTER_VALUE()           xTaskGetTickCountFromISR() /* default: use Tick counter as runtime counter */
#else /* no runtime stats, use empty macros */
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()     /* nothing */
  #define portGET_RUN_TIME_COUNTER_VALUE()             /* nothing */
#endif

#define configUSE_HEAP_SCHEME                   5

/* Software timer definitions. */
#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                 16
#ifndef configTIMER_TASK_STACK_DEPTH
#define configTIMER_TASK_STACK_DEPTH            ( 512 )
#endif

//Lower Power
#define configUSE_TICKLESS_IDLE                  CONFIG_FREERTOS_TICKLESS_IDLE
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP    CONFIG_FREERTOS_EXPECTED_IDLE_TIME_BEFORE_SLEEP
#define configCHECK_FOR_STACK_OVERFLOW           2

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES        ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet            1
#define INCLUDE_uxTaskPriorityGet           1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskCleanUpResources       0
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_vTaskDelayUntil             0
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_xTaskGetSchedulerState      1
#define INCLUDE_pcTaskGetTaskName           1
#define INCLUDE_xTimerPendFunctionCall      1
#define INCLUDE_uxTaskGetStackHighWaterMark 1
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         4
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 3

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY     ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
/* USER CODE BEGIN 1 */   
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );} 
/* USER CODE END 1 */

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#endif //FREERTOS_CONFIG_H
