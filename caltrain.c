#include <pthread.h>
#include "caltrain.h"
/*
used to initialize station using station pointer.
*/
void station_init(struct station *station)
{
    (*station).count=0;
    pthread_mutex_init(&((*station).trainWait), NULL);
    pthread_cond_init(&((*station).trainArrive), NULL);
    pthread_cond_init(&((*station).seated), NULL);
}
/*
used when train arrives the station and calls out for passengers.
*/
void station_load_train(struct station *station, int count)
{
    if (count ==0 || (*station).count==0)
        return;
    pthread_mutex_lock(&((*station).trainWait));
    (*station).toset=(*station).set=(count <(*station).count ) ? count : (*station).count;
    pthread_cond_broadcast(&((*station).trainArrive));
    pthread_cond_wait(&((*station).seated), &((*station).trainWait));
    pthread_mutex_unlock(&((*station).trainWait));
}
/*
used when a passengers arrives the station and waits a train.
*/
void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&((*station).trainWait));
    (*station).count++;
    while(1)
    {
        pthread_cond_wait(&((*station).trainArrive), &((*station).trainWait));
        if((*station).count>0&&(*station).toset>0)
        {
            (*station).toset--;
            (*station).count--;
            break;
        }
    }
    pthread_mutex_unlock(&((*station).trainWait));
}
/*
used to make sure that a passenger is in his seat just like air plans first class tickets.
*/
void station_on_board(struct station *station)
{
    (*station).set--;
    if((*station).set<=0)
    {
        pthread_cond_signal(&((*station).seated));
    }
}
