/* CIIC 2013
   Solution of problem B - Score: 100;

   Sliding Window + Segment Tree

   Complexity: O(N log N)

   Pedro Paredes
*/

#include <stdio.h>

#define MAX 1000050

struct node
{
  node* left;
  node* right;
  int val;
} typedef node;

int seq[MAX];
node *root;

int gcd(int a, int b)
{
  if (b > a)
    return gcd(b, a);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

void init(node* cur, int l, int r)
{
  if (l == r)
  {
    cur->val = seq[l];
    return;
  }

  cur->left = new node();
  cur->right = new node();

  int m = (l + r) / 2;
  init(cur->left, l, m);
  init(cur->right, m + 1, r);
  
  cur->val = gcd(cur->left->val, cur->right->val);
}

int query_seg(node* cur, int bl, int br, int l, int r)
{
  if (br < l || bl > r)
    return 0;
  if (bl <= l && br >= r)
    return cur->val;

  int m = (l + r) / 2;
  int h1 = query_seg(cur->left, bl, br, l, m);
  int h2 = query_seg(cur->right, bl, br, m + 1, r);

  if (h1 == 0)
    return h2;
  if (h2 == 0)
    return h1;

  return gcd(h1, h2);
}

int query(int a, int b, int N)
{
  if (b - a >= 11)
    return query_seg(root, a, b, 0, N - 1);
  int d = seq[a], i;
  for (i = a + 1; i <= b; i++)
    d = gcd(d, seq[i]);
  return d;
}

int main()
{
  int N, S, ans = 0;
  int i, a, b, d;

  scanf("%d %d", &N, &S);

  for (i = 0; i < N; i++)
    scanf("%d", &seq[i]);

  root = new node();
  init(root, 0, N - 1);

  a = 0; b = 0;
  d = seq[0];
  while(b < N)
  {
    while (d < S && a < b)
    {
      a++;
      d = query(a, b, N);
    }
    if (b - a + 1 > ans && seq[a] >= S)
      ans = b - a + 1;
    b++;
    d = gcd(d, seq[b]);
  }
  printf("%d\n", ans);

  return 0;
}
