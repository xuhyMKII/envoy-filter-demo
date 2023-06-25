-- 这个BUILD文件是Bazel构建系统的一部分，它定义了如何构建和测试这个项目中的代码。


load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)
load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

package(default_visibility = ["//visibility:public"])

-- 这个目标构建一个名为envoy的二进制文件。这个二进制文件依赖于http_filter_config库和Envoy的主入口库（envoy_main_entry_lib）。
envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":http_filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

-- 这个目标生成这个项目中的API协议缓冲区代码。
-- api_proto_package()是一个Bazel的宏（macro），它用于生成Protocol Buffers（protobuf）相关的代码。这个宏是在Envoy项目中定义的，它封装了一些Bazel规则，用于编译protobuf文件并生成C++代码
api_proto_package()

-- envoy_cc_library：这个目标构建两个库，http_filter_lib和http_filter_config。
-- http_filter_lib库包含http_filter.cc源文件，它依赖于协议缓冲区代码和Envoy的通用HTTP过滤器库。
-- http_filter_config库包含http_filter_config.cc源文件，它依赖于http_filter_lib库和Envoy的过滤器配置接口。
envoy_cc_library(
    name = "http_filter_lib",
    srcs = ["http_filter.cc"],
    hdrs = ["http_filter.h"],
    repository = "@envoy",
    deps = [
        ":pkg_cc_proto",
        "@envoy//source/extensions/filters/http/common:pass_through_filter_lib",
    ],
)

envoy_cc_library(
    name = "http_filter_config",
    srcs = ["http_filter_config.cc"],
    repository = "@envoy",
    deps = [
        ":http_filter_lib",
        "@envoy//envoy/server:filter_config_interface",
    ],
)

-- 这个目标构建一个名为http_filter_integration_test的测试，这个测试依赖于http_filter_config库和Envoy的HTTP集成测试库。
envoy_cc_test(
    name = "http_filter_integration_test",
    srcs = ["http_filter_integration_test.cc"],
    repository = "@envoy",
    deps = [
        ":http_filter_config",
        "@envoy//test/integration:http_integration_lib",
    ],
)
