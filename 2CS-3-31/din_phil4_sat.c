#include <pthread.h>
#include <assert.h>

#include <stdio.h>

#define N 4

pthread_mutex_t  x[N];
int phil;

void *thread1(void *arg)
{
  int id, *aptr1, left, right;
  
  aptr1=(int *)arg;
  id=*aptr1;

  left=id;
  right=(id+1)%N;

  pthread_mutex_lock(&x[right]);
  pthread_mutex_lock(&x[left]);
  pthread_mutex_unlock(&x[left]);
  pthread_mutex_unlock(&x[right]);

  return NULL;
}

int main()
{
  int i;
  int arg[N];
  phil = 0;

  pthread_t trd_id[N];

  for(i=0; i<N; i++)
    pthread_mutex_init(&x[i], NULL);

  for(i=0; i<N; i++)
  {
    arg[i]=i;
    pthread_create(&trd_id[i], 0, thread1, &arg[i]);
  }
   
  for(i=0; i<N; i++)
    pthread_join(trd_id[i], 0);
             
  return 0;
}

