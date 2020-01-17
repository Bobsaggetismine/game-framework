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
				bq::logger::debug("resource: " + location + " already loaded, returning loaded resource");
				return *m_resources[("res/" + location)];
			}
			else {
				bq::logger::debug("resource: " + location + " does not already exist, attempting to load...");
			}
			T* res = DBG_NEW T();
			if (res->loadFromFile("res/"+location)) {
				m_resources["res/"+location] = res;
				bq::logger::debug("resource: " + location + " loaded from file");
				return *m_resources["res/" + location];
			}
			else {
				bq::logger::warn("resource: " + location + " does not existing, defaulting to failed res");
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


