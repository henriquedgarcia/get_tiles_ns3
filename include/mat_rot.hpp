#ifndef MAT_ROT_H
#define MAT_ROT_H

#include <opencv2/core.hpp>

#include "types.hpp"

namespace MatRot {
cv::Mat get_matrix(ViewportCoord yaw_pitch_roll);

inline Point3D apply_matrix(const cv::Mat& mat, const Point3D& p) {
  /* Apply matrix M to point p */
  Point3D xyz;
  xyz.x = mat.at<double>(0, 0) * p.x + mat.at<double>(0, 1) * p.y + mat.at<double>(0, 2) * p.z;
  xyz.y = mat.at<double>(1, 0) * p.x + mat.at<double>(1, 1) * p.y + mat.at<double>(1, 2) * p.z;
  xyz.z = mat.at<double>(2, 0) * p.x + mat.at<double>(2, 1) * p.y + mat.at<double>(2, 2) * p.z;
  return xyz;
}

inline Frustrum rotate_frustrum(const Frustrum& frustrum, const cv::Mat& mat) {
  Frustrum rotated = frustrum;
  for (auto& normal : rotated.normals) {
    normal = apply_matrix(mat, normal);
  }

  return rotated;
}

class MatRot {
public:
    static cv::Mat get_matrix(const ViewportCoord& yaw_pitch_roll);

    static Frustrum rotate_frustrum(const Frustrum& frustrum, const cv::Mat& mat) {
        Frustrum rotated = frustrum;
        for (auto& normal : rotated.normals) {
            cv::Mat p = (cv::Mat_<double>(3,1) << normal.x, normal.y, normal.z);
            cv::Mat r = mat * p;
            normal.x = r.at<double>(0,0);
            normal.y = r.at<double>(1,0);
            normal.z = r.at<double>(2,0);
        }
        return rotated;
    }
};



}  // namespace MatRot

#endif  // MAT_ROT_H
