#include<iostream>
#include<fstream>
#include<random>
#include<sstream>
#include<string>
#include<map>
#include<variant>
#include<any>

using namespace std;

enum string_code {
	INFORMATION, TRAIN, WARNING,
	ARRIVAL, DEPARTURE,
	NONE, MILD, MEDIUM, HIGH, CRITICAL
};

string_code hashit(std::string const& inString)
{
	if (inString == "INFORMATION") return INFORMATION;
	if (inString == "TRAIN")       return TRAIN;
	if (inString == "WARNING")     return WARNING;
	if (inString == "none")        return NONE;
	if (inString == "mild")        return MILD;
	if (inString == "medium")      return MEDIUM;
	if (inString == "high")        return HIGH;
	if (inString == "critical")    return CRITICAL;
}

class InfoObject
{
public:
	string msg;
	InfoObject() = default;
	InfoObject(const string &m) :msg(m) {};
	friend ostream& operator << (ostream &os, const InfoObject &message)
	{
		os << "INFORMATION " << message.msg << '\n';
		return os;
	}
};

class TrainObject
{
public:
	const enum class Direction :int { ARRIVAL, DEPARTURE };
	static map<string, Direction> Direction_map;
	int train_id;
	Direction direction;
	string time;

	TrainObject(int id, Direction dir, string tm) : train_id(id), direction(dir), time(tm) {};

	friend ostream& operator << (ostream &os, const TrainObject &message)
	{
		os << "TRAIN " << message.train_id << ", " <<
			((message.direction == Direction::ARRIVAL) ? "arrival" : "departure")
			<< " at " << message.time << '\n';
		return os;
	}
};

class WarningObject
{
public:
	const enum class Severity :int { NONE, MILD, MEDIUM, HIGH, CRITICAL };
	static map<string, Severity> Severity_map;

	Severity severity;

	string msg;

	WarningObject(string text, Severity sever) : msg(text), severity(sever) {}

	friend ostream& operator << (ostream &os, const WarningObject &message)
	{
		const char* severity_values[5] = { "none", "mild", "medium", "high", "critical" };
		os << "WARNING " << message.msg << "(" <<
			severity_values[static_cast<std::underlying_type_t<Severity>>(message.severity)] << ")\n";
		return os;
	}
};

class Message {

public:

	Message() { type = InfoObject{}; };
	~Message() {};
	std::variant<InfoObject, TrainObject, WarningObject> type;


	friend istream& operator >> (istream &is, Message &message)
	{
		auto svr = WarningObject::Severity::NONE;
		string str, type, dir, time;
		string msg2;
		getline(is, str);

		istringstream iss(str);
		iss >> type;

		switch (hashit(type))
		{
		case INFORMATION:
			iss.get();
			getline(iss, msg2);
			message.type = InfoObject{ msg2 };
			break;
		case TRAIN:
			int id;
			iss >> id;
			//,
			iss >> dir;
			iss >> dir;
			iss >> time;
			iss.get();
			getline(iss, time);


			if (dir == "arrival")
				message.type = TrainObject{ id,TrainObject::Direction::ARRIVAL, time };
			else
				message.type = TrainObject{ id,TrainObject::Direction::DEPARTURE, time };


			break;
		case WARNING:
			iss.get();
			string temp, temp2;
			getline(iss, temp);
			int last_pos = temp.find_last_of("(");
			temp2 = temp.substr(0, last_pos);

			string severity;
			severity = temp.substr(last_pos + 1, temp.size() - last_pos - 2);

			switch (hashit(severity))
			{
			case     NONE: svr = WarningObject::Severity::NONE;     break;
			case     MILD: svr = WarningObject::Severity::MILD;     break;
			case   MEDIUM: svr = WarningObject::Severity::MEDIUM;   break;
			case     HIGH: svr = WarningObject::Severity::HIGH;     break;
			case CRITICAL: svr = WarningObject::Severity::CRITICAL; break;
			default: break;
			}
			message.type = WarningObject{ temp2, svr };
			break;
		}

		return is;
	}
};


void produce_schedule(const char* name)
{
	ofstream out_file(name);

	out_file << InfoObject{ "All is fine in this fine city" };

	out_file << TrainObject{ 3, TrainObject::Direction::ARRIVAL,
		"8:0" };

	out_file << TrainObject{ 7, TrainObject::Direction::DEPARTURE,
		"10:15" };

	out_file << TrainObject{ 2,TrainObject::Direction::ARRIVAL,
		"12:20" };

	out_file << WarningObject{ "Please do not litter", WarningObject::Severity::MEDIUM };
}

void consume(Message &message)
{
	std::visit([](auto&& arg){ cout << arg; }, message.type);
}

int main()
{
	produce_schedule("sched.txt");
	// this interface has been imposed by your architects

	ifstream schedule{ "sched.txt" };
	for (Message msg; schedule >> msg; )
		consume(msg);

	system("pause");

	return 0;
}
