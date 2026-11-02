
#define BSP_QUEUE_C


#include "bsp_queue.h"
#include "stdio.h"
#include "main.h"
/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void initializeQueue(cyclic_queue *q) 
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/*------------------------------------------------------------------------
 * @brief   queue is empty
 * @input
 * @return
------------------------------------------------------------------------*/
signed char isEmpty(cyclic_queue *q) 
{
    return q->size == 0;
}

/*------------------------------------------------------------------------
 * @brief queue is Full
 * @input
 * @return
------------------------------------------------------------------------*/
signed char isFull(cyclic_queue *q) 
{
    return q->size == QUEUE_MAX_SIZE;
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
int message_enqueue(cyclic_queue *q,unsigned char msg) 
{
    if(isFull(q))
    {
		return 0;
    }
    q->items[q->rear] = msg;
    q->rear = (q->rear + 1) % QUEUE_MAX_SIZE;   
    q->size++;
	return 1;
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
int message_dequeue(cyclic_queue *q,unsigned char *msg) 
{
    if(q->size==0)
    {
        return 0 ;
    }
    *msg = q->items[q->front] ;
    q->front = (q->front + 1) % QUEUE_MAX_SIZE;
    q->size--;
    return 1;
}






























///*-------------------------------------------------------------------
//function:
//-------------------------------------------------------------------*/
//int main() 
//{
//    CircularQueue q;
//    initializeQueue(&q);

//    enqueue(&q, 10);
//    enqueue(&q, 20);
//    enqueue(&q, 30);
//    enqueue(&q, 40);
//    enqueue(&q, 50);

//    // ��������һ��Ԫ�ص������Ķ���
//    enqueue(&q, 60);

//    printf("%d dequeued from queue\n", dequeue(&q));
//    printf("%d dequeued from queue\n", dequeue(&q));

//    // �����������пռ䣬����������Ԫ��
//    enqueue(&q, 60);

//    // ��������ֱ������Ϊ��
//    while (!isEmpty(&q)) {
//        printf("%d dequeued from queue\n", dequeue(&q));
//    }
//    return 0;
//}









