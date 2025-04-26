git clone https://github.com/google/googletest.git

cd googletest

cmake -B build -DCMAKE_INSTALL_PREFIX=/Users/karina/Documents/Projects/otus/cpp_basic/googletest/sources_webinar/project_prebuilt_gtest/googletest_prebuild

cmake --build build --target install

cd ..

cmake -B build -DGTEST_ROOT=/Users/karina/Documents/Projects/otus/cpp_basic/googletest/sources_webinar/project_prebuilt_gtest/googletest_prebuild

cmake --build build

# Windows:
#cmake -B build -DCMAKE_INSTALL_PREFIX=/Users/karina/Projects/webinar-gtest/project_prebuilt_gtest/googletest_prebuild -Dgtest_force_shared_crt=ON
