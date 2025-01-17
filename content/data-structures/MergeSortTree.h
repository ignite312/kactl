/**
 * Author: Himel
 * Date: 
 * License: 
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
// C++ program to count number of smaller or equal to given number and given row range.
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
void buildTree(int idx, int ss, int se, vector<int> a[], vector<int> sTree[])
{
	if (ss == se)
	{
		sTree[idx] = a[ss];
		return;
	}

	int mid = (ss + se) / 2;
	buildTree(2 * idx + 1, ss, mid, a, sTree);
	buildTree(2 * idx + 2, mid + 1, se, a, sTree);

	merge(sTree[2 * idx + 1].begin(),
		  sTree[2 * idx + 1].end(),
		  sTree[2 * idx + 2].begin(),
		  sTree[2 * idx + 2].end(),
		  back_inserter(sTree[idx]));
}

// Recursive function to count smaller elements from row a[ss] to a[se] and value smaller than or equal to k.
int queryRec(int node, int start, int end, int ss, int se, int k, vector<int> a[], vector<int> sTree[])
{
	if (ss > end || start > se)
		return 0;

	if (ss <= start && se >= end)
	{
		return upper_bound(sTree[node].begin(), sTree[node].end(), k) - sTree[node].begin();
	}

	int mid = (start + end) / 2;
	int p1 = queryRec(2 * node + 1, start, mid, ss, se, k, a, sTree);
	int p2 = queryRec(2 * node + 2, mid + 1, end, ss, se, k, a, sTree);

	return p1 + p2;
}

// A wrapper over query().
int query(int start, int end, int k, vector<int> a[], int n, vector<int> sTree[])
{
	return queryRec(0, 0, n - 1, start, end, k, a, sTree);
}

int main()
{
	int n = 3;
	int arr[][3] = {{2, 4, 5}, {3, 4, 9}};

	// build an array of vectors from above input
	vector<int> a[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i].push_back(arr[i][j]);

	// Construct segment tree
	vector<int> sTree[MAX];
	buildTree(0, 0, n - 1, a, sTree);

	cout << query(0, 1, 5, a, n, sTree) << endl;
	return 0;
}
