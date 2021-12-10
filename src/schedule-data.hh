

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
		DataTime(const tm&);
		const time_t* operator =(const time_t*);
		const tm& operator =(const tm&);
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
	class Configuration;
	
	typedef std::list<core::DataTime> Day;
	struct Time
	{
		core::DataTime begin;
		core::DataTime end;

		void granulate(const Configuration*, Day& out);
		void set_begin(const Configuration*,const std::string& str);
		void set_end(const Configuration*,const std::string& str);
		void set_begin(const std::string& str);
		void set_end(const std::string& str);
		
	};
	
	

	class Configuration
	{
	public:
		enum SchemaWeek
		{
			MF,//Monday - Fraday
			MS,//Monday - Saturday
		};
		enum Schema
		{
			UNKNOW,
			NORMAL,
			WITH_SUBJECTS_TIMES,
		};
		enum FormatDT
		{
			NONE,
			HOUR,
			DAY_HOUR,
		};

	public:
		Configuration();
		Configuration(const std::string& name);
		long to_hours(double )const;
		unsigned int get_time_per_hour() const;
		SchemaWeek get_schema_week()const;
		Schema get_schema()const;
		void set_schema(Schema);
		const std::string& get_format_string_datatime()const;
		FormatDT get_format_dt()const;
		int get_begin_day() const;

	private:
		SchemaWeek schema_week;
		unsigned int time_per_hour;//en minutes por hora
		Schema schema;
		FormatDT format;
		static std::string formats_dt_hour;
		static std::string formats_dt_day_hour;
	};
		
	class Target
	{
	public:
		Target();
		Target(const Configuration*);
		void init();
		const Configuration* operator =(const Configuration*);
		const Configuration* set(const Configuration*);
		const std::vector<Day>& get_times()const;	
		std::vector<Day>& get_times();			
		void print(std::ostream&)const;
		/**
		*\brief Guarda la lista de horas indicadas en orden segun el dia indicado
		**/	
		void save(const Day&);

		void sort();

	private:
		/**
		*\brief Fucion de ordenamiento ascendente
		**/
		static bool cmpHour(const core::DataTime& f,const core::DataTime& s);
	private:
		const Configuration* config;
		std::vector<Day> times;//horario de disponibilidad
	};


	class Teacher : public oct::core::Person, public Target
	{
	public:
		Teacher(const std::string& name,const std::string& ap,const std::string& am);
		Teacher(const std::string& name);
		Teacher();
		void init(); 		
		void print(std::ostream&)const;
		
	protected:	
	private:
		std::string name;
	};
		
	class Subject : public Target
	{
	public:
		Subject(const std::string& name);
		Subject();
		void set(const std::string& name,unsigned int time );

		const std::string& get_name()const;
		unsigned int get_time()const;
		void print(std::ostream&)const;

	public:		

	private:
		std::string name;
		unsigned int time;//tiempo que se devfe impartir de clase
	};
	
	class Room : public Target
	{
	public:
		Room(const std::string& name);
		Room();

		const std::string& get_name()const;
		Room& operator =(const std::string&);
		void print(std::ostream&) const;
		
	public:		

	private:
		std::string name;
	};

	
	class Targets
	{

	public:
		Targets();
		Targets(const Data*);
		
		const Data* operator = (const Data*);
		const Data* set(const Data*);

	protected:
		const Data* dataObject;
	};
	
	class Teachers : public Targets
	{		
	public:
	
	public:
		Teachers();
		Teachers(const std::string& fn);
		const std::list<Teacher>& get_list() const;

		void loadFile(const std::string& fn);
		void print(std::ostream&);
		const Teacher* search(const std::string&) const;


	private:
		void indexing();

	private:
		std::list<Teacher> teachers;
		std::map<std::string, Teacher*> teacher_by_name;
	};

	class Subjects : public Targets
	{
	public:
		
	public: 
		Subjects(const std::string& fn, const Data* );
		Subjects();
		void loadFile(const std::string& fn);
		void print(std::ostream&)const;
		const Subject* search(const std::string&) const;
		const std::list<Subject>& get_list() const;
		
	private:
		void indexing();
	private:
		std::list<Subject> subjects;
		std::map<std::string, Subject*> subject_by_name;
	};

	class Teachers_Subjects : public Targets
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
		void loadFile(const std::string& fn);
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
	};

	class Rooms : public Targets
	{
	public:
		
	public:
		Rooms();
		Rooms(const std::string& fn);
		const std::list<Room>& get_list() const;

		void loadFile(const std::string& fn);
		void print(std::ostream&)const;

		const Room* search(const std::string&)const;
		
	private:
		void indexing();

	private:
		std::list<Room> rooms;
		std::multimap<std::string, Room*> rooms_by_name;
	};

	class Groups : public Targets
	{
	public:
		struct Group : public std::vector<const Subject*>
		{
			const Room* room;
			
			Group();	
			void print(std::ostream&) const;
		};
		typedef std::list<Group>::iterator iterator;
		typedef std::list<Group>::const_iterator const_iterator;

	public:
		Groups();
		Groups(const std::string& fn,const Data* data);
		const std::list<Group>& get_list() const;

		void loadFile(const std::string& fn);
		void print(std::ostream&)const;

		const Group* search_name(const std::string&)const;
		const Group* search_by_subject(const std::string&)const;

	private:
		void indexing();

	private:
		std::list<Group> groups;
		std::multimap<std::string, Group*> groups_by_name;
		std::multimap<std::string, Group*> groups_by_subject;
	};
	
	typedef std::vector<core::DataTime> DaysTimes;
	struct TeacherDust
	{
		const Teacher* teacher;
		std::vector<DaysTimes> times;
	};

	/*struct Target
	{
		std::vector<TeacherDust> teachers;
		unsigned int subject;
		std::vector<DaysTimes> room;
	};*/
	
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