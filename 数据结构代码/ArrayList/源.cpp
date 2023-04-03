#include <iostream>
#include <cstdio>
#define USE_OS
using namespace std;

//已提供
class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};



//start


template <typename T>
class ArrayList
{
private:
	T *val;
	int len;

public:
	ArrayList(T *arr, int length)
	{
		if (length < 0)
			throw error("invalid length");
		len = length;
		val = new T[len];
		for (int i = 0; i < len; i++)
			val[i] = arr[i];
	}
	ArrayList(int length)
	{
		if (length < 0)
			throw error("invalid length");
		len = length;
		val = new T[len];
	}
	ArrayList(const ArrayList<T> &a)
	{
		len = a.len;
		val = new T[len];
		for (int i = 0; i < len; i++)
			val[i] = a[i];
	}
	~ArrayList()
	{
		delete []val;
	}

	int size(void)
	{
		return len;
	}

	T &operator[](const int i) const
	{
		if (i >= len || i < 0)
			throw error("index out of bound");
		
		return val[i];
	}

	ArrayList<T> operator+(const ArrayList<T> &a) const
	{
		ArrayList<T> sum(len + a.len);
		int i = 0;
		for (; i < len; i++)
			sum[i] = val[i];
		for (; i < len + a.len; i++)
			sum[i] = a[i - len];
		return sum;
	}


	ArrayList<T> &operator=(const ArrayList<T> &a)
	{
		if (this == &a)
			return *this;
		len = a.len;
		delete []val;
		val = new T[len];
		for (int i = 0; i < len; i++)
			val[i] = a.val[i];
		return *this;
	}

	bool operator==(const ArrayList<T> &a) const
	{
		if (len != a.len)
			return false;
		if (this == &a)
			return true;
		for (int i = 0; i < len; i++)
		{
			if (!(val[i] == a.val[i]))
				return false;
		}
		return true;
	}

	bool operator!=(const ArrayList<T> &a) const
	{
		if (*this == a)
			return false;
		else return true;
	}

	template <typename X>
	friend ostream &operator<<(ostream &out, const ArrayList<X> &a);
	void print() const
	{
        for (int i = 0; i < len - 1; i++)
			cout << val[i] << " ";
		cout << val[len - 1];
    }
};

template <typename T>
ostream &operator<<(ostream &out, const ArrayList<T> &a)
{
	for (int i = 0; i < a.len - 1; i++)
		out << a.val[i] << " ";
	out << a.val[a.len - 1];
	return out;
}