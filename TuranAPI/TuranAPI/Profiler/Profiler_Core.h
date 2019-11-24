#pragma once
#include "TuranAPI/API_includes.h"


/*
	Create a Profiling system that starts profiling in Begin_Profiling, profiles functions with Profile_Function, profiles scopes with Profile_Scope(name) and ends all profiling systems with End_Profiling!


*/


namespace TuranAPI {
	namespace Profiler {


		//Store a specific function or scope in this class!

		class TURANAPI Profiled_Scope {
		public:
			bool Is_Recording;
			long long START_POINT, END_POINT, THREAD_ID, DURATION;
			string NAME;
			//Use this constructor to fill the data later!
			Profiled_Scope();
			//Use this constructor to start profiling a scope!
			Profiled_Scope(const string& name);
			~Profiled_Scope();
		};

		//Store recording data in this class!

		class TURANAPI Profiling_Session {
		public:
			string FILEPATH;
			vector<Profiled_Scope> PROFILED_SCOPEs_ARRAY;

			Profiling_Session(const string& PATH);
			void FILL_PROFILING_DATA(Profiled_Scope* profiled_scopes_array, const unsigned int scope_number);
			~Profiling_Session();
		};

		//Use this class for recording!
		//Only one recording is possible!

		class TURANAPI Active_Profiling_Session : Profiling_Session {
			Active_Profiling_Session(const string& FILEPATH);
			static void* START_POINT_PTR;
			static Profiling_Session* SELF;
		public:
			~Active_Profiling_Session();

			friend TURANAPI void Begin_Recording_Session(const string& FILEPATH);
			friend TURANAPI void Stop_Recording_Session();
			friend TURANAPI void Save_a_ProfiledScope_toSession(const Profiled_Scope& PROFILED_SCOPE);
		};


		TURANAPI void Begin_Recording_Session(const string& FILEPATH);
		TURANAPI void Stop_Recording_Session();
		TURANAPI void Save_a_ProfiledScope_toSession(const Profiled_Scope& PROFILED_SCOPE);
		TURANAPI Profiling_Session* Load_a_Profiling_Resource(const string& PATH);
		TURANAPI void Save_a_ProfilingResource_toDisk(const Profiling_Session& Resource);
	}
}

/*
#define TURAN_BEGIN_PROFILING(filepath) TuranAPI::Profiler::Begin_Recording_Session(filepath)
#define TURAN_STOP_PROFILING() TuranAPI::Profiler::Stop_Recording_Session()
#define TURAN_PROFILE_SCOPE(name) TuranAPI::Profiler::Profiled_Scope ProfilingScope##__LINE__(name)
#define TURAN_PROFILE_FUNCTION() TURAN_PROFILE_SCOPE(__FUNCSIG__)
*/