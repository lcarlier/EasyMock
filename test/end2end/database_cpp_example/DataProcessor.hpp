#include "Database.hpp"

class DataProcessor {
  Database& db;
public:
  DataProcessor(Database& database) : db(database) {}

  int process(std::string id) {
    if(!db.connect("db://test")) {
      return -1;
    }
    int value = db.fetchData(id);
    return value * 2;
  }
};