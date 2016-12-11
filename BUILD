import json

build = dict(
  string = dict(
    type = 'c++/library',
    srcs = [
      'format.cc',
      'util.cc',
    ],

    hdrs = [
      'format.h',
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
