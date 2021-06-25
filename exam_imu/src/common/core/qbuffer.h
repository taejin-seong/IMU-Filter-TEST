/*
 * qbuffer.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_COMMON_CORE_QBUFFER_H_
#define SRC_COMMON_CORE_QBUFFER_H_

#ifdef _cpluscplus
extern "C"{
#endif


#include "def.h"

typedef struct
{
	uint32_t in;
	uint32_t out;
	uint32_t len;

	uint8_t *p_buf;
}qbuffer_t;


void qbufferInit(void);
bool qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length);
bool qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
bool qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t qbufferAvailable(qbuffer_t *p_node);
void qbufferFlush(qbuffer_t *p_node);







#ifdef __cpluscplus
}
#endif
#endif /* SRC_COMMON_CORE_QBUFFER_H_ */
