#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

int
sStrstr (char *s, int sn, char *p, int pn)
{
  int i = 0, j = 0;
  while ((i < sn) && (j < pn))
    {
      if (s[i] == p[j])
	{
	  i++;
	  j++;
	}
      else
	{
	  i = i - j + 1;
	  j = 0;
	}
    }
  if (j == pn)
    return (i - j);
  else
    return -1;
}

int
getNext (char *p, int pn, int next[])
{
  int j = 0;
  int k = -1;
  next[j] = k;
  while (j < pn)
    {
      if ((k == -1) || (p[k] == p[j]))
	{
	  next[++j] = ++k;
	}
      else
	{
	  k = next[k];
	}
    }
  return 0;
}

int
kStrstr (char *s, int sn, char *p, int pn)
{
  int i = 0, j = 0;
  int next[256] = { 0 };
  getNext (p, pn, next);
  while ((i < sn) && (j < pn))
    {
      if ((j == -1) || (s[i] == p[j]))
	{
	  i++;
	  j++;
	}
      else
	{
	  j = next[j];
	}
    }

  if (j == pn)
    return (i - j);
  else
    return -1;
}

void
verifyS ()
{
  char *s = "goodgoogle";
  char *p = "goog";

  int i = kStrstr (s, strlen (s), p, strlen (p));
  printf ("%s\n", (i == -1) ? "NULL" : s + i);
  return;
}


int **
threeSum (int *nums, int numsSize, int *returnSize)
{
  int i, j, k;
  int **val;
  int n = numsSize*(numsSize-1)*(numsSize-2);
  val = (int **)malloc(sizeof(int *) * n);
  for (i = 0; i < n; i++) {
      val[i] = (int *)malloc(sizeof(int) * 3);
  }
  *returnSize = 0;
  for (i = 0; i < numsSize; i++)
    {
      for (j = i + 1; j < numsSize; j++)
	{
	  for (k = j + 1; k < numsSize; k++)
	    {
	      if (((nums[i] + nums[j] + nums[k]) == 0))
		{
		  int index = *returnSize;
		  val[index][0] = i;
		  val[index][1] = j;
		  val[index][2] = k;
		  *returnSize += 1;
		}
	    }
	}
    }
  return (int **)val;
}

int
verifyT ()
{
  int i;
  int val = 0;
  int **rt;
  int a[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
  rt = threeSum (a, sizeof(a)/sizeof(a[0]), &val);
  for (i = 0; i < val; i++) {
  printf ("%d: %d %d %d\n", i, rt[i][0], rt[i][1], rt[i][2]);
  }
  return 0;
}


int
main ()
{
  verifyT ();
  return 0;
}
