

#ifndef EC_SCHEDULE_DATA_HH
#define EC_SCHEDULE_DATA_HH

#include "GA.hh"

namespace oct::core
{
	class DataTime : public tm
	{
	public:
		DataTime();
		const time_t* operator =(const time_t*);
		int get_week_day()const;
		int diffHours(DataTime& dt);
	};

	class Person
	{
	public:
		Person(const std::string& name,const std::string& ap,const std::string& am);
		Person(const std::string& name);
		Person();

		const Person& operator =(const std::string& name);
		virtual void get_name(std::string&);

	private:
		std::vector<std::string> names; 
	};

}

namespace oct::ec::sche
{
	
	class Enviroment;

	struct Time
	{
		core::DataTime begin;
		core::DataTime end;
	};

	class Configuration
	{
	public:
		enum SchemaWeek
		{
			MF,//Mondy - Fraday
			MS,//Monday - Sturday
		};
	public:
		Configuration(const std::string& name);

	private:
		SchemaWeek schema;
		
	};
		
	
	class Teacher : public oct::core::Person
	{
	public:
		Teacher(const std::string& name,const std::string& ap,const std::string& am);
		Teacher(const std::string& name);
		Teacher();
		
		virtual const std::string& get_name();
		
	private:
		std::string name;
	};
		
	class Subject 
	{
	public:
		Subject(const std::string& name);
		Subject();

		virtual const std::string& get_name();
		
	private:
		std::string name;
	};
	
	class Room 
	{
	public:
		Room(const std::string& name);
		Room();

		virtual const std::string& get_name();
		Room& operator =(const std::string&);
		
	private:
		std::string name;
	};

	
	
	class Teachers
	{
		struct Row : public std::vector<Time>
		{
			Teacher teacher;

			Row();
			Row(int z);		
		};
		
	public: 
		Teachers(const std::string& fn);
		void loadFile(const std::string& fn);
		void print(std::ostream&);

	private:
		std::list<Row> teachers;
	};

	class Subjects
	{
		struct Row
		{
			Subject subject;
			Teacher teacher;

			Row();
		};
		
	public: 
		Subjects(const std::string& fn);
		void loadFile(const std::string& fn);
		void print(std::ostream&);
	private:
		std::list<Row> rooms;
	};

	class Rooms
	{
		struct Row : public std::vector<ec::sche::Time>
		{
			Room room;
			Subject subject;
			
			Row();
			Row(int z);		
		};
		
	public:
		Rooms(const std::string& fn);
		void loadFile(const std::string& fn);
		void print(std::ostream&);
		
	private:
		std::list<Row> rooms;
	};
	
	typedef std::vector<core::DataTime> DaysTimes;

	struct Target
	{
		std::vector<DaysTimes> teacher;
		unsigned int subject;
		std::vector<DaysTimes> room;
	};
	
	typedef std::vector<Target> Pile;
	
	

}

#endif