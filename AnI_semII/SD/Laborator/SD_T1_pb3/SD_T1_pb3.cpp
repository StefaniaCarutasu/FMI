#include<iostream>
using namespace std;
int main()
{
	int st_tarusi[10], n, tos=-1, x;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		if (tos == -1)
		{
			st_tarusi[++tos] = x;
		}

		else
		{
			if (st_tarusi[tos] == x)
				tos--;
		}
	}
	if (tos == -1)
		cout << "Valid";
	else cout << "Invalid";
	return 0;
}