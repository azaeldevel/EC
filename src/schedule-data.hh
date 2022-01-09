

#ifndef EC_SCHEDULE_DATA_HH
#define EC_SCHEDULE_DATA_HH

#include <map>
#include <ctime>

#include "ec.hh"


namespace oct::core
{
	class Time : public std::tm
	{
	public:
		Time();
		Time(const tm&);
		Time(const Time&);

		const std::time_t* operator =(const std::time_t*);
		const std::time_t& operator =(const std::time_t&);
		const tm& operator =(const tm&);
		const Time& operator =(const Time&);
		bool operator ==(const Time&)const;
		bool operator ==(const std::time_t&)const;
		bool operator <(const Time&)const;
		bool operator >(const Time&)const;

		int get_week_day()const;
		double diff(const Time& dt)const;

		void addSeconds(std::time_t);

		void print(std::ostream&, const std::string&) const;

		void read(const std::string& time, const std::string& format);
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
		if(ls.size() == 0) ls.end();
		if(ls.size() == 1) ls.begin();
		
		std::uniform_int_distribution<> distrib(0, ls.size() - 1);
		typename std::list<T>::const_iterator it = ls.begin();
		std::advance(it,distrib(dre));				
		return it;
	}

	template<typename T> typename std::vector<T>::const_iterator random(const std::vector<T>& ls)
	{
		if(ls.size() == 0) ls.end();
		if(ls.size() == 1) ls.begin();
		
		std::uniform_int_distribution<> distrib(0, ls.size() - 1);
		typename std::vector<T>::const_iterator it = ls.begin();
		std::advance(it,distrib(dre));				
		return it;
	}




	/**
	*\brief Tomando como referencia el valor second, verifica se sucede a first
	*\return true en caso de que la relacion se cumpla, falso en caso de que no
	*/
	bool is_post_hour(const core::Time& first,const core::Time& second, const Configuration&);
	/**
	*\brief Tomando como referencia el valor second, verifica si a first antesede
	*\return true en caso de que la relacion se cumpla, falso en caso de que no
	*/
	bool is_prev_hour(const core::Time& first,const core::Time& second, const Configuration&);
	void add_hours(core::Time& first,unsigned int hours, const Configuration& config);
	void rest_hours(core::Time& first,unsigned int hours, const Configuration& config);


	enum check_codes
	{
		PASS,
		HOURS_DIFFERENT_DAY,
		BLOCK_CONTENT_SIZE_FAIL,
	};
	class Day : public std::list<core::Time>
	{
	public:
		typedef std::list<const core::Time*> Block;
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
		void print_intevals_csv(std::ostream&,const Configuration& data) const;


		/**
		*\brief Verifica la velides de la informacion
		*\return true si esta ordenada y los bloques estan formados correctamente, false en otro caso
		*/
		check_codes check()const;

		const Block* random_block() const;

		/**
		*\brief Agrega al bloques las horas solicitas, lo mas cercanas possibles a la hora indicada
		*/
		void get_hours_around(const core::Time&, unsigned int count,Block& )const;
		/**
		*\brief Agrega al bloques 1 hora, lo mas cercanas possibles a la hora indicada
		*/
		void get_hours_around(const core::Time&,Block& )const;

		static bool is_continue(const core::Time& first, const core::Time& second, const Data&);

	private:
		//static bool cmpHour(const core::DataTime& f,const core::DataTime& s);
		std::list<core::Time>::iterator blocking(std::list<core::Time>::iterator begin);
		
		/**
		*\brief Determina las combinaciones possibles para cubir la clase indicada con el bloque
		**/
		void combns(std::list<Day>&, unsigned int hours, const Block& b,Day&)const;
	private:
		Blocks blocks;
	};

	//typedef std::list<Day> DaysOptions;
	class DaysOptions : public std::list<Day>
	{
	public:
		void random(Day&)const;
	};
	//typedef std::vector<DaysCombs> WeekCombs;
	class WeekOptions : public std::vector<DaysOptions>
	{
	public:
		WeekOptions();
		
		/**
		*\brief Genera una semana al azar en base las opciones disponibles en el objeto
		**/
		void random(WeekHours&)const;


		/**
		*\brief Genera una semana al azar en base las opciones disponibles en el objeto
		**/
		unsigned int count()const;
		/**
		*\brief Optiene para el dia numero 'day' la canitad de 'hours' en la hora 'base' si encuentra coloca el resultado en 'result' y retorna true
		**/
		bool get_day(unsigned int day,unsigned int hours,const core::Time& at,const Configuration& ,Day& result)const;
	private:
		//std::random_device rd;
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

		void print_intevals_csv(std::ostream&,const Configuration& data) const;

		check_codes check()const;

		bool empty()const;
		
		/**
		*\brief Cuenta las horas que hay en esta semana
		**/
		unsigned int count_hours()const;

		void clear_days();

		/**
		*\brief Genera un horario aleatorio para cubir la materia indicada, con el horario disponible actaul
		**/
		void cover(const Subject&, WeekHours&)const;

		/**
		*\brief Seleciona un dia al azar
		**/
		const Day* random_day_disp()const;
		
		/**
		*\brief Optiene para el dia numero 'day' la canitad de 'hours' en la hora 'base' si encuentra coloca el resultado en 'result' y retorna true
		**/
		bool get_day(unsigned int day,unsigned int hours,const core::Time& at,const Configuration& ,Day& result)const;

	private:
		void combns(std::list<WeekHours>&,const WeekOptions&)const;
	};

	struct IntervalTime
	{
		core::Time begin;
		core::Time end;

		IntervalTime();
		IntervalTime(const std::string&,const std::string&);
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
		unsigned int to_hours(double )const;
		//unsigned int get_time_per_hour() const;
		unsigned int get_seconds_per_hour() const;
		SchemaWeek get_schema_week()const;
		Schema get_schema()const;
		void set_schema(Schema);
		//const std::string& get_format_string_datatime()const;
		//static const std::string& get_format_string_datatime(FormatDT);
		FormatDT get_format_dt()const;
		int get_begin_day() const;
		real get_hours_sigma()const;
		const std::string get_out_directory()const;

		/**
		*\brief Agrega a la hora indicada, la cantidad de horas indicas y coloca el resultado el variable de retorno
		*\param dt hora a base, operando para sumar
		*\param hours cantiad de horas a agregar a dt
		*\param result variable de retorno, donde se coloca el resultado de la operacion
		*/
		void add(const core::Time& dt, unsigned int hours, core::Time& result);

		/**
		*\brief Resta a la hora indicada, la cantidad de horas indicas y coloca el resultado el variable de retorno
		*\param dt hora a base, operando para restar
		*\param hours cantiad de horas a restar a dt
		*\param result variable de retorno, donde se coloca el resultado de la operacion
		*/
		void rest(const core::Time& dt, unsigned int hours, core::Time& result);
	private:
		SchemaWeek schema_week;
		unsigned int seconds_per_hour;//en minutes por hora
		Schema schema;
		FormatDT format;
		real hours_sigma;
		std::string out_dir;
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
		struct HBS
		{
			const Subject* subject;			
			const Row* row;
			unsigned int req_hours;
			unsigned int disp_hours;
		};
	public: 
		Teachers_Subjects();
		Teachers_Subjects(const std::string& fn,const Data* data);
		void loadFile(const std::string& fn);
		void print(std::ostream&)const;

		const std::list<Row>& get_list() const;
		const std::map<std::string, HBS>& get_hbs()const;

		const Row* searchTeachers(const std::string&)const;
		void searchSubjects(const std::string&, std::list<const Row*>& )const;
		void hour_by_subjects_csv(std::ofstream& fn);
		
	private:
		void indexing();
	private:
		std::list<Row> teachers_subjects;
		std::map<std::string, Row*> teachers_by_name;
		std::multimap<std::string, Row*> subjects_by_name;
		std::map<std::string, HBS> hbs_by_subject;
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
		std::string name;//TODO:soporte para gruopos en distintos salon
		const Room* room;
			
		Group();	
		void print(std::ostream&) const;
	};

	class Groups : public Targets
	{
	public:
		typedef std::list<Group>::iterator iterator;
		typedef std::list<Group>::const_iterator const_iterator;
		struct key_hbs
		{
			const Room* room;
			const Subject* subject;

			bool operator < (const key_hbs&) const;
		};

		struct HBRS
		{
			const Room* room;
			const Subject* subject;
			const Group* group;	
			//unsigned int req_hours;
			unsigned int disp_hours;
		};
	public:
		Groups();
		Groups(const std::string& fn,const Data* data);
		const std::list<Group>& get_list() const;
		unsigned int get_max_lessons()const;
		const std::map<key_hbs, HBRS>& get_hbrs()const;

		void loadFile(const std::string& fn);
		void print(std::ostream&)const;

		const Group* search_name(const std::string&)const;
		const Group* search_by_subject(const std::string&)const;

	private:
		void indexing();

	private:
		std::list<Group> groups;
		std::map<std::string, Group*> groups_by_name;
		std::multimap<std::string, Group*> groups_by_subject;
		unsigned int max_lessons;
		std::map<key_hbs, HBRS> hbrs_list;//horas disponible por materia y salon
	};
	
	typedef std::vector<core::Time> DaysTimes;
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
	
	struct Lesson
	{
		const Group* group;
		const Subject* subject;
		const Teacher* teacher;
		const Room* room;
		const Data* data;
		WeekHours week;

		Lesson();
	};
	
	/**
	*\brief Clases impartidas aun gurpo
	**/
	class ClassRoom : public std::vector<Lesson>
	{
	public:
		ClassRoom();
		ClassRoom(unsigned int);
		ClassRoom(const ClassRoom&);

		ClassRoom& operator =(const ClassRoom&);
		
		void juncting(const ClassRoom&,const ClassRoom&);

		void mutate();
		
		void save_csv(std::ostream&) const;

	private:
	private:
	};

	/**
	*\brief 
	**/
	class Schedule : public std::vector<ClassRoom>
	{
	public:
		Schedule();
		Schedule(unsigned int);
		Schedule(const Schedule&);
		
		Schedule& operator =(const Schedule&);

		void search_teachers(const std::string&, std::vector<const Lesson*>&)const;
		
		void indexing();

		void juncting(const Schedule&,const Schedule&);

		void mutate();
		
		void save_csv(const Configuration&) const;
	private:

	private:
		std::multimap<std::string, const Lesson*> lesson_by_teacher;
		
	};

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

	namespace output
	{
		class Schedules
		{

		};

		class Teacher
		{

		};

		struct Day
		{
			const sche::Subject* subject;
			const sche::Teacher* teacher;
			const sche::Room* room;
			WeekHours week;
		};

		class Student : public std::vector<Day>
		{
		public:
			
		public:
			Student();
			Student(const ClassRoom& );
			Student& operator =(const ClassRoom& );
			void print_csv(std::ostream&,const Configuration&) const;
		private:
			const sche::Group* group;
		};

		class Students : public std::vector<Student>
		{
		public:
			
		public:
			Students(const sche::Schedule& );
			void print_csv(std::ostream&,const Configuration&) const;
		};
	}

}

#endif