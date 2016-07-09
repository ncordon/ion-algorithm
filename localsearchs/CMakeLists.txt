PROJECT(ls CXX)
SET(CMAKE_CXX_COMPILER)
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
  example.cc
)

ADD_LIBRARY(localsearch SHARED ${LSSRC})
TARGET_LINK_LIBRARIES(localsearch)

ADD_EXECUTABLE(example_ls example.cc)
TARGET_LINK_LIBRARIES(example_ls localsearch)
