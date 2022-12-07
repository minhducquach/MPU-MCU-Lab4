/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Minh Duc Quach
 */


#include "scheduler.h"

//struct Node TaskArray[SCH_MAX_TASKS + 1];

sTasks SCH_Tasks_G[SCH_MAX_TASKS+1];
uint32_t current_index_task = 0;

char str[50];

void SCH_Init(void){
	current_index_task = 0;
	for (uint32_t i = 0; i <= SCH_MAX_TASKS; i++){
		SCH_Tasks_G[i].pTask = NULL;
		SCH_Tasks_G[i].Delay = -1;
		SCH_Tasks_G[i].Period = -1;
		SCH_Tasks_G[i].RunMe = -1;
		SCH_Tasks_G[i].TaskID = -1;
		SCH_Tasks_G[i].led_index = -1;
//		if (i == 0){
//			free_ptr = &(TaskArray[i]);
//		}
//		else {
//			TaskArray[i-1].next = &(TaskArray[i]);
//		}
//		if (i == SCH_MAX_TASKS){
//			TaskArray[i].next = NULL;
//		}
//	}
//	if (head == NULL){
//		head = allocNode();
	}
}
//
uint32_t SCH_Add_Task (void (*pFunction)(uint32_t), uint32_t led_index, uint32_t DELAY, uint32_t PERIOD){
	if (current_index_task < SCH_MAX_TASKS){
		SCH_Tasks_G[current_index_task].pTask = pFunction;
		SCH_Tasks_G[current_index_task].Delay = DELAY;
		SCH_Tasks_G[current_index_task].Period = PERIOD;
		SCH_Tasks_G[current_index_task].RunMe = 0;
		SCH_Tasks_G[current_index_task].TaskID = current_index_task;
		SCH_Tasks_G[current_index_task].led_index = led_index;
		return current_index_task++;
	}
	return SCH_MAX_TASKS;
//	struct Node* tmp = allocNode();
//	tmp->data.Delay = DELAY;
//	tmp->data.Period = PERIOD;
//	tmp->data.pTask = pFunction;
//	tmp->data.TaskID = current_index_task;
//	current_index_task++;
//	addNode(tmp);
}

uint8_t SCH_Delete_Task(uint32_t TASK_ID){
	for (uint32_t i = TASK_ID; i < SCH_MAX_TASKS; i++){
		SCH_Tasks_G[i] = SCH_Tasks_G[i+1];
		current_index_task--;
		return 0;
	}
//	if (SCH_Tasks_G[TASK_ID].pTask != NULL){
//		SCH_Tasks_G[current_index_task].pTask = NULL;
//		SCH_Tasks_G[current_index_task].Delay = -1;
//		SCH_Tasks_G[current_index_task].Period = -1;
//		SCH_Tasks_G[current_index_task].RunMe = -1;
//		SCH_Tasks_G[current_index_task].led_index = -1;
//		SCH_Tasks_G[current_index_task].TaskID = -1;
//		return 0;
//	}
	return 1;
//	deleteNode(TASK_ID);
}
//
void SCH_Update(void){
	for (int i = 0; i < SCH_MAX_TASKS; i++){
		if (SCH_Tasks_G[i].Delay > 0){
			SCH_Tasks_G[i].Delay--;
		}
		else if (SCH_Tasks_G[i].Delay == 0){
			SCH_Tasks_G[i].Delay = SCH_Tasks_G[i].Period;
			SCH_Tasks_G[i].RunMe += 1;
		}
	}
//	struct Node* tmp = getFront();
//	if (tmp){
//		if (tmp->data.Delay == 0){
//			tmp->data.RunMe += 1;
//		}
//		else tmp->data.Delay--;
//	}
}

void SCH_Dispatch_Tasks(void){
	for (uint32_t i = 0; i < current_index_task; i++){
		if (SCH_Tasks_G[i].RunMe > 0){
			SCH_Tasks_G[i].RunMe--;
			HAL_UART_Transmit(&huart2, (uint8_t*) str, sprintf(str, "Timestamp: %lu\r\n", tick * 10), 1000);
			(*SCH_Tasks_G[i].pTask)(SCH_Tasks_G[i].led_index);
			if (SCH_Tasks_G[i].Period == 0){
				uint8_t del = SCH_Delete_Task(i);
			}
		}
	}
//	struct Node* tmp = getFront();
//	if (tmp && tmp->data.RunMe){
//		tmp->data.RunMe--;
//		(*tmp->data.pTask)();
//		if (!tmp->data.RunMe){
//			if (!tmp->data.Period){
//				deleteNode(tmp->data.TaskID);
//				return;
//			}
//			struct Node* del = popFront();
//			del->data.Delay = del->data.Period;
//			addNode(del);
//		}
//	}
}
