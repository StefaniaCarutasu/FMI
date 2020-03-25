#include <iostream>
using namespace std;
int w[500];

int main()
{
	int n, i, v[100];
	cin >> n;

	for (i = 0; i < n; i++)
		cin >> v[i];

	int max = v[0];

	for (i = 1; i < n; i++)
		if (v[i] > max) max = v[i];

	for (i = 0; i < n; i++)
		w[v[i]]++;

	bool ok = false;
	i = 0;

	while (ok == false && i <= max)
	{
		if (w[i] >= n / 2 + 1)
		{
			ok = true; break;
		}
		i++;
	}

	if (ok)
		cout << i;
	else
		cout << "Nu exista un astfel de element";
	return 0;
}