/* CIIC 2013

   Pedro Paredes
*/

#include <stdio.h>

#define MAX 1000050

int seq[MAX];

int gcd(int a, int b)
{
  if (b > a)
    return gcd(b, a);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int main()
{
  int N, S, ans = 0;
  int i, j;

  scanf("%d %d", &N, &S);

  for (i = 0; i < N; i++)
    scanf("%d", &seq[i]);

  for (i = 0; i < N; i++)
  {
    int d = seq[i];
    for (j = i; j < N; j++)
    {
      d = gcd(d, seq[j]);
      if (d < S)
        break;
      if (j - i + 1 > ans)
        ans = j - i + 1;
    }
    i = j;
  }

  printf("%d\n", ans);

  return 0;
}
