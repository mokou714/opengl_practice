#pragma once
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <string>


namespace simple_engine {
	template<typename... Args>
	using GenericFunc = void(*)(Args... args); //和typedef相比 using可以适用于template

	class Engine {

	public:
		static Engine* Instance();

		bool Initialize();
		void Run();
		void Stop();
		void DoLogic();
		void DoRender();
		void BeginFrame();
		void EndFrame();
		void Destroy();

	private:
		static Engine* s_engine;
		bool is_running;
		size_t m_frame_count;
		
		std::unordered_map<std::string, std::vector<GenericFunc<>>> m_inputEventsMap;
		Engine();
	};

}