#include <stdio.h>
#include <stdlib.h>
#define Content_N 10000
#define Max_V 100
#define BUF_SIZE 32

/*-------------- Function ------------------------*/
int file_input(char [], int [][2]);
int max(int, int);
/*------------------------------------------------*/

/*-------------- Main ----------------------------*/
int main(int argc, char *argv[]){
  int n, v;
  int i, j; //ループ変数
  int cost[Content_N][2];
  int ans[Content_N][Max_V];
  
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

  printf("%d\n", ans[0][v-1]);

  return 0;
}
/*-------------------------------------------------*/

int file_input(char filename[], int cost[][2]){
  FILE *fp;
  char buf[Content_N][BUF_SIZE], buf2[BUF_SIZE];
  int line = 0, i, j, k, l, m;
  
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("%s is empty.\n", filename);
    return -1;
  }
  
  while(fgets(buf[line], BUF_SIZE, fp) != NULL){
    line++;
  }
  for(i = 0; i < line; i++){
    j = 0;
    k = 0;
    l = 0;
    while(buf[i][j] != '\0'){
      if(buf[i][j] == ',' || buf[i][j] == '\n'){
	cost[i][k] = atoi(buf2);
	k++;
	j++;
	l = 0;
	for(m = 0; m < BUF_SIZE; m++){
	  buf2[m] = '\0';
	}
      }
      else{
	buf2[l] = buf[i][j];
	j++;
	l++;
      }
    }
  }
 
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
