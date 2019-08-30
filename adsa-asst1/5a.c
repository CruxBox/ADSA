#include<stdio.h>
#include<stdlib.h>

//returns index of the local minimum
int find_local_minimum(int array[], int low, int high, int size){
  
  int mid = low + (high - low)/2 ;
  
  //assuming that when array[i] == array[i-1] we don't consider it a minimum
  if((mid==0 || array[mid] < array[mid -1]) && (mid==(size-1) || array[mid+1]>array[mid])){
    return mid;
  }
  else if(mid>0 && array[mid-1] < array[mid]){
    return find_local_minimum(array, low, mid - 1, size);
  }
  return find_local_minimum(array,mid+1, high, size);
  
}

int main(){
  int n;
  scanf("%d",&n);
  int array[n];
  
  for(int i=0;i<n;i++){
    scanf("%d",&array[i]);
  }
  
  printf("The local minimum is %d\n",array[find_local_minimum(array,0,n-1,n)]);
  
  return 0;
}
