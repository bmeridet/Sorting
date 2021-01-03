#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

struct Node
{
	int val;
	Node* next;
	Node(int _val) { val = _val; next = nullptr; }
};

struct Array
{
	int* A;
	int size;
	Array(int _size);
};

int FindMax(Array& A);
void Swap(Array& A, int i1, int i2);

void BubbleSort(Array& A);
void SelectionSort(Array& A);
void InsertionSort(Array& A);
void CountSort(Array& A);

int Partition(Array& A, int s, int e);
void SetMedian(Array& A, int s, int e);
void QuickSort(Array& A, int s, int e);

void Merge(Array& A, int s, int m, int e);
void MergeSort(Array& A, int s, int e);

void RadixSort(Array& A);
void ShellSort(Array& A);

void Print(Array& A);

int main()
{
	Array A(15);

	Print(A);

	ShellSort(A);

	Print(A);

	return 0;
}

Array::Array(int _size)
{
	size = _size;
	A = new int[size];

	for (int i = 0; i < size; ++i)
	{
		A[i] = rand() % 100;
	}
}

int FindMax(Array& A)
{
	int max = 0;

	for (int i = 1; i < A.size; ++i)
	{
		if (A.A[i] > A.A[max])
			max = i;
	}

	return max;
}

void Swap(Array& A, int i1, int i2)
{
	int temp = A.A[i1];
	A.A[i1] = A.A[i2];
	A.A[i2] = temp;
}

void BubbleSort(Array& A)
{
	for (int i = 0; i < A.size - 1; ++i)
	{
		int flag = false;

		for (int j = 0; j < A.size - i - 1; ++j)
		{
			if (A.A[j] > A.A[j + 1])
			{
				Swap(A, j, j + 1);
				flag = true;
			}
		}

		if (!flag)
			return;
	}

	return;
}

void SelectionSort(Array& A)
{
	for (int i = 0; i < A.size - 1; ++i)
	{
		int min = i;

		for (int j = i + 1; j < A.size; ++j)
		{
			if (A.A[j] < A.A[min])
				min = j;
		}

		if (min != i)
			Swap(A, i, min);
	}
}

void InsertionSort(Array& A)
{
	for (int i = 0; i < A.size - 1; ++i)
	{
		int j = i + 1;

		while (A.A[j] < A.A[j - 1] && j > 0)
		{
			Swap(A, j, j - 1);
			j--;
		}
	}
}

void CountSort(Array& A)
{
	int maxVal = A.A[FindMax(A)];
	int* B = new int[maxVal + 1];

	for (int i = 0; i < maxVal + 1; ++i)
		B[i] = 0;

	for (int i = 0; i < A.size; ++i)
		B[A.A[i]] += 1;

	int i = 0;
	int j = 0;

	while (j <= maxVal)
	{
		if (B[j] > 0)
		{
			A.A[i++] = j;
			B[j] -= 1;
		}
		else
			j++;
	}
}

int Partition(Array& A, int s, int e)
{
	SetMedian(A, s, e);

	int val = A.A[s];
	int i = s;

	for (int j = i + 1; j <= e; ++j)
	{
		if (A.A[j] < val)
			Swap(A, ++i, j);
	}

	Swap(A, s, i);

	return i;
}

void SetMedian(Array& A, int s, int e)
{
	int m = s + (e - s) / 2;

	if (m < e && m > s || m > e && m < s)
		Swap(A, s, m);
	else if (s < m && s > e || s > m && s < e)
		return;
	else
		Swap(A, s, e);
}

void QuickSort(Array& A, int s, int e)
{
	if (s < e)
	{
		int sorted = Partition(A, s, e);

		QuickSort(A, s, sorted - 1);
		QuickSort(A, sorted + 1, e);
	}
}

void Merge(Array& A, int s, int m, int e)
{
	int sizeLeft = m - s + 1;
	int sizeRight = e - m;

	int* left = new int[sizeLeft];
	int* right = new int[sizeRight];

	for (int i = 0; i < sizeLeft; ++i)
		left[i] = A.A[s + i];

	for (int i = 0; i < sizeRight; ++i)
		right[i] = A.A[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = s;

	while (i < sizeLeft && j < sizeRight)
	{
		if (left[i] < right[j])
			A.A[k++] = left[i++];
		else
			A.A[k++] = right[j++];
	}

	while (i < sizeLeft)
		A.A[k++] = left[i++];

	while (j < sizeRight)
		A.A[k++] = right[j++];

	delete[] left;
	delete[] right;
}

void MergeSort(Array& A, int s, int e)
{
	if (s < e)
	{
		int m = s + (e - s) / 2;

		MergeSort(A, s, m);
		MergeSort(A, m + 1, e);

		Merge(A, s, m, e);
	}
}

int GetDigits(int val)
{
	int count = 0;

	while (val > 0)
	{
		count += 1;
		val /= 10;
	}

	return count;
}

void InitializeBins(Node** bins, int n)
{
	for (int i = 0; i < n; ++i)
		bins[i] = nullptr;
}

int GetIndex(int val, int idx)
{
	return (int)(val / pow(10, idx)) % 10;
}

void Insert(Node** bins, int val, int idx)
{
	Node* temp = new Node(val);

	if (bins[idx] == nullptr)
	{
		bins[idx] = temp;
	}
	else
	{
		Node* ptr = bins[idx];

		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}

		ptr->next = temp;
	}
}

int Delete(Node** bins, int idx)
{
	Node* temp = bins[idx];
	bins[idx] = bins[idx]->next;
	
	int val = temp->val;
	delete temp;

	return val;
}

void RadixSort(Array& A)
{
	int max = A.A[FindMax(A)];
	int numPass = GetDigits(max);

	Node** bins = new Node * [10];

	InitializeBins(bins, 10);

	for (int pass = 0; pass < numPass; ++pass)
	{
		for (int i = 0; i < A.size; ++i)
		{
			int idx = GetIndex(A.A[i], pass);
			Insert(bins, A.A[i], idx);
		}

		int i = 0;
		int j = 0;

		while (i < 10)
		{
			while (bins[i] != nullptr)
				A.A[j++] = Delete(bins, i);

			i++;
		}

		InitializeBins(bins, 10);
	}

	delete[] bins;
}

void ShellSort(Array& A)
{
	for (int gap = A.size / 2; gap >= 1; gap /= 2)
	{
		for (int j = gap; j < A.size; ++j)
		{
			int temp = A.A[j];
			int i = j - gap;

			while (i >= 0 && A.A[i] > temp)
			{
				A.A[i + gap] = A.A[i];
				i = i - gap;
			}

			A.A[i + gap] = temp;
		}
	}
}

void Print(Array& A)
{
	for (int i = 0; i < A.size; ++i)
		cout << A.A[i] << " ";
	cout << endl;
}