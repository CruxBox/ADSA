#include <stdio.h>
#include <stdlib.h>

void merge(int *enter_time, int *exit_time, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[2][n1], R[2][n2];

  for (i = 0; i < n1; i++)
    L[0][i] = enter_time[l + i], L[1][i] = exit_time[l + i];
  for (j = 0; j < n2; j++)
    R[0][j] = enter_time[m + 1 + j], R[1][j] = exit_time[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (L[0][i] <= R[0][j])
    {
      enter_time[k] = L[0][i];
      exit_time[k] = L[1][i];
      i++;
    }
    else
    {
      enter_time[k] = R[0][j];
      exit_time[k] = R[1][j];

      j++;
    }
    k++;
  }

  while (i < n1)
  {
    enter_time[k] = L[0][i];
    exit_time[k] = L[1][i];

    i++;
    k++;
  }

  while (j < n2)
  {
    enter_time[k] = R[0][j];
    exit_time[k] = R[1][j];

    j++;
    k++;
  }
}
void mergeSort(int *enter_time, int *exit_time, int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
    mergeSort(enter_time, exit_time, l, m);
    mergeSort(enter_time, exit_time, m + 1, r);
    merge(enter_time, exit_time, l, m, r);
  }
}

int binary_search(int enter_time[], int l, int r, int exit_time)
{
  if(l<r){
    int mid = l + (r-l)/2;

    if(enter_time[mid]<=exit_time && enter_time[mid+1]>exit_time) return mid;
    if(enter_time[mid]>exit_time) return binary_search(enter_time, l, mid,exit_time);
    if(enter_time[mid]<exit_time) return binary_search(enter_time,mid+1,r,exit_time);
  }
}


int main()
{

  int n;
  printf("Enter number of pairs: ");
  scanf("%d", &n);

  int enter_time[n], exit_time[n];

  printf("Enter pairs: ");

  for (int i = 0; i < n; i++)
  {
    scanf("%d %d", &enter_time[i], &exit_time[i]);
  }

  mergeSort(enter_time, exit_time, 0, n);

  int ret;
  int ans=0;
  for(int i=0;i<n-1;i++){

    ret = binary_search(enter_time, i, n-1, exit_time[i]);
    ans+=(ret - i);
  }  

  printf("%d\n", ans);
  return 0;
}
