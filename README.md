[![Build Status](https://travis-ci.org/jeshuam/cppstring.svg?branch=master)](https://travis-ci.org/jeshuam/cppstring)

To run coverage on Windows:

$ jbuild -c debug --cc_compiler="cl.exe" build :string_test
$ OpenCppCoverage.exe -v --modules 'string_test' --sources 'cppstring' --excluded_sources '.jbuild' --excluded_sources 'third_party' --excluded_sources '*_test.cc' -- ./bin/debug/string_test.exe
