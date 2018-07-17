#include<iostream>
#include<vector>
#include<memory>

using namespace std;

class whatever
{
public:

	struct Iplaceholder
	{
		virtual void print() = 0;
	};

	shared_ptr<Iplaceholder> ptr;

	template<typename T>
	struct placeholder : public Iplaceholder
	{
		T value;
		placeholder(const T& v) : value(v) {}

		void print() override { cout << typeid(value).name() << '\n'; }
	};

public:

	template<typename T>
	whatever(const T &el) { ptr = shared_ptr<Iplaceholder>(new placeholder<T>(el) ); }
	~whatever() {  }

	template<typename T>
	friend T whatever_cast(const whatever&);

	void print(){ ptr->print(); }
};
template<typename T>
T whatever_cast(const whatever &we)
{
	return dynamic_pointer_cast<whatever::placeholder<T>>(we.ptr)->value;
}

struct Installer
{
	virtual void install(whatever we) = 0;
	virtual ~Installer() = default;
};

struct DemoInstaller : public Installer
{
public:
	void install(whatever we) override
	{
		we.print();
	}
};

vector<whatever> get_new_features()
{
	return vector<whatever>
	{
		shared_ptr<Installer>(new DemoInstaller),
			string("I love my instructor"), 3, 3.14159
	};
}
void install(vector<whatever> vec)
{
	auto inst = whatever_cast<shared_ptr <Installer> > (vec.front()) /* as shared_ptr<Installer> */;

	for (auto p = next(begin(vec)); p != end(vec); ++p)
	{
		inst->install(*p);
	}
}


int main()
{
	install(get_new_features());

	system("pause");
	return 0;
}
