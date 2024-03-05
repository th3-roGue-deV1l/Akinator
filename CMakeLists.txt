# CMakeList.txt : CMake project for Techhi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Techhi")

find_package(TBB REQUIRED)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Add source to this project's executable.
add_executable (Techhi "./src/Techhi.cpp" "./src/Techhi.h" "./src/BinaryDecisionTree.h" "./src/utils.h" "./src/utils.cpp" "./src/CART.h" "./src/CART.cpp")

target_link_libraries(Techhi TBB::tbb)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Techhi PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
