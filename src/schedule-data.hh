

#ifndef EC_SCHEDULE_DATA_HH
#define EC_SCHEDULE_DATA_HH

#include <map>

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

		const std::string& operator =(const std::string& name);
		const std::string& get_name()const;

	private:
		std::string name; 
	};

}

namespace oct::ec::sche
{
	
	class Enviroment;
	struct Data;

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
				
	private:
		std::string name;
	};
		
	class Subject 
	{
	public:
		Subject(const std::string& name);
		Subject();
		void set(const std::string& name,unsigned int time );

		const std::string& get_name()const;
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

		const std::string& get_name()const;
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
			void print(std::ostream&)const; 	
		};
	
	public:
		Teachers();
		Teachers(const std::string& fn);
		const std::list<Row>& get_list() const;

		void loadFile(const std::string& fn);
		void print(std::ostream&);
		const Row* search(const std::string&) const;

	private:
		void indexing();

	private:
		std::list<Row> teachers;
		std::map<std::string, Row*> teacher_by_name;
	};

	class Subjects
	{
	public:
		struct Row
		{
			Subject subject;

			Row();
			void print(std::ostream&)const;
		};
		
	public: 
		Subjects(const std::string& fn);
		Subjects();
		void loadFile(const std::string& fn);
		void print(std::ostream&)const;
		const Row* search(const std::string&) const;
		const std::list<Row>& get_list() const;
		
	private:
		void indexing();
	private:
		std::list<Row> subjects;
		std::map<std::string, Row*> subject_by_name;
	};

	class Teachers_Subjects
	{
	public: 
		struct Row
		{
			const Subject* subject;
			const Teacher* teacher;

			Row();
			void print(std::ostream&)const;
		};
		
	public: 
		Teachers_Subjects();
		Teachers_Subjects(const std::string& fn,const Data* data);
		void loadFile(const std::string& fn,const Data* data);
		void print(std::ostream&)const;
		const std::list<Row>& get_list() const;
		void searchTeachers(const std::string&, std::list<Row*>& )const;
		void searchSubjects(const std::string&, std::list<Row*>& )const;
	private:
		void indexing();
	private:
		std::list<Row> teachers_subjects;
		std::multimap<std::string, Row*> teachers_by_name;
		std::multimap<std::string, Row*> subjects_by_name;
		const Data* dataObject;
	};

	class Rooms
	{
	public:
		struct Row : public std::vector<ec::sche::Time>
		{
			Room room;
			
			Row();
			Row(int z);		
			void print(std::ostream&) const;
		};
		
	public:
		Rooms();
		Rooms(const std::string& fn);
		const std::list<Row>& get_list() const;

		void loadFile(const std::string& fn);
		void print(std::ostream&)const;

		const Row* search(const std::string&)const;
		
	private:
		void indexing();

	private:
		std::list<Row> rooms;
		std::multimap<std::string, Row*> rooms_by_name;
	};

	class Groups
	{
	public:
		struct Row : public std::vector<const Subject*>
		{
			const Room* room;
			
			Row();	
			void print(std::ostream&) const;
		};
		
	public:
		Groups();
		Groups(const std::string& fn,const Data* data);
		const std::list<Row>& get_list() const;

		void loadFile(const std::string& fn,const Data* data);
		void print(std::ostream&)const;

		const Row* search(const std::string&)const;
		
	private:
		void indexing();

	private:
		std::list<Row> groups;
		std::multimap<std::string, Row*> groups_by_name;
		const Data* dataObjects;
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
		Groups groups;

		void load(const std::string& dir);
	};
	
	

}

#endif