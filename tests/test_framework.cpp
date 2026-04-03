#include "test_framework.hpp"
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

std::string get_log_filename(std::string prefix) {
  auto agora = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(agora);
  std::tm tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << prefix << "_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".log";
  return oss.str();
}

void TestRegistry::add(const FunctionName &name, TestFunction fn) {
  tests.push_back({name, fn});
}

TestRegistry::TestRegistry(std::string name)
    : name(name),
      log("") {}

void TestRegistry::save_log() {
  std::string nomeArquivo = get_log_filename("test_log");
  std::ofstream arquivo(nomeArquivo);
  if (arquivo.is_open()) {
    arquivo << this->log;
    arquivo.close();
    std::cout << "Arquivo salvo como: " << nomeArquivo << "\n";
  } else {
    std::cerr << "Erro ao criar arquivo!\n";
  }
}

void TestRegistry::runAll() {
  std::string msg = this->name;
  std::cout << msg;
  this->log = msg;

  int passed = 0, failed = 0;
  for (auto &t : tests) {
    try {
      t.second();
      msg = "[OK] " + t.first + "\n";
      std::cout << msg;
      this->log = this->log + msg;
      passed++;
    } catch (const AssertTrue &e) {
      msg = "[FAIL] " + t.first + " -> " + std::string(e.what()) + "\n";
      std::cout << msg;
      this->log = this->log + msg;
      failed++;
    } catch (...) {
      msg = "[FAIL] " + t.first + " -> erro desconhecido\n";
      std::cout << msg;
      this->log = this->log + msg;
      failed++;
    }
  }

  msg = "Resumo: " + std::to_string(passed) + " passaram, " +
        std::to_string(failed) + " falharam.\n\n";
  std::cout << msg;

  this->log = this->log + msg;
  this->save_log();
}
