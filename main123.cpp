#include <vector>
#include <iostream>

template<typename T, typename Container = std::vector<T>>
class priority_queue {
	Container hT;



	/**
	 * ���������� ������ ������ ������ �� ������� ��������
	 * 2*i + 1
	 */
	int _leftChildIndex(int parentIndex)
	{
		int childIndex = 2 * parentIndex + 1;
		return childIndex;
	}

	/**
	 * ���������� ������ ������� ������ �� ������� ��������
	 * 2*i + 2
	 */
	int _rightChildIndex(int parentIndex)
	{
		int childIndex = 2 * parentIndex + 2;
		return childIndex;
	}

	/**
	 * ���������� ������ �������� �� ������� ������
	 * (int)(0.5 * i + 0.5) - 1
	 */
	int _parentIndex(int childIndex)
	{
		return ((0.5 * childIndex + 0.5) - 1);
	}

	/**
	 * "�����������" �����
	 */
	void _siftUp(int index)
	{
		if (index <= 0)
		{
			return;
		}
		if (hT[index] > hT[_parentIndex(index)])
		{
			int temp = hT[index];
			hT[index] = *hT[_parentIndex(index)];
			hT[_parentIndex(index)] = temp;
			_siftUp(_parentIndex(index));
		}
	}


	/**
	 * "�����������" ����
	 */
	void _siftDown(int index)
	{
		int temp = hT[index];
		if (index <= 0)
		{
			return;
		}

		if (hT[index] < hT[_leftChildIndex(index)])
		{
			hT[index] = hT[_leftChildIndex(index)];
			hT[_leftChildIndex(index)] = temp;
			_siftDown(_leftChildIndex(index));
		}
		else if (hT[index] < hT[_rightChildIndex(index)])
		{
			hT[index] = hT[_rightChildIndex(index)];
			hT[_rightChildIndex(index)] = temp;
			_siftDown(_rightChildIndex(index));
		}
	}

public:
	/**
	 * ���������� �������� � �������
	 * ����������� ����� siftUp
	 */
	T push()
	{
		int i;
		std::cin >> i;
		hT.resize(hT.size() + 1);
		hT.push_back(i);
		_siftUp(hT.size());
		return hT;
	}

	/**
	 * ���������� ������� ������� �������,
	 * �� ������ ���
	 *
	 * ���������� ������ �������
	 */
	T top() const
	{
		return hT[0];
	}

	/**
	 * ���������� ������� ������� �������,
	 * ������ ���
	 *
	 * ���������� ������ �������, ������� ���, ������ siftDown
	 */
	T pop()
	{
		T value = top();

		if (hT.size() != 1)
		{
			std::swap(hT[0], hT[hT.size() - 1]);
		}
		hT.pop_back();
		if (!empty())
		{
			_siftDown(0);
		}
		return value;
	}

	/**
	 * ���������, ������ ������� ��� ���
	 */
	bool empty() const
	{
		if (hT.epmty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

int main() {
	priority_queue<int> q;
}
