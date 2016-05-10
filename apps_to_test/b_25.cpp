/* CIIC 2013

   Pairs Search + Linear gcd query

   Complexity: O(N^3)

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

int query(int l, int r)
{
  int i, d = seq[l];
  for (i = l + 1; i <= r; i++)
    d = gcd(d, seq[i]);
  return d;
}

int main()
{
  int N, S, ans = 0;
  int i, j;

  scanf("%d %d", &N, &S);

  for (i = 0; i < N; i++)
    scanf("%d", &seq[i]);

  for (i = 0; i < N; i++)
    for (j = i; j < N; j++)
      if (query(i, j) >= S && j - i + 1 > ans)
        ans = j - i + 1;

  printf("%d\n", ans);

  return 0;
}
