#include <iostream>
#include <algorithm>
#include <stack>
#include <assert.h>

///
/// Ако b < a, функцията разменя техните стойности
///
template <class T>
void swapif(T& a, T& b)
{
	if( b < a )
		std::swap(a, b);
}


///
/// Пряка селекция (Selection Sort)
///
template <class T>
void SelectionSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	for(size_t i = 0; i < Size-1; i++)
	{
		size_t min = i;

		for(size_t j = i+1; j < Size; j++)
		{
			if(pArr[j] < pArr[min])
				min = j;
		}

		swapif(pArr[i], pArr[min]);
	}
}


///
/// Метод на мехурчето (Bubble Sort)
///
template <class T>
void BubbleSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	for(size_t i = 0; i < Size-1; i++)
	{
		for(size_t j = Size-1; j > i; j--)
		{
			swapif(pArr[j-1], pArr[j]);
		}
	}
}


///
/// Функция, която връща ключа на някакъв произволен тип.
///

template <class T>
int key(T& value)
{
	return static_cast<int>(value);
}


template <class T>
void DistributionCounting(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Намираме най-големия ключ в масива
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		int nextKey = key(pArr[i]);

		if(maxN < nextKey)
			maxN = nextKey;
	}

	// В този масив ще пазим позициите, от които започва дадена поредица от елементи
	// във вече сортирания масив

	size_t * pEndsAt = new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) //нулираме стойностите
		pEndsAt[i] = 0;

	for(size_t i = 0; i < Size; i++)
	{
		pEndsAt[key(pArr[i])]++;
	}

	for(int i = 1; i <= maxN; i++)
	{
		pEndsAt[i] += pEndsAt[i-1];
	}

	T* pSorted = new T[Size];

	size_t j = Size;

	while(j--)
	{
		size_t pos = --pEndsAt[key(pArr[j])];
		pSorted[pos] = pArr[j];
	}

	for(size_t i = 0; i < Size; i++)
	{
		pArr[i] = pSorted[i];
	}

	delete [] pSorted;
	delete [] pEndsAt;
}


template <> void DistributionCounting<int>(int* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Намираме най-голямото число в масива
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		if(maxN < pArr[i])
			maxN = pArr[i];
	}

	
	size_t * pCounts =  new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) // нулираме стойностите
		pCounts[i] = 0;

	for(size_t i = 0; i < Size; i++)
	{
		pCounts[pArr[i]]++;
	}

	size_t pos = 0;

	for(int i = 0; i <= maxN; i++)
	{
		while(pCounts[i] > 0)
		{
			pArr[pos++] = i;
			pCounts[i]--;
		}
	}

	delete [] pCounts;
}



///
/// Сортиране чрез вмъкване (Insertion Sort)
///
template <class T>
void InsertionSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Преместваме минималният елемент най-отпред
	for(size_t i = Size-1; i > 0; i--)
	{
		swapif(pArr[i-1], pArr[i]);
	}

	for(size_t i = 2; i < Size; i++)
	{
		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-1] > value)
		{
			pArr[j] = pArr[j-1];
			j--;
		}

		pArr[j] = value;
	}
}


template <class T>
void ShellSortH(T* pArr, size_t Size, size_t k, size_t h)
{
	pArr = pArr + k;
	Size = Size - k;

	size_t LastElement = (Size / h) * h - 1;

	size_t i;

	for(i = LastElement; i > 0; i-=h)
	{
		assert( 0 <= i && i < Size);
		assert( 0 <= (i-h) && (i-h) < Size);
		swapif(pArr[i-h], pArr[i]);
	}

	assert(i == 0);

	for(size_t i = h; i < Size; i+=h)
	{
		assert( 0 <= i && i < Size);

		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-h] > value)
		{
			assert( 0 <= j && j < Size);
			pArr[j] = pArr[j-h];
			j-=h;
		}

		assert( 0 <= j && j < Size);

		pArr[j] = value;
	}
}


///
/// Сортировка на Шел (Shell Sort)
///
template <class T>
void ShellSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	size_t h = 1;

	while(h < Size / 9)
		h = h*3 + 1;

	for( ; h > 0; h = (h - 1) / 3 )
	{
		for(size_t i = 0; i < h; i++)
		{
			ShellSortH(pArr, Size, i, h);
		}
	}
}


///
/// Бързо сортиране (Quicksort)
///
template <class T>
void QuickSort(T* pArr, size_t Size)
{
	if(Size <= 1 || !pArr)
		return;

	size_t pos = Partition(pArr, Size);

	QuickSort(pArr, pos);
	QuickSort(pArr + pos + 1, Size - pos - 1);
}


///
/// Итеративна версия на бързо сортиране (Quicksort)
///
template <class T>
void QuickSortIterative(T* pArr, size_t Size)
{
	if (Size <= 1 || !pArr)
		return;

	std::stack<size_t> st;

	// Добавяме началото и края на масива в стека
	st.push(Size);
	st.push(0);

	size_t start, end, length;

	while (!st.empty())
	{
		start = st.top();
		st.pop();
		end = st.top();
		st.pop();

		length = end - start;

		if(length > 1)
		{
			size_t pos = Partition(pArr + start, length);
			
			// Начало и край на лявата част
			st.push(start + pos);
			st.push(start);

			// Начало и край на дясната част
			st.push(end);
			st.push(start + pos + 1);
		}
	}
}


template <class T>
size_t Partition(T* pArr, size_t Size)
{
	assert(Size >= 2);

	if(Size == 2)
	{
		swapif(pArr[0], pArr[1]);
		return 1;
	}

	size_t middle = Size / 2;
	swapif(pArr[0], pArr[middle]);
	swapif(pArr[0], pArr[Size-1]);
	swapif(pArr[middle], pArr[Size-1]);

	std::swap(pArr[middle], pArr[Size-2]);

	T& partitioningElement = pArr[Size-2];

	size_t left = 0;
	size_t right = Size-2;

	while(true)
	{
		while(pArr[++left] < partitioningElement)
			;

		while(pArr[--right] > partitioningElement)
		{
			if(left == right)
				break;
		}

		if(left >= right)
			break;

		std::swap(pArr[left], pArr[right]);
	}

	std::swap(pArr[left], partitioningElement);

	return left;
}


///
///	Пирамидално сортиране (Heap Sort)
///
template <class T>
void HeapSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	size_t i = Size / 2;

	while(i--)
	{
		Sift(pArr, i, Size);
	}


	i = Size;

	while(--i)
	{
		std::swap(pArr[0], pArr[i]);
		Sift(pArr, 0, i);
	}
}


///
///	Сортиране чрез сливане (Merge Sort)
///
template <class T>
void MergeSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	T* pBuffer = new T[Size];

	MergeSortStep(pArr, Size, pBuffer);

	delete []  pBuffer;
}

template <class T>
void MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if(Size <= 1)
		return;

	size_t middle = Size / 2;

	MergeSortStep(pArr, middle, pBuffer);

	MergeSortStep(pArr + middle, Size - middle, pBuffer + middle);

	Merge(pArr, middle, pArr + middle, Size - middle, pBuffer);

	for(size_t i = 0; i < Size; i++)
		pArr[i] = pBuffer[i];
}

///
///	Слива съдържанието на двата сортирани масива pA и pB
///	в масива pResult.
template <class T>
void Merge(T* pA, size_t sizeA, T* pB, size_t sizeB, T* pResult)
{
	size_t i = 0; 
	size_t ia = 0;
	size_t ib = 0;

	while(ia < sizeA && ib < sizeB)
		pResult[i++] = (pA[ia] < pB[ib] ? pA[ia++] : pB[ib++]);

	while(ia < sizeA)
		pResult[i++] = pA[ia++];

	while(ib < sizeB)
		pResult[i++] = pB[ib++];
}


//
// Инстанцираме шаблоните за работа с double
//
template void swapif<double>(double& a, double& b);
template void SelectionSort<double>(double* pArr, size_t Size);
template void BubbleSort<double>(double* pArr, size_t Size);
template void ShakerSort<double>(double* pArr, size_t Size);
template int key<double>(double& value);
template void DistributionCounting<double>(double* pArr, size_t Size);
template void InsertionSort<double>(double* pArr, size_t Size);
template void ShellSortH<double>(double* pArr, size_t Size, size_t k, size_t h);
template void ShellSort<double>(double* pArr, size_t Size);
template void QuickSort<double>(double* pArr, size_t Size);
template void QuickSortIterative<double>(double* pArr, size_t Size);
template size_t Partition<double>(double* pArr, size_t Size);
template void HeapSort<double>(double* pArr, size_t Size);
template void Sift<double>(double* pArr, size_t pos, size_t Size);
template void MergeSort<double>(double* pArr, size_t Size);
template void MergeSortStep<double>(double* pArr, size_t Size, double* pBuffer);
template void Merge<double>(double* pA, size_t sizeA, double* pB, size_t sizeB, double* pResult);
template void BottomUpMergeSort<double>(double* pArr, size_t Size);
