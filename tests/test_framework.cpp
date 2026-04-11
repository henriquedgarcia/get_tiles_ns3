#include "test_framework.hpp"
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

/*
A classe de teste deve criar um objeto std::string para armazenar o log dos
resultados dos testes e injetar no construtor do TestRegistry. O nome do log
será baseado no timestamp da execução desta classe. Pelo fato do projeto ser
pequeno os testes não serão paralelizados, assim o timestamp do log dever único.
Em seguida, a classe de teste deve adicionar os testes usando o método add e por
fim chamar o método runAll para executar os testes. O log será salvo pela classe
TestRegistry.

O método add recebe um objeto std::string com o nome do teste e uma função
lambda. O lambda deve chamar o método de teste correspondente. O método de teste
deve usar a macro TEST_ASSERT para verificar as condições do teste. Se a
condição for verdadeira, o teste passa, caso contrário, ele falha. Todo caso é
registrado no log.

Exemplo:

TestErpTransformations::TestErpTransformations() {
  std::string log = "TestErpTransformations:\n";
  TestRegistry tests(log);

  tests.add("test_mn2uv", [this]() { test_mn2uv(); });
  tests.add("test_uv2mn", [this]() { test_uv2mn(); });
  tests.runAll();
};

void TestErpTransformations::test_mn2uv() {
  Resolution resolution(4320, 2160);
  PointMN mn(1360, 1825);
  PointUV uv = erp::mn2uv(mn, resolution);
  TEST_ASSERT(uv[0] == 0.31493055555555555 && uv[1] == 0.84513888888888888,
              "mn2uv transformation failed");
}

void TestErpTransformations::test_uv2mn() {
  Resolution resolution(4320, 2160);
  PointUV uv(0.315, 0.845);
  PointMN mn = erp::uv2mn(uv, resolution);
  TEST_ASSERT(mn[0] == 1360 && mn[1] == 1825, "uv2mn transformation failed");
}

*/

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
