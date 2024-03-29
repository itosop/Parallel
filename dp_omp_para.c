#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 
#define Content_N 10000
#define Max_V 10000
#define BUF_SIZE 16

int cost[Content_N][2];
int ans[Content_N+1][Max_V+1];

/*-------------- Function ------------------------*/
int file_input(char [], int [][2]);
int max(int, int);
/*------------------------------------------------*/

/*-------------- Main ----------------------------*/
int main(int argc, char *argv[]){
  int n, v;
  int i, j; //ループ変数
  struct timespec startTime, endTime;
  
  n = file_input(argv[1], cost);
  if(n == -1){
    return -1;
  }

  printf("Please input volume : "); scanf("%d", &v);

  /* 時間計測 開始 */
  clock_gettime(CLOCK_REALTIME, &startTime);
  
  for(j = 0; j <= v; j++){
    ans[n][j] = 0;
  }
 
  for(i = n-1; i >= 0; i--){
    #pragma omp parallel for private(j)
    for(j = 0; j <= v; j++){
      if(j < cost[i][0]){
	ans[i][j] = ans[i+1][j];
      }
      else{
	ans[i][j] = max(ans[i+1][j], ans[i+1][j-cost[i][0]] + cost[i][1]);
      }
    }
  }

  /* 時間計測 終了 */
  clock_gettime(CLOCK_REALTIME, &endTime);
  
  printf("Ans = %d\n", ans[0][v]);
  
  printf("elapsed time = ");
  if (endTime.tv_nsec < startTime.tv_nsec) {
    printf("%5ld.%09ld", endTime.tv_sec - startTime.tv_sec - 1,
	   endTime.tv_nsec + (long int)1.0e+9 - startTime.tv_nsec);
  }
  else {
    printf("%5ld.%09ld", endTime.tv_sec - startTime.tv_sec,
	   endTime.tv_nsec - startTime.tv_nsec);
  }
  printf("(sec)\n");
  
  return 0;
}
/*-------------------------------------------------*/

int file_input(char filename[], int C[][2]){
  FILE *fp;
  int line = 0, ret;
  
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("%s is empty.\n", filename);
    return -1;
  }

  while((ret=fscanf(fp, "%d,%d", &C[line][0], &C[line][1])) != EOF){   
    line++;
  }
  fclose(fp);
 
  return line;
}


int max(int a, int b){
  if(a < b){
    return b;
  }
  else{
    return a;
  }
}
