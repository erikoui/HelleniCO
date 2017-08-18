#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int i,j,n;

	freopen("ngame.in", "r", stdin);
	freopen("ngame.out", "w", stdout);

	scanf("%d",&n);

	int *a=new int[n];
	int *sum=new int[n+1];
	int **w=new int*[n];




	for (i=0;i<n;++i){
		scanf("%d", &a[i]);
	}
	sum[0]=0;
	for (i = 0; i < n; ++i){
		sum[i + 1] = sum[i] + a[i];
		w[i] = new int[n];
		w[i][i] = a[i];
	}

	for (i=n-1;i>=0;--i){
		for (j=i+1;j<n;++j){
			w[i][j] = max(sum[j + 1] - sum[i + 1] - w[i + 1][j] + a[i],
				sum[j] - sum[i] - w[i][j - 1] + a[j]);
		}
	}
	printf("%d %d\n", w[0][n - 1], sum[n] - w[0][n - 1]);

	return 0;
}
