#ifndef BINARY_SEARCH__CPP
#define BINARY_SEARCH__CPP
#include "BinarySearch.hpp"
#include <vector>

namespace binary_search
{
    template<typename T>
    T Vanilla<T>::calcMidPoint(T a, T b)
    {
        return a + ((b - a) / 2);
    }

    template<typename T>
    T Vanilla<T>::search_I(std::vector<T>& nums)
    {
        while (leftIndex <= rightIndex)
        {
            if (target == nums[midIndex])
                return midIndex;
            if (target < nums[midIndex])
                rightIndex = midIndex - 1;
            else
                leftIndex = midIndex + 1;

            midIndex= calcMidPoint(leftIndex, rightIndex);
        }
        return -1;
    }

    template<typename T>
    T Vanilla<T>::search_II(std::vector<T>& nums)
    {
        while (leftIndex <= rightIndex)
        {
            if (target == nums[midIndex])
                return midIndex;
            if (target < nums[midIndex])
                rightIndex = midIndex;
            else
                leftIndex = midIndex + 1;
            midIndex = calcMidPoint(leftIndex, rightIndex);
        }

        // Post-processing:
        if (leftIndex != nums.size() && nums[leftIndex] == target)
            return leftIndex;

        return -1;
    }

    template<typename T>
    T Vanilla<T>::search_III(std::vector<T>& nums)
    {
        while (leftIndex + 1 < rightIndex)
        {
            if (target == nums[midIndex])
                return midIndex;
            if (target < nums[midIndex])
                rightIndex = midIndex;
            else
                leftIndex = midIndex;

            midIndex = calcMidPoint(leftIndex, rightIndex);
        }

        // Post-processing:
        if (nums[leftIndex] == target)
            return leftIndex;
        if (nums[rightIndex] == target)
            return rightIndex;

        return -1;
    }

    template<typename T>
    T Vanilla<T>::search(std::vector<T>& nums, T targetInput)
    {
        leftIndex = 0;
        rightIndex = nums.size() - 1;
        target = targetInput;
        midIndex= calcMidPoint(leftIndex, rightIndex);
        return search(nums);
    }

    int NumberHigherLower::guess(int num)
    {
        if (m_targetNumber < num)
            return -1;
        if (m_targetNumber > num)
            return 1;
        else
            return 0;
    }
    int NumberHigherLower::guessNumber(int n)
    {
        leftIndex = 0;
        rightIndex = n;
        while (leftIndex <= rightIndex)
        {
            auto temp1 =  rightIndex - leftIndex;
            auto temp2 =  rightIndex + leftIndex;
            
            //cast leftIndex + rightIndex (_not_ the division result) to size_t to expand storage size for
            //this intermediate calculation (wrap around otherwise, resulting in slow/incomplete algo)
            midIndex = (size_t)(leftIndex + rightIndex) / 2;
            if (guess(midIndex) == 0)
                return midIndex;
            else if (guess(midIndex) == -1)
                rightIndex = midIndex - 1;
            else if (guess(midIndex) == 1)
                leftIndex = midIndex + 1;
        }
        return -1;
    }

	template<typename T>
	T RotatedArraySearch<T>::calcMidPoint(T a, T b)
	{
        return a + ((b - a) / 2);
    }

	template<typename T>
	bool RotatedArraySearch<T>::isRotated(std::vector<T>& nums)
	{
		return nums[0] > nums[nums.size()-1];
	}

	template<typename T>
	T RotatedArraySearch<T>::pivotPoint(std::vector<T>& nums)
	{
		int size = nums.size();
		left = 0;
		right = size - 1;

		while (left <= right)
		{
			mid = calcMidPoint(left, right);
			if (nums[mid] > nums[mid + 1])
				return mid;

			if (nums[mid] < nums[mid - 1])
				return mid - 1;

			if (nums[0] > nums[mid])
				right = --mid;
			else
				left = ++mid;
		}
		//pivot point not found
		return -1;
	}

	template<typename T>
	T RotatedArraySearch<T>::search(std::vector<T>& nums, T leftIdx, T rightIdx)
	{
		left = 0;
		right = nums.size() - 1;

		while (left <= right)
		{
			mid = calcMidPoint(left, right);

			if (nums[mid] == target)
				return mid;

			if (nums[mid] < target)
				left = ++mid;

			else
				right = --mid;
		}


	}

	template<typename T>
	T RotatedArraySearch<T>::search(std::vector<T>& nums, T targetInput)
	{
		int size = nums.size();
		target = targetInput;

		if (size == 0)
			return -1;

		if (!isRotated(nums))
			return search(nums, 0, size-1);
		int pp = pivotPoint(nums);
		left_1 = 0;
		right_1 = pp;
		left_2 = pp + 1;
		right_2 = size - 1;

		int search_1 = search(nums, left_1, right_1);
		int search_2 = search(nums, left_2, right_2);

		return search_1 != -1 ?  search_1: search_2;
	}

	std::vector<int> FindKClosetNeighbours::PrintKClosestNeighbours(
		std::vector<int>& inputArr,
		const int k,
		const int tgtIdx
	)
	{
		// Store target value
		tgtStore.push_back(inputArr[tgtIdx]);

		// Variable to store the end index of the input array 
		int LastIdx = inputArr.size() - 1;

		// Left and right indicies
		int LeftIdx, RightIdx;
		
		int count = 1;
		int i = 1;
		while (count < k)
		{
			LeftIdx = tgtIdx - i;
			RightIdx = tgtIdx + i;
			if (LeftIdx >= 0 && RightIdx <= LastIdx)
			{
				leftOfTgt_intermediate_Store.push(inputArr[LeftIdx]);
				rightOfTgtStore.push_back(inputArr[RightIdx]);
				count += 2;
			}
			else if (RightIdx <= LastIdx)
			{
				rightOfTgtStore.push_back(inputArr[RightIdx]);
				count += 1;
			}

			else if (LeftIdx >= 0)
			{
				leftOfTgt_intermediate_Store.push(inputArr[LeftIdx]);
				count += 1;
			}
			else
			{
				break;
			}
			i++;
		}

		if (count == k + 1)
		{
			rightOfTgtStore.erase(rightOfTgtStore.end() - 1);
		}

		std::vector <int> result;

		while (!leftOfTgt_intermediate_Store.empty())
		{
			result.push_back(leftOfTgt_intermediate_Store.top());
			leftOfTgt_intermediate_Store.pop();
		}
		result.push_back(inputArr[tgtIdx]);

		for (auto elem : rightOfTgtStore)
		{
			result.push_back(elem);
		}
		
		return result;
	}

	std::vector<int> FindKClosetNeighbours::PrintKClosestNeighbours_TARGETOUT(std::vector<int>& inputArr, const int k, const int tgtVal)
	{
		const int LowestVal = inputArr[0];
		const int HighestVal = inputArr[inputArr.size() - 1];

		std::vector<int> result;

		int count = 1;
		auto it = inputArr.begin();
		if (tgtVal < LowestVal)
		{
			while (count <= k)
			{
				result.push_back(*it++);
				++count;
			}
			
			return result; 
		}

		count = 1;
		it = inputArr.end() - 1;
		std::stack<int> tempStack;
		if (tgtVal > HighestVal)
		{
			while (count <= k)
			{
				tempStack.push(*it--);
				++count;
			}
			
			while (!tempStack.empty())
			{
				result.push_back(tempStack.top());
				tempStack.pop();
			}
			return result; 
		}

	}

}//namespace binary_search
#endif