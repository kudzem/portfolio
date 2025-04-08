#include "my_string.h"
#include <string>

using namespace std;

int main() {

	{
		string s;
		my_string my_s;

		cout << "s = " << s << endl;
		cout << "my s = " << my_s << endl;
	}

	{
		string s = "i need a doctor";
		my_string my_s = "i need a doctor";

		cout << "s = " << s << endl;
		cout << "my s = " << my_s << endl;

		s = "I'm about to lose my mind";
		my_s = "I'm about to lose my mind";

		cout << "s = " << s << endl;
		cout << "my s = " << my_s << endl;
	}

	{
		string s("i need a doctor");
		my_string my_s("i need a doctor");

		cout << "s = " << s << endl;
		cout << "s size" << s.size() << endl;
		cout << "s capacity" << s.capacity() << endl;
		cout << "my_s = " << my_s << endl;
		cout << "s size" << my_s.size() << endl;
		cout << "s capacity" << my_s.capacity() << endl;
	}

	{
		string s2("to bring me back to life");
		string s(s2);
		my_string my_s2("to bring me back to life");
		my_string my_s(my_s2);

		cout << "s = " << s << endl;
		cout << "s size" << s.size() << endl;
		cout << "s capacity" << s.capacity() << endl;
		cout << "my_s = " << my_s << endl;
		cout << "s size" << my_s.size() << endl;
		cout << "s capacity" << my_s.capacity() << endl;
	}

	{
		string s2("to bring me back to life");
		string s(std::move(s2));
		my_string my_s2("to bring me back to life");
		my_string my_s(std::move(my_s2));

		cout << "s = " << s << endl;
		cout << "s size" << s.size() << endl;
		cout << "s capacity" << s.capacity() << endl;
		cout << "my_s = " << my_s << endl;
		cout << "s size" << my_s.size() << endl;
		cout << "s capacity" << my_s.capacity() << endl;
	}
}