#include <iostream>
#include<memory>
using namespace std;

template<typename T>
class Shared_ptr
{
private:
	T* _ptr;//指针
	int* _count;//引用次数的地址
public:
	Shared_ptr(T* ptr = nullptr) :_ptr(ptr)
	{
		if (_ptr)
		{
			_count = new int(1);
		}
		else
		{
			_count = new int(0);
		}
	}
	Shared_ptr(const Shared_ptr& ptr)
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}
	/*Shared_ptr& operator=(const Shared_ptr& ptr)
	{
		if (this == &ptr) {return *this;}
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}
		if (this->_ptr)
		{
			(*this->_count)--;  //A=B 把自己的指向指向给B
			if (this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;
		return *this;
	}*/
	Shared_ptr& operator=(const Shared_ptr& ptr)
	{
		if (this == &ptr) {return *this;}
		(*this->_count)--;  //A=B 把自己的指向指向给B
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;
		return *this;
	}

	//operator*重载
	T& operator*()
	{
		if (this->_ptr)
		{
			return *(this->_ptr);
		}
	}

	//operator->重载
	T& operator->()
	{
		if (this->_ptr)
		{
			return this->_ptr;
		}
	}

	//析构函数
	~Shared_ptr()
	{
		(*this->_count)--;
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
		}
	}
	int get_count()
	{
		return *this->_count;
	}
};

Unique_ptr(unique_ptr<T> const& ptr) = delete;
    Unique_ptr<T>& operator=(Unique_ptr<T> const& ptr) = delete;

template <typename T>
class Unique_ptr {//禁止拷贝构造和赋值，只允许移动构造和移动赋值
private:
    T* ptr_;
    void del() {
        if (ptr_)  //安全问题
        {
            delete ptr_;
            ptr_ = nullptr;  //防止野指针
        }
    }

public:
    Unique_ptr(T* ptr = nullptr) :ptr_(ptr) {}
    ~Unique_ptr() {
        del();
    }
    T& operator*() const {
        return *ptr_;
    }
	T* operator->() {
        return ptr_;
    }
    void reset() {
        del();
    }
    T* operator->() {
        return ptr_;
    }

    T* release() {
        T* p = ptr_;
        ptr_ = nullptr;
        return p;
    }
	void move(Unique_ptr<T>& t) {
		this->ptr_=t.release();	
	}
};




//测试
int main() 
{

	Shared_ptr<int> s_ptr(new int(8));
	cout << "共享指针的值：" << *s_ptr << endl;
	cout << "共享个数：" << s_ptr.get_count() << endl;
	Shared_ptr<int> s_ptr2(s_ptr);
	cout << "复制构造后个数：" << s_ptr.get_count() << endl;
	Shared_ptr<int> s_ptr3;
	s_ptr3 = s_ptr;
	cout << "赋值后个数：" << s_ptr.get_count() << endl;
	cout << endl << endl;

	Unique_ptr<int> ptr(new int(8));
	Unique_ptr<int> ptr11(new int(9));
	cout << "独占指针的值：" << *ptr << endl;
	ptr.move(ptr11);
	int* p = ptr.release();
	cout << "进行移动后释放的值：" << *p << endl;
	delete p;
	ptr11.~Unique_ptr();

	return 0;
}




