#ifndef TEST_FRAMEWORK_HPP
#define TEST_FRAMEWORK_HPP

#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using TestFunction = std::function<void()>;
using FunctionName = std::string;
using TestCase = std::pair<FunctionName, TestFunction>;
using TestList = std::vector<TestCase>;

class AssertTrue : public std::exception {
  std::string message;

 public:
  explicit AssertTrue(const std::string &msg)
      : message(msg) {}

  const char *what() const noexcept override { return message.c_str(); }
};

inline void TEST_ASSERT(bool condition,
                        const std::string &message = "Assertion failed") {
  if (!condition) {
    throw AssertTrue(message);
  }
}

class TestRegistry {
 public:
  TestRegistry(std::string name);
  void add(const FunctionName &name, TestFunction fn);
  void runAll();
  void save_log();

 private:
  TestList tests;
  std::string log;
  std::string name;
};

#endif // TEST_FRAMEWORK_HPP