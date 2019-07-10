#include <stdio.h>
#include <stdlib.h>
#define Content_N 10000
#define Max_V 200
#define BUF_SIZE 16

/*-------------- Function ------------------------*/
int file_input(char [], int [][2]);
int max(int, int);
/*------------------------------------------------*/

/*-------------- Main ----------------------------*/
int main(int argc, char *argv[]){
  int n, v;
  int i, j; //ループ変数
  int cost[Content_N][2];
  int ans[Content_N+1][Max_V+1];
  
  n = file_input(argv[1], cost);
  if(n == -1){
    return -1;
  }

  printf("Please input volume : "); scanf("%d", &v);
  
  for(j = 0; j <= v; j++){
    ans[n][j] = 0;
  }
  for(i = n-1; i >= 0; i--){
    for(j = 0; j <= v; j++){
      if(j < cost[i][0]){
	ans[i][j] = ans[i+1][j];
      }
      else{
	ans[i][j] = max(ans[i+1][j], ans[i+1][j-cost[i][0]] + cost[i][1]);
      }
    }
  }
  
  printf("%d\n", ans[0][v]);
 
  return 0;
}
/*-------------------------------------------------*/

int file_input(char filename[], int cost[][2]){
  FILE *fp;
  int line = 0, ret;
  
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("%s is empty.\n", filename);
    return -1;
  }

  while((ret=fscanf(fp, "%d,%d", &cost[line][0], &cost[line][1])) != EOF){   
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
