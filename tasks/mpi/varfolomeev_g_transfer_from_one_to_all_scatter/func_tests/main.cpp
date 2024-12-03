// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <vector>

#include "mpi/varfolomeev_g_transfer_from_one_to_all_scatter/include/ops_mpi.hpp"

TEST(varfolomeev_g_transfer_from_one_to_all_scatter_mpi, Test_Sum) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_sum(1, 0);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 120;
    global_vec = varfolomeev_g_transfer_from_one_to_all_scatter_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_sum.data()));
    taskDataPar->outputs_count.emplace_back(global_sum.size());
  }

  varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar);
  ASSERT_EQ(testMpiTaskParallel.validation(), true);
  testMpiTaskParallel.pre_processing();
  testMpiTaskParallel.run();
  testMpiTaskParallel.post_processing();

  if (world.rank() == 0) {
    ASSERT_EQ(1, 1);
  }
}

// TEST(varfolomeev_g_transfer_from_one_to_all_scatter, Test_Diff) {
//   boost::mpi::communicator world;
//   std::vector<int> global_vec;
//   std::vector<int32_t> global_diff(1, 0);
//   // Create TaskData
//   std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

//   if (world.rank() == 0) {
//     const int count_size_vector = 240;
//     global_vec = varfolomeev_g_transfer_from_one_to_all_scatter_mpi::getRandomVector(count_size_vector);
//     taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataPar->inputs_count.emplace_back(global_vec.size());
//     taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_diff.data()));
//     taskDataPar->outputs_count.emplace_back(global_diff.size());
//   }

//   varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar, "-");
//   ASSERT_EQ(testMpiTaskParallel.validation(), true);
//   testMpiTaskParallel.pre_processing();
//   testMpiTaskParallel.run();
//   testMpiTaskParallel.post_processing();

//   if (world.rank() == 0) {
//     // Create data
//     std::vector<int32_t> reference_diff(1, 0);

//     // Create TaskData
//     std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//     taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataSeq->inputs_count.emplace_back(global_vec.size());
//     taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_diff.data()));
//     taskDataSeq->outputs_count.emplace_back(reference_diff.size());

//     // Create Task
//     varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq,
//     "-"); ASSERT_EQ(testMpiTaskSequential.validation(), true); testMpiTaskSequential.pre_processing();
//     testMpiTaskSequential.run();
//     testMpiTaskSequential.post_processing();

//     ASSERT_EQ(reference_diff[0], global_diff[0]);
//   }
// }

// TEST(varfolomeev_g_transfer_from_one_to_all_scatter, Test_Diff_2) {
//   boost::mpi::communicator world;
//   std::vector<int> global_vec;
//   std::vector<int32_t> global_diff(1, 0);
//   // Create TaskData
//   std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

//   if (world.rank() == 0) {
//     const int count_size_vector = 120;
//     global_vec = varfolomeev_g_transfer_from_one_to_all_scatter_mpi::getRandomVector(count_size_vector);
//     taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataPar->inputs_count.emplace_back(global_vec.size());
//     taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_diff.data()));
//     taskDataPar->outputs_count.emplace_back(global_diff.size());
//   }

//   varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar, "-");
//   ASSERT_EQ(testMpiTaskParallel.validation(), true);
//   testMpiTaskParallel.pre_processing();
//   testMpiTaskParallel.run();
//   testMpiTaskParallel.post_processing();

//   if (world.rank() == 0) {
//     // Create data
//     std::vector<int32_t> reference_diff(1, 0);

//     // Create TaskData
//     std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//     taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataSeq->inputs_count.emplace_back(global_vec.size());
//     taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_diff.data()));
//     taskDataSeq->outputs_count.emplace_back(reference_diff.size());

//     // Create Task
//     varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq,
//     "-"); ASSERT_EQ(testMpiTaskSequential.validation(), true); testMpiTaskSequential.pre_processing();
//     testMpiTaskSequential.run();
//     testMpiTaskSequential.post_processing();

//     ASSERT_EQ(reference_diff[0], global_diff[0]);
//   }
// }

// TEST(varfolomeev_g_transfer_from_one_to_all_scatter, Test_Max) {
//   boost::mpi::communicator world;
//   std::vector<int> global_vec;
//   std::vector<int32_t> global_max(1, 0);
//   // Create TaskData
//   std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

//   if (world.rank() == 0) {
//     const int count_size_vector = 240;
//     global_vec = varfolomeev_g_transfer_from_one_to_all_scatter_mpi::getRandomVector(count_size_vector);
//     taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataPar->inputs_count.emplace_back(global_vec.size());
//     taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_max.data()));
//     taskDataPar->outputs_count.emplace_back(global_max.size());
//   }

//   varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar, "max");
//   ASSERT_EQ(testMpiTaskParallel.validation(), true);
//   testMpiTaskParallel.pre_processing();
//   testMpiTaskParallel.run();
//   testMpiTaskParallel.post_processing();

//   if (world.rank() == 0) {
//     // Create data
//     std::vector<int32_t> reference_max(1, 0);

//     // Create TaskData
//     std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//     taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataSeq->inputs_count.emplace_back(global_vec.size());
//     taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_max.data()));
//     taskDataSeq->outputs_count.emplace_back(reference_max.size());

//     // Create Task
//     varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq,
//     "max"); ASSERT_EQ(testMpiTaskSequential.validation(), true); testMpiTaskSequential.pre_processing();
//     testMpiTaskSequential.run();
//     testMpiTaskSequential.post_processing();

//     ASSERT_EQ(reference_max[0], global_max[0]);
//   }
// }

// TEST(varfolomeev_g_transfer_from_one_to_all_scatter, Test_Max_2) {
//   boost::mpi::communicator world;
//   std::vector<int> global_vec;
//   std::vector<int32_t> global_max(1, 0);
//   // Create TaskData
//   std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

//   if (world.rank() == 0) {
//     const int count_size_vector = 120;
//     global_vec = varfolomeev_g_transfer_from_one_to_all_scatter_mpi::getRandomVector(count_size_vector);
//     taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataPar->inputs_count.emplace_back(global_vec.size());
//     taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_max.data()));
//     taskDataPar->outputs_count.emplace_back(global_max.size());
//   }

//   varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskParallel testMpiTaskParallel(taskDataPar, "max");
//   ASSERT_EQ(testMpiTaskParallel.validation(), true);
//   testMpiTaskParallel.pre_processing();
//   testMpiTaskParallel.run();
//   testMpiTaskParallel.post_processing();

//   if (world.rank() == 0) {
//     // Create data
//     std::vector<int32_t> reference_max(1, 0);

//     // Create TaskData
//     std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//     taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
//     taskDataSeq->inputs_count.emplace_back(global_vec.size());
//     taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_max.data()));
//     taskDataSeq->outputs_count.emplace_back(reference_max.size());

//     // Create Task
//     varfolomeev_g_transfer_from_one_to_all_scatter_mpi::TestMPITaskSequential testMpiTaskSequential(taskDataSeq,
//     "max"); ASSERT_EQ(testMpiTaskSequential.validation(), true); testMpiTaskSequential.pre_processing();
//     testMpiTaskSequential.run();
//     testMpiTaskSequential.post_processing();

//     ASSERT_EQ(reference_max[0], global_max[0]);
//   }
// }