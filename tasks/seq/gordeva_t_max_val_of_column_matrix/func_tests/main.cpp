#include <gtest/gtest.h>

#include <climits>
#include <vector>

#include "seq/gordeva_t_max_val_of_column_matrix/include/ops_seq.hpp"

std::vector<int> rand_vec_seq_1(int size, int down, int upp) {
  std::vector<int> v(size);
  for (auto &number : v) number = down + (std::rand() % (upp - down + 1));
  return v;
}

std::vector<std::vector<int>> rand_matr_seq_1(int rows, int cols) {
  std::vector<std::vector<int>> matr(rows, std::vector<int>(cols));

  for (int i = 0; i < rows; ++i) {
    matr[i] = rand_vec_seq_1(cols, 0, 200);
  }
  for (int j = 0; j < cols; ++j) {
    int row_rand = std::rand() % rows;
    matr[row_rand][j] = 10;
  }
  return matr;
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Empty_Input) {
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_FALSE(testTaskSequential.validation());
}

TEST(gordeva_t_max_val_of_column_matrix_seq, IsEmptyOutput) {
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);

  taskDataSeq->inputs_count.push_back(5);
  taskDataSeq->inputs_count.push_back(5);
  taskDataSeq->inputs.push_back(reinterpret_cast<uint8_t *>(new int[25]));

  ASSERT_FALSE(testTaskSequential.validation());

  delete[] reinterpret_cast<int *>(taskDataSeq->inputs[0]);
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Max_val_of_500_columns_with_random) {
  const int rows = 500;
  const int cols = 500;

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);
  std::vector<std::vector<int>> matrix = rand_matr_seq_1(rows, cols);

  for (auto &i : matrix) taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(i.data()));
  taskDataSeq->inputs_count.emplace_back(rows);
  taskDataSeq->inputs_count.emplace_back(cols);

  std::vector<int> res(cols, 0);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());

  for (int j = 0; j < cols; j++) {
    int max_el = matrix[0][j];
    for (int i = 1; i < rows; i++) {
      if (matrix[i][j] > max_el) {
        max_el = matrix[i][j];
      }
    }
    ASSERT_EQ(res[j], max_el);
  }
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Max_val_of_500_1000_columns_with_random) {
  const int rows = 500;
  const int cols = 1000;

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);
  std::vector<std::vector<int>> matrix = rand_matr_seq_1(rows, cols);

  for (auto &i : matrix) taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(i.data()));
  taskDataSeq->inputs_count.emplace_back(rows);
  taskDataSeq->inputs_count.emplace_back(cols);

  std::vector<int> res(cols, 0);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());

  for (int j = 0; j < cols; j++) {
    int max_el = matrix[0][j];
    for (int i = 1; i < rows; i++) {
      if (matrix[i][j] > max_el) {
        max_el = matrix[i][j];
      }
    }
    ASSERT_EQ(res[j], max_el);
  }
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Max_val_of_1000_3000_columns_with_random) {
  const int rows = 1000;
  const int cols = 3000;

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);
  std::vector<std::vector<int>> matrix = rand_matr_seq_1(rows, cols);

  for (auto &i : matrix) taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(i.data()));
  taskDataSeq->inputs_count.emplace_back(rows);
  taskDataSeq->inputs_count.emplace_back(cols);

  std::vector<int> res(cols, 0);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_TRUE(testTaskSequential.pre_processing());
  ASSERT_TRUE(testTaskSequential.run());
  ASSERT_TRUE(testTaskSequential.post_processing());

  for (int j = 0; j < cols; j++) {
    int max_el = matrix[0][j];
    for (int i = 1; i < rows; i++) {
      if (matrix[i][j] > max_el) {
        max_el = matrix[i][j];
      }
    }
    ASSERT_EQ(res[j], max_el);
  }
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Incorrect_Input) {
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);

  taskDataSeq->inputs_count.push_back(10);
  taskDataSeq->inputs_count.push_back(0);
  taskDataSeq->inputs.push_back(reinterpret_cast<uint8_t *>(new int[10]));
  taskDataSeq->outputs_count.push_back(1);

  ASSERT_FALSE(testTaskSequential.validation());

  delete[] reinterpret_cast<int *>(taskDataSeq->inputs[0]);
}

TEST(gordeva_t_max_val_of_column_matrix_seq, Incorrect_val_of_output) {
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  gordeva_t_max_val_of_column_matrix_seq::TestTaskSequential testTaskSequential(taskDataSeq);

  taskDataSeq->inputs_count.push_back(10);
  taskDataSeq->inputs_count.push_back(15);
  taskDataSeq->inputs.push_back(reinterpret_cast<uint8_t *>(new int[150]));
  taskDataSeq->outputs_count.push_back(10);

  ASSERT_FALSE(testTaskSequential.validation());

  delete[] reinterpret_cast<int *>(taskDataSeq->inputs[0]);
}
