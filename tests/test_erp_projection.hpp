#ifndef TEST_ERP_PROJECTION_HPP
#define TEST_ERP_PROJECTION_HPP

#include "erp.hpp"
#include "types.hpp"

class TestERP {
public:
  ERP *erp;
  Resolution resolution;
  Tiling tiling;

  TestERP(std::string &log);
  void test_Projection();
};
#endif // TEST_ERP_PROJECTION_HPP
