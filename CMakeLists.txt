PROJECT(ls CXX)
SET(CMAKE_CXX_COMPILER)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
SET (LSSRC
  domain.cc
  random.cc
  srandom.cc
  solis.cc
  simplex.cc
  cmaeshan.cc
  origcmaes.cc
  problemcec2014.cc
  cec2014_func.cpp
  problem.cc
  #example.cc
  aux.cc
  solution.cc
  metaheuristic.cc
  main.cc
)

ADD_LIBRARY(localsearch SHARED ${LSSRC})
TARGET_LINK_LIBRARIES(localsearch)

#ADD_EXECUTABLE(example_ls example.cc)
#TARGET_LINK_LIBRARIES(example_ls localsearch)

ADD_EXECUTABLE(main main.cc)
TARGET_LINK_LIBRARIES(main localsearch)
