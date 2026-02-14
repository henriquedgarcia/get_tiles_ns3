#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include "types.h"
#include <iostream>
#include <string>
#include <vector>

class CsvHandler {
  private:
    const std::string filename;
    const std::vector<std::string> columnTypes;
    int write_header(std::ofstream& output_file_stream,
                     const std::vector<std::string>& headers = {});
    void write_csv_line(std::ofstream& out, const std::vector<Field>& values);

  public:
    CsvHandler(const std::string& filename,
               const std::vector<std::string>& columnTypes);
    int write(const std::vector<Row>& rows,
              const std::vector<std::string>& headers = {});
    std::vector<Row> read(bool skipHeader = true);
};

#endif // CSV_HANDLER_H