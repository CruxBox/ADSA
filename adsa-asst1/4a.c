#include<stdio.h>
#include<stdlib.h>

int min(int a, int b){
  return a>b?b:a;
}

int main(){
  
  int n;
  scanf("%d",&n);
  int array[n];
  
  for(int i=0;i<n;i++){
  scanf("%d",&array[i]);
  }

  int mino = array[0];
  
  for(int i=1;i<n;i++){
    mino = min(mino, array[i]);
  }

  printf("The minimum number is: %d\n", mino);

return 0;
}
