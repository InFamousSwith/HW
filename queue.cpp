#include <vector>
#include <iostream>
 
template<typename T, typename Container = std::vector<T>>
        class priority_queue {
    Container hT;
 
 
 
    /**
	 * Возвращает индекс левого ребёнка по индексу родителя
	 * 2*i + 1
	 */
    int _leftChildIndex(int parentIndex)
    {
        int childIndex = 2 * parentIndex + 1;
        return childIndex;
    }
 
    /**
	 * Возвращает индекс правого ребёнка по индексу родителя
	 * 2*i + 2
	 */
    int _rightChildIndex(int parentIndex)
    {
        int childIndex = 2 * parentIndex + 2;
        return childIndex;
    }
 
    /**
	 * Возвращает индекс родителя по индексу ребёнка
	 * (int)(0.5 * i + 0.5) - 1
	 */
    int _parentIndex(int childIndex)
    {
        return ((0.5 * childIndex + 0.5) - 1);
    }
 
    /**
	 * "Просеивание" вверх
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
            hT[index] = hT[_parentIndex(index)];
            hT[_parentIndex(index)] = temp;
            _siftUp(_parentIndex(index));
        }
    }
 
 
    /**
	 * "Просеивание" вниз
	 */
    void _siftDown(int index)
    {
        int temp = hT[index];
        if (index < 0 || _leftChildIndex(index) > hT.size() - 1)
        {
            return;
        }
 
        if (hT[index] < hT[_leftChildIndex(index)] && ((_rightChildIndex(index) < hT.size() && hT[_leftChildIndex(index)] > hT[_rightChildIndex(index)]) ||
        _rightChildIndex(index) >= hT.size()))
        {
            hT[index] = hT[_leftChildIndex(index)];
            hT[_leftChildIndex(index)] = temp;
            _siftDown(_leftChildIndex(index));
        }
        else if (_rightChildIndex(index) < hT.size() && hT[index] < hT[_rightChildIndex(index)])
        {
            hT[index] = hT[_rightChildIndex(index)];
            hT[_rightChildIndex(index)] = temp;
            _siftDown(_rightChildIndex(index));
        }
    }
 
public:
    /**
	 * Добавление элемента в очередь
	 * Реализуется через siftUp
	 */
 
    priority_queue() = default;
 
    void push(const T& value) {
        hT.reserve(hT.size() + 1);
        hT.push_back(value);
        _siftUp(hT.size() - 1);
    }
 
    /**
	 * Возвращает верхний элемент очереди,
	 * НЕ удаляя его
	 *
	 * Возвращает первый элемент
	 */
    T top() const
    {
        return hT[0];
    }
 
    /**
	 * Возвращает верхний элемент очереди,
	 * удаляя его
	 *
	 * Возвращает первый элемент, удаляет его, делает siftDown
	 */
    T pop() {
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
	 * Проверяет, пустая очередь или нет
	 */
    bool empty() const
    {
        return hT.empty();
    }
 
    void Print() {
        for (const auto& val : hT) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
};
 
 
int main() {
    priority_queue<int> q;
    for (int i = 0; i < 5; ++i) {
        int value;
        std::cin >> value;
        q.push(value);
    }
    q.push(6);
    q.Print();
 
    q.pop();
    q.Print();
 
    return 0;
}
