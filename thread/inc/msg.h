#ifndef THREAD_INC_MSG_H_
#define THREAD_INC_MSG_H_

#include "types.h"
#include "thread.h"

#define MSG_BOX_EMPTY	(0xFFFFFFFEU)
#define MSG_BOX_FULL	(0xFFFFFFFFU)

#define MSG_ACTION_SUCCESS	(0U)
#define MSG_ACTION_FAILURE	(1U)

uint32_t
msg_post(thd_t* to, thd_priv_t *msg);

uint32_t
msg_retrieve(thd_t* to, thd_priv_t *msg);


#endif /* THREAD_INC_MSG_H_ */
