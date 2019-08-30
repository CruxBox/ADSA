#include<stdio.h>
#include<stdlib.h>

int min(int a, int b){
  return a>b?b:a;
}

void swap(int* a, int* b){
  int temp;
  temp = *b;
  *b = *a;
  *a = temp;
} 

void sort(int* array , int size){
  
  int minIndex = -1;
  for(int i=0; i<size-1;i++){
    minIndex = i;
    for(int j=i+1; j<size;j++){
      if(array[j] < array[minIndex])
          minIndex = j;
    }
    swap(&array[i],&array[minIndex]);
  }
}

int main(){
  int n;
  scanf("%d",&n);
  int array[n];

  for(int i=0;i<n;i++){
    scanf("%d",&array[i]);
  }

  sort(array, n);
  
  //printing the array
  
  for(int i=0;i<n;i++){
  printf("%d ",array[i]);
  }

  return 0;
}  
