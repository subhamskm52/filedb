#include "filedb/importer/CsvImporter.h"
#include <csv.hpp>

namespace filedb::importer {
    void CsvImporter::import(const std::filesystem::path& file_path, Database &db) {
        csv::CSVReader _csv_file(file_path.generic_string());
        for (csv::CSVRow& row : _csv_file) {
          for (csv::CSVField& field:  row){
              std::cout << field.get() <<std::endl;
          }
        }
    }

}
