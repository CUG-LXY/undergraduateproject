
#include <iostream>
using namespace std;
template <typename T>
class Unique_ptr {
private:
    T* ptr_;
    //���ÿ������캯�������أ�,�Ӷ���ռ����
    Unique_ptr(unique_ptr<T> const& up) = delete;
    Unique_ptr<T>& operator=(Unique_ptr<T> const& up) = delete;
    void del() {
        if (ptr_)  //��ֹ�ͷ�����Ȩ��delete
        {
            delete ptr_;
            ptr_ = nullptr;  //��ֹҰָ��
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
    void reset() {
        del();
    }
    T* get() const {
        return ptr_;
    }
    T* release() {
        T* p = ptr_;
        ptr_ = nullptr;
        return p;
    }
    T* operator->() {
        return ptr_;
    }
};


template <typename T>
T* move(Unique_ptr<T>& tmp) {
    if (tmp.get()) {
        return tmp.release();
    }
}
// test
int main() {

    Unique_ptr<int> up(new int(10));
    cout << "  " << *up << endl;
    int* p = up.release();  //�ͷ�unque_ptr������Ȩ�����ض���ĵ�ַ
    cout << "p: " << *p << endl;
    delete p;  //�ͷ��ڴ棬�����ڴ�й¶

    struct num {
        int a_;
        int b_;
        num(int a, int b) : a_(a), b_(b) {}
    };
    Unique_ptr<num> up2(new num(1, 2));
    cout << up2->a_ << endl;

    Unique_ptr<int> up3(new int[10]);
    *(up3.get() + 3) = 10;

    Unique_ptr<int> up4(move(up3));
    cout << "up4: " << *(up4.get() + 3) << endl;
    return 0;
}
