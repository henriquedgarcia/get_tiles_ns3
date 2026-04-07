  // void Test::test_SeenTiles() {
  //   SeenTiles seen_tiles(fov, this->proj);
  //   std::vector<Tile> vptiles = seen_tiles.get_vptiles(yaw_pitch_roll);

  //   // informações sobre os tiles. fazer um loop também.
  //   cout << "\t" << "fov = " << fov[0] << "x" << fov[1] << endl;
  //   cout << "\t"
  //        << "yaw_pitch_roll = (yaw=" << yaw_pitch_roll[0]
  //        << ", pitch=" << yaw_pitch_roll[1] << ", roll=" << yaw_pitch_roll[2]
  //        << ")" << endl;
  //   cout << "\t" << "Number of visible tiles: " << vptiles.size() << endl;
  //   cout << "\t" << "Visible tiles indices: ";
  //   for (const Tile &tile : vptiles) {
  //     cout << tile.index << " ";
  //   };
  //   cout << endl;
  // };

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