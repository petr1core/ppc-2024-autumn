#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "core/task/include/task.hpp"

namespace varfolomeev_g_matrix_max_rows_vals_seq {

int searchMaxInVec(std::vector<int> vec);
std::vector<std::vector<int>> generateMatrix(int rows, int cols, int a, int b);

class MaxInRows : public ppc::core::Task {
 public:
  explicit MaxInRows(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  int size_n, size_m;
  std::vector<std::vector<int>> mtr;
  std::vector<int> res_vec;
};

}  // namespace varfolomeev_g_matrix_max_rows_vals_seq