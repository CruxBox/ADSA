#include<stdio.h>
#include<stdlib.h>

int min(int a, int b){
  return a>b?b:a;
}

int findMinimum(int array[], int start_index, int end_index){
  if(start_index==end_index) return array[start_index];
  
  int mid = start_index + (end_index - start_index)/2;
  return min(findMinimum(array,start_index,mid),findMinimum(array,mid+1,end_index));
  
}
int main(){
  int n;
  scanf("%d",&n);
  int array[n];
  
  for(int i=0;i<n;i++){
    scanf("%d",&array[i]);
  }

  printf("The minimum is: %d\n",findMinimum(array, 0, n-1));
}  
