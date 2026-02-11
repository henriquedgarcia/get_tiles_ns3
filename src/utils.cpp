#include "utils.h"

#include <fstream> // std::ofstream, std::ifstream
#include <iostream>
#include <numeric> // std::iota
#include <sstream> // std::stringstream
#include <variant> // std::variant
#include <vector>  // std::vector

#include "types.h"

std::pair<double, double> linear_regression(const std::vector<double>& y) {
    int n = (int)y.size();
    std::vector<double> x(n);
    std::iota(x.begin(), x.end(), 0);

    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_x2 = 0.0, sum_xy = 0.0;

    for (int i = 0; i < n; ++i) {
        sum_x2 += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    double denom = n * sum_x2 - sum_x * sum_x;
    double a = (n * sum_xy - sum_x * sum_y) / denom;
    double b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;

    return {a, b};
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
                                    int n_future = 30) {
    int n_input = data.size();

    // extrair cada coordenada
    std::vector<double> xs(n_input), ys(n_input), zs(n_input);
    for (int i = 0; i < n_input; ++i) {
        xs[i] = data[i].x;
        ys[i] = data[i].y;
        zs[i] = data[i].z;
    }

    // regressão linear separada
    auto [ax, bx] = linear_regression(xs);
    auto [ay, by] = linear_regression(ys);
    auto [az, bz] = linear_regression(zs);

    // prever próximos 30 pontos
    std::vector<Point3D> future;
    int start = n_input, end = n_input + n_future;

    for (int i = start; i < end; ++i) {
        double fx = ax * i + bx;
        double fy = ay * i + by;
        double fz = az * i + bz;
        future.push_back({fx, fy, fz});
    }

    return future;
}

using Field = std::variant<int, double, std::string>;

enum class Exception { FILE_NOT_FOUND };

using Row = std::vector<Field>;

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

CsvHandler::CsvHandler(const std::string& filename,
                       const std::vector<std::string>& columnTypes)
    : filename(filename), columnTypes(columnTypes) {
}

int CsvHandler::write_header(std::ofstream& output_file_stream,
                             const std::vector<std::string>& headers = {}) {
    int count = 0;

    if (!headers.empty()) { // Cabeçalho opcional
        std::vector<Field> headerFields(headers.begin(), headers.end());
        write_csv_line(output_file_stream, headerFields);
        count++;
    }
    return count;
};

void CsvHandler::write_csv_line(std::ofstream& out,
                                const std::vector<Field>& values) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::visit([&](auto&& val) { out << val; }, values[i]);
        if (i + 1 < values.size())
            out << ",";
    }
    out << "\n";
}

int CsvHandler::write(const std::vector<Row>& rows,
                      const std::vector<std::string>& headers = {}) {
    std::ofstream output_file_stream(this->filename);

    if (!output_file_stream.is_open())
        return -1;

    int count = this->write_header(output_file_stream, headers);

    for (const auto& row : rows) // Para cada linha, escreva os campos
    {
        write_csv_line(output_file_stream, row);
        count++;
    }
    output_file_stream.close();
    return count;
}

std::vector<Row> CsvHandler::read(bool skipHeader = true) {
    std::ifstream file(this->filename);
    std::vector<Row> rows;
    std::string line;

    if (!file.is_open())
        return rows;

    if (skipHeader) // descarta cabeçalho
        std::getline(file, line);

    // Para cada linha, use std::stringstream para dividir por vírgula e
    // converter os campos
    while (std::getline(file, line)) {
        std::string value;
        Row row;

        // Converte linha em stream de string para usar getline com delimitador
        std::stringstream ss(line);

        // Para cada coluna, leia o campo seguinte de acordo com o tipo
        // especificado em columnTypes
        for (size_t i = 0; i < columnTypes.size(); ++i) {
            // Leia um campo se não conseguir ler um campo, interrompe o loop
            if (!std::getline(ss, value, ','))
                break;

            // case "int", convert to int
            if (columnTypes[i] == "int") {
                row.push_back(std::stoi(value));
            }
            // case "double", convert to double
            else if (columnTypes[i] == "double") {
                row.push_back(std::stod(value));
            }
            // string is the default case
            else {
                row.push_back(value);
            }
        }
        rows.push_back(row);
    }

    return rows;
}

// int main() {
//     // Definindo os tipos das colunas: x,y,z como double
//     CsvHandler handler({"double","double","double"});

//     // Criando dados
//     std::vector<Row> data = {
//         {{1.0, 2.0, 3.0}},
//         {{4.0, 5.0, 6.0}},
//         {{7.0, 8.0, 9.0}}
//     };

//     // Escreve CSV
//     handler.write("points.csv", data, {"x","y","z"});

//     // Lê CSV
//     auto loaded = handler.read("points.csv");

//     for (const auto& row : loaded) {
//         double x = std::get<double>(row.fields[0]);
//         double y = std::get<double>(row.fields[1]);
//         double z = std::get<double>(row.fields[2]);
//         std::cout << x << ", " << y << ", " << z << "\n";
//     }
// }