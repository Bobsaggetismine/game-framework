#pragma once
#include "bqpch.h"
#include <bq/core/logger.h>
namespace bq {

	template <class T>
	class resource_manager {
		
		std::string m_ext;
		std::map<std::string, std::unique_ptr<T>> m_resources;
	public:
		
		resource_manager(const std::string& ext): m_ext(ext) {
			std::unique_ptr<T> res = std::make_unique<T>();
			std::string name = "res/fail." + ext;
			res->loadFromFile(name);
			m_resources[name] = std::move(res);
		}
		const T& get(const std::string& location) {
			if (m_resources.find(("res/" + location))!= m_resources.end()) {
				return *m_resources[("res/" + location)];
			}
			else {
				bq::logger::debug("resource: " + location + " does not already exist, attempting to load...");
			}
			std::unique_ptr<T> res = std::make_unique<T>();
			if (res->loadFromFile("res/"+location)) {
				m_resources["res/"+location] = std::move(res);
				bq::logger::debug("resource: " + location + " loaded from file");
				return *m_resources["res/" + location];
			}
			else {
				bq::logger::warn("resource: " + location + " does not exist, defaulting to failed res");
				std::string name = "res/fail." + m_ext;
				return *m_resources[name];
			}
		}
	};
}


