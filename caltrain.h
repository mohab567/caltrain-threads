#include <pthread.h>

struct station {
	int count,toset,set;
	pthread_mutex_t trainWait; 
	pthread_cond_t trainArrive;
	pthread_cond_t seated;

	
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
