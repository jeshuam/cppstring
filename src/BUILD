import json

build = dict(
  string = dict(
    type = 'c++/library',
    srcs = [
      'constants.cc',
      'format.cc',
      'split.cc',
      'util.cc',
    ],

    hdrs = [
      'constants.h',
      'format.h',
      'split.h',
      'util.h',
    ],

    deps = [
      '//third_party/boost/any',
      '//third_party/gflags',
    ],
  ),

  string_test = dict(
    type = 'c++/test',
    srcs = [
      'format_test.cc',
      'split_test.cc',
      'util_test.cc',
    ],

    deps = [
      ':string',
      '//third_party/googletest:main',
    ],
  ),

  doc = dict(type = 'doxygen'),
)

print(json.dumps(build))
