// UML_HW_06_Svyrydov.
//

#include <iostream>

using namespace std;

class Handler {
protected:
	Handler* next;

public:
	void setHandler(Handler* next) {
		this->next = next;
	}

	Handler() {}

	Handler(Handler* next) : next(next) {}

	virtual void process(string) = 0;
};


class MailChecker 
	: public Handler
{
public:
	MailChecker() : Handler() {}

	MailChecker(Handler* next) : Handler(next) {}

	void process(string data) override
	{
		char dog = '@';
		char point = '.';
		char space = ' ';

		bool dog_ = false;
		bool point_ = false;

		for (char c : data)
		{
			if (c == dog)
			{
				dog_ = true;
			}

			if (c == point && dog_)
			{
				point_ = true;
			}

			if (c == space && dog_ && point_)
			{
				break;
			}

			if (c == space && (!dog_ || !point_))
			{
				cout << "Wrong mail address" << endl;
				return;
			}
		}
		next->process(data);
	}
};


class PassChecker 
	: public Handler
{
public:
	PassChecker() : Handler() {}

	PassChecker(Handler* next) : Handler(next) {}

	void process(string data) override
	{
		char space = ' ';

		bool space_ = false;

		int passLen = 0;

		for (char c : data)
		{
			if (c == space)
			{
				space_ = true;
			}

			if (space_)
			{
				passLen++;
			}
		}

		if (passLen < 9)
		{
			cout << "Password is too short" << endl;
			return;
		}

		next->process(data);
	}
};


class Registrator
	: public Handler
{
public:
	Registrator() : Handler() {}

	Registrator(Handler* next) : Handler(next) {}

	void process(string data) override
	{
		cout << "Registration success" << endl;

		if (next == nullptr)
		{
			return;
		}
		next->process(data);
	}
};


int main()
{
	Handler* action = new MailChecker(new PassChecker(new Registrator()));

	cout << "aaagmail.com 11111111" << endl;
	action->process("aaagmail.com 11111111");

	cout << "aaa@gmailcom 11111111" << endl;
	action->process("aaa@gmailcom 11111111");

	cout << "aaa@gmail.com 111111" << endl;
	action->process("aaa@gmail.com 111111");

	cout << "aaa@gmail.com 11111111" << endl;
	action->process("aaa@gmail.com 11111111");
}