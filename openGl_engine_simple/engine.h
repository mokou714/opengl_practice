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

		bool init();
		void run();
		void stop();

		void doLogic();
		void doRender();
		void beginFrame();
		void endFrame();

		void destroy();

	private:
		static Engine* s_engine;
		bool is_running;
		
		std::unordered_map<std::string, std::vector<GenericFunc<>>> m_inputEventsMap;
		Engine();
	};

}