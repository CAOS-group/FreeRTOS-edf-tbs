/*
 * tbs.h
 *
 *  Created on: Feb 14, 2024
 *      Author: admin
 */

#ifndef INC_TBS_H_
#define INC_TBS_H_

#include <FreeRTOS.h>
#include <portmacro.h>
#include <projdefs.h>

#ifndef INC_FREERTOS_H
	#error "include FreeRTOS.h must appear in source files before include task.h"
#endif

typedef float Bandwidth_t;
/*
 * tbs.h
 * <pre>
 * void Start_TBS(
 * 					Bandwidth_t B
 * 				 ); </pre>
 * Initialize the Total Bandwidth Server to manage any aperiodic
 * task creation. This function should always be called BEFORE
 * starting the Scheduler
 *
 * @param B is the Bandwidth available for the server to allocate to the
 * aperiodic Tasks: it is equal to 1 minus the utilization factor of the periodic
 * tasks (the utilization factor is the sum of the WCET / Period of every task)
 * Should ALWAYS be lower than 1
 *
 */
void Start_TBS(Bandwidth_t B);

/**
 * tbs.h
 *<pre>
 BaseType_t xTaskCreateAperiodic(
							  TaskFunction_t pvTaskCode,
							  const char * const pcName,
							  configSTACK_DEPTH_TYPE usStackDepth,
							  void *pvParameters,
							  TickType_t xWCET,
							  TaskHandle_t *pvCreatedTask
						  );</pre>
 *
 * Create a new aperiodic task,  calculate its deadline and use xTaskCreatePeriodic
 * to add it to the ready list (see documentation of "xTaskCreatePeriodic" for further details).
 *
 * @param pvTaskCode Pointer to the task entry function.  Tasks
 * must have vTaskDelete() call at the end (always explicit ending).
 *
 * @param pcName A descriptive name for the task.  This is mainly used to
 * facilitate debugging.  Max length defined by configMAX_TASK_NAME_LEN - default
 * is 16.
 *
 * @param usStackDepth The size of the task stack specified as the number of
 * variables the stack can hold - not the number of bytes.  For example, if
 * the stack is 16 bits wide and usStackDepth is defined as 100, 200 bytes
 * will be allocated for stack storage.
 *
 * @param pvParameters Pointer that will be used as the parameter for the task
 * being created.
 *
 * @param xWCET The worst execution time of the aperiodic task, should be estimated by
 * the user and passed in system ticks: it is used to calculate the deadline to be used
 * along with periodic tasks
 *
 * @param pvCreatedTask Used to pass back a handle by which the created task
 * can be referenced.
 *
 * @return pdPASS if the task was successfully created and added to a ready
 * list, otherwise an error code defined in the file projdefs.h
 *
 * Example usage:
   <pre>
 // Aperiodic Task to be created.
 void vAperiodicTaskCode( void * pvParameters )
 {
	// Task code goes here.
	// Aperiodic task should not have an infinite loop inside


	// All Aperiodic Task should always be explicitly terminated using vTaskDelete
	vTaskDelete(NULL);
 }

 // Function that creates the task.
 void AperiodicTaskCreation( void )
 {
 	 //
 	  *
 	  * Task Code Here
 	  *
 	  *
 	 //

	 xTaskCreateAperiodic( vTaskCode, "NAME", STACK_SIZE, &ucParameterToPass, xWCET, &xHandle );
	 configASSERT( xHandle );

	//
	 *
	 *
	 * Task continues
	 *
	 *
	//

 }
   </pre>
 * \defgroup xTaskCreate xTaskCreate
 * \ingroup Tasks
 */

#endif /* INC_TBS_H_ */
