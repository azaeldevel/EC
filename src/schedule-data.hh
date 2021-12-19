

#ifndef EC_SCHEDULE_DATA_HH
#define EC_SCHEDULE_DATA_HH

#include <map>


#include "ec.hh"


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

		void print(std::ostream&, const std::string) const;
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
	class Subject;
	class WeekHours;
	
	template<typename T> typename std::list<T>::const_iterator random(const std::list<T>& ls)
	{
		if(ls.size() > 1)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, ls.size() - 1);
			typename std::list<T>::const_iterator it = ls.begin();
			std::advance(it,dis(gen));				
			return it;
		}
		else if(ls.size() == 1)
		{
			return ls.begin();
		}
		
		return ls.end();
	}

	template<typename T> typename std::vector<T>::const_iterator random(const std::vector<T>& ls)
	{
		if(ls.size() > 1)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, ls.size() - 1);
			typename std::vector<T>::const_iterator it = ls.begin();
			std::advance(it,dis(gen));				
			return it;
		}
		else if(ls.size() == 1)
		{
			return ls.begin();
		}
		
		return ls.end();
	}
	

	enum check_codes
	{
		PASS,
		HOURS_DIFFERENT_DAY,
		BLOCK_CONTENT_SIZE_FAIL,
	};
	class Day : public std::list<core::DataTime>
	{
	public:
		typedef std::list<const core::DataTime*> Block;
		typedef std::list<Block> Blocks;
		
	public:
		Day();
		Day(const Day&);
		Day& operator =(const Day&);

		Blocks& get_blocks();
		const Blocks& get_blocks() const;

		/**
		*\brief determinar horas en comun
		**/
		Day& inters(const Day& comp1, const Day& comp2);

		/**
		*\brief determinar horas en comundeterminar en este dia
		*/
		bool haveDisponible()const;

		/**
		*\brief Determina las combinaciones possibles para cubir la clase indicada con el horario actual
		**/
		void combns(std::list<Day>&, unsigned int hours)const;

		/**
		*\brief Ordena y crea los bloques de horas
		*/
		void sort();

		void add(const Block& );

		void print_day(std::ostream&) const;
		void print_blocks(std::ostream&) const;


		/**
		*\brief Verifica la velides de la informacion
		*\return true si esta ordenada y los bloques estan formados correctamente, false en otro caso
		*/
		check_codes check()const;
	private:
		//static bool cmpHour(const core::DataTime& f,const core::DataTime& s);
		std::list<core::DataTime>::iterator blocking(std::list<core::DataTime>::iterator begin);
		
		/**
		*\brief Determina las combinaciones possibles para cubir la clase indicada con el bloque
		**/
		void combns(std::list<Day>&, unsigned int hours, const Block& b,Day&)const;
	private:
		Blocks blocks;
	};

	typedef std::list<Day> DaysOptions;
	//typedef std::vector<DaysCombs> WeekCombs;
	class WeekOptions : public std::vector<DaysOptions>
	{
	public:
		WeekOptions();
		
		/**
		*\brief Genera una semana al azar en base las opciones disponibles en el objeto
		**/
		void random(WeekHours&);


		/**
		*\brief Genera una semana al azar en base las opciones disponibles en el objeto
		**/
		unsigned int count()const;
	private:
		std::random_device rd;
	};
	class WeekHours : public std::vector<Day>
	{
	public:
		static const unsigned int WEEK_SIZE;

	public:
		WeekHours();

		const std::list<const Day*>& get_disponible()const;

		/**
		*\brief determinar horas en comun
		**/
		WeekHours& inters(const WeekHours& comp1, const WeekHours& comp2);

		/**
		*\brief Determina las combinaciones possibles para cubir la clase indicada con el horario actual
		**/
		//unsigned int combinations(const Subject*)const;

		/**
		*\brief Determina las combinaciones possibles para cubir la clase indicada con el horario actual
		**/
		void combns(const Subject& ,WeekOptions& )const;

		unsigned int days_disp() const;

		void sort();

		void print(std::ostream&) const;

		check_codes check()const;

		bool empty()const;
	private:
		void combns(std::list<WeekHours>&,const WeekOptions&)const;
	};

	struct Time
	{
		core::DataTime begin;
		core::DataTime end;

		Time();
		Time(const std::string&,const std::string&);
		/**
		*\brief Convirte el valor time en elementos de la clase Day
		**/
		void granulate(const Configuration*, Day& out);
		/**
		*\brief Convirte el valor time en elementos de la clase Day, crea los bloques de tiempo.
		**/
		void granulate(const Configuration*, WeekHours& out);
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
		//const std::string& get_format_string_datatime()const;
		//static const std::string& get_format_string_datatime(FormatDT);
		FormatDT get_format_dt()const;
		int get_begin_day() const;

	private:
		SchemaWeek schema_week;
		unsigned int time_per_hour;//en minutes por hora
		Schema schema;
		FormatDT format;
	public:
		static const std::string formats_dt_hour;
		static const std::string formats_dt_day_hour;
		static const std::string formats_dt_dayn_hour;
	};
		
	class Target
	{
	public:
		Target();
		Target(const Configuration*);
		void init();
		const Configuration* operator =(const Configuration*);
		const Configuration* set(const Configuration*);
		const WeekHours& get_week()const;	
		WeekHours& get_week();			
		void print(std::ostream&)const;
		/**
		*\brief Guarda la lista de horas indicadas en orden segun el dia indicado
		**/	
		//void save(const Day&);

		void sort();

	private:
		/**
		*\brief Fucion de ordenamiento ascendente
		**/
		//static bool cmpHour(const core::DataTime& f,const core::DataTime& s);
	private:
		const Configuration* config;
		WeekHours times;//horario de disponibilidad
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
		void fetch_times(Target&,std::stringstream&,unsigned int ,const std::string& );
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
		struct Row : public std::list<const Subject*>
		{
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
		const Row* searchTeachers(const std::string&)const;
		void searchSubjects(const std::string&, std::list<const Row*>& )const;
	private:
		void indexing();
	private:
		std::list<Row> teachers_subjects;
		std::map<std::string, Row*> teachers_by_name;
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


	struct Group : public std::vector<const Subject*>
	{
		const Room* room;
			
		Group();	
		void print(std::ostream&) const;
	};

	class Groups : public Targets
	{
	public:
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
	
	struct Goal
	{
		const Group* group;
		const Teacher* teacher;
		const Subject* subject;
		const Room* room;
		WeekHours week;
	};
	//typedef std::list<Goal> Goals;
	class Goals : public std::vector<Goal>
	{
	public:
		Goals();
		Goals(unsigned int);
		Goals(const Goals&);

		Goals& operator =(const Goals&);
		
		void juncting(const Goals&,const Goals&);
	private:
		std::random_device rd;
	};

	/**
	*\brief Difine las calses impartidas(por semana)
	**/
	typedef Goals Schedule;

	/**
	*\brief Variasiones del Horario
	**/
	struct Schedules : std::vector<Schedule>
	{

	};

	/*struct ScheduleStudent : public Schedule
	{

	private:	
		
	};
	struct ScheduleTeacher : public Schedule
	{


	private:	
		
	};

	struct ScheduleStudents : public std::vector<ScheduleStudent>
	{

	};
	struct ScheduleTeachers : public std::vector<ScheduleTeacher> 
	{

	};*/

}

#endif