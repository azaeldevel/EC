

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
		double diff(const DataTime& dt)const;
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
		Configuration();
		Configuration(const std::string& name);
		long to_hours(double )const;
		unsigned int get_time_per_hour() const;
		SchemaWeek get_schema_week()const;

	private:
		SchemaWeek schema_week;
		unsigned int time_per_hour;//en minutes
	};
		
	
	class Teacher : public oct::core::Person
	{
	public:
		Teacher(const std::string& name,const std::string& ap,const std::string& am);
		Teacher(const std::string& name);
		Teacher();
		
		const std::string& get_name();
		
	private:
		std::string name;
	};
		
	class Subject 
	{
	public:
		Subject(const std::string& name);
		Subject();
		void set(const std::string& name,unsigned int time );

		const std::string& get_name();
		unsigned int get_time()const;
		
	private:
		std::string name;
		unsigned int time;//tiempo que se devfe impartir de clase
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
	public:
		struct Row : public std::vector<Time>
		{
			Teacher teacher;

			Row();
			Row(int z);		
		};
	
	public:
		Teachers();
		Teachers(const std::string& fn);
		const std::list<Row>& get_list() const;

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

			Row();
		};
		
	public: 
		Subjects(const std::string& fn);
		Subjects();
		void loadFile(const std::string& fn);
		void print(std::ostream&);
	private:
		std::list<Row> rooms;
	};

	class Teachers_Subjects
	{
		struct Row
		{
			Subject subject;
			Teacher teacher;

			Row();
		};
		
	public: 
		Teachers_Subjects();
		Teachers_Subjects(const std::string& fn);
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
		Rooms();
		Rooms(const std::string& fn);
		void loadFile(const std::string& fn);
		void print(std::ostream&);
		
	private:
		std::list<Row> rooms;
	};
	
	typedef std::vector<core::DataTime> DaysTimes;
	struct TeacherDust
	{
		const Teacher* teacher;
		std::vector<DaysTimes> times;
	};

	struct Target
	{
		std::vector<TeacherDust> teachers;
		unsigned int subject;
		std::vector<DaysTimes> room;
	};
	
	typedef std::vector<Target> Pile;

	struct Data
	{
		Configuration config;
		Teachers teachers;
		Subjects subjects;
		Rooms rooms;
		Teachers_Subjects teachers_subjects;
	};
	
	

}

#endif