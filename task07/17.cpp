#include<iostream>
#include<vector>
#include<memory>
#include<any>

using namespace std;

struct Installer
{
	Installer() = default;

	virtual void install(std::any we) = 0;
	virtual ~Installer() = default;

};


struct DemoInstaller : public Installer
{
public:

	DemoInstaller() = default;

	void install(std::any we)
	{

		if (we.type() == typeid(shared_ptr<Installer>))
		{
			cout << "Invalid feature\n";
			return;
		}
		
		cout << we.type().name() << "\n";
	}

};

vector<std::any> get_new_features()
{
	return vector<std::any>
	{
		shared_ptr<Installer>(new DemoInstaller), 
			string("I love my instructor"), 3, 3.14159, 
			shared_ptr<Installer>(new DemoInstaller)
	};
}
void install(vector<std::any> vec)
{

	auto inst = any_cast<shared_ptr<Installer>>(vec.front()) /* as shared_ptr<Installer> */;
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
