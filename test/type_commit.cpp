//          Copyright Carl Pearson 2020 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//    https://www.boost.org/LICENSE_1_0.txt)

#include <mpi.h>

#include "../include/env.hpp"

#include "../support/type.hpp"

int main(int argc, char **argv) {
  environment::noTempi = false;
  MPI_Init(&argc, &argv);

  int rank = 0, size = 1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (1 != size) {
    std::cerr << "ERROR: requires exactly 1 rank\n";
    exit(1);
  }

  {
    std::cerr << "TEST: make_2d_hv_by_rows\n";
    MPI_Datatype ty = make_2d_hv_by_rows(13, 5, 16, 3, 53);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: make_2d_hv_by_cols\n";
    MPI_Datatype ty = make_2d_hv_by_cols(13, 5, 16, 3, 53);
    MPI_Type_commit(&ty);
  }
  // MPI_Finalize();
  // exit(0);

  Dim3 copyExt(100,13,47);
  Dim3 allocExt(256,512,1024);

  {
    std::cerr << "TEST: MPI_Type_create_subarray\n";
    MPI_Datatype ty = make_subarray(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: MPI_Type_create_subarray\n";
    MPI_Datatype ty = make_off_subarray(copyExt, allocExt, Dim3(4, 4, 4));
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: make_subarray_v\n";
    MPI_Datatype ty = make_subarray_v(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: make_byte_v_hv\n";
    MPI_Datatype ty = make_byte_v_hv(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: make_float_v_hv\n";
    MPI_Datatype ty = make_float_v_hv(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: v1 hv hv\n";
    MPI_Datatype ty = make_byte_v1_hv_hv(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: make_byte_vn_hv_hv\n";
    MPI_Datatype ty = make_byte_vn_hv_hv(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    Dim3 copyExt(100,100,1);
    Dim3 allocExt(100,100,100);
    std::cerr << "TEST: v1 hv hv\n";
    MPI_Datatype ty = make_byte_v1_hv_hv(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: hindexed_block\n";
    MPI_Datatype ty = make_hib(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  {
    std::cerr << "TEST: hi\n";
    MPI_Datatype ty = make_hi(copyExt, allocExt);
    MPI_Type_commit(&ty);
  }

  MPI_Finalize();
  return 0;
}
