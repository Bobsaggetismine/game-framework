#pragma once
#include <bq/common.h>
namespace bq {

	template <class T>
	class resource_manager {
		
		std::string m_ext;
	public:
		std::map<std::string, T*> m_resources;
		resource_manager(std::string ext): m_ext(ext) {
			T* res = DBG_NEW T();
			std::string name = "res/fail." + ext;
			res->loadFromFile(name);
			m_resources[name] = res;
		}
		T& get(std::string location) {
			if (m_resources.find(("res/" + location))!= m_resources.end()) {
#ifdef _DEBUG
				bq::logger::info("resource: " + location + " already loaded, returning loaded resource");
#endif
				return *m_resources[("res/" + location)];
			}
#ifdef _DEBUG
			else {
				bq::logger::info("resource: " + location + " does not already exist, attempting to load...");
			}
#endif
			T* res = DBG_NEW T();
			if (res->loadFromFile("res/"+location)) {
				m_resources["res/"+location] = res;
#ifdef _DEBUG
				bq::logger::info("resource: " + location + " loaded from file");
#endif
				return *m_resources["res/" + location];
			}
			else {
#ifdef _DEBUG
			bq::logger::info("resource: " + location + " does not existing, defaulting to failed res");
#endif
				std::string name = "res/fail." + m_ext;
				return *m_resources[name];
			}
		}
		void close() {
			for (auto p : m_resources) {
				delete p.second;
			}
		}
	};
}


