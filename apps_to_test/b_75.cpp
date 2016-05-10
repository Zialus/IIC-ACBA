/* CIIC 2013

   Sliding Window + Linear gcd query (and constant sometimes)

   Complexity: O(N^2) Optimized

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
  int i, a, b, d;

  scanf("%d %d", &N, &S);

  for (i = 0; i < N; i++)
    scanf("%d", &seq[i]);

  a = 0; b = 0;
  d = seq[0];
  while(b < N)
  {
    while (d < S && a < b)
    {
      a++;
      d = seq[a];
      for (i = a + 1; i <= b; i++)
        d = gcd(d, seq[i]);
    }
    if (b - a + 1 > ans && seq[a] >= S)
      ans = b - a + 1;
    b++;
    d = gcd(d, seq[b]);
  }
  printf("%d\n", ans);

  return 0;
}
