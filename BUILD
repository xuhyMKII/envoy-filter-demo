package(default_visibility=["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)

# 目标名为envoy，它是一个二进制目标，用于构建Envoy的可执行文件。
# 这个目标依赖于echo2_config库和envoy_main_entry_lib库。

envoy_cc_binary(
    name="envoy",
    repository="@envoy",
    deps=[
        ":echo2_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)


# 目标名为echo2_lib，它是一个库目标，用于构建echo2.cc和echo2.h文件。
# 这个库依赖于Envoy的一些库，如buffer_interface、connection_interface、
# filter_interface、assert_lib和logger_lib。

envoy_cc_library(
    name="echo2_lib",
    srcs=["echo2.cc"],
    hdrs=["echo2.h"],
    repository="@envoy",
    deps=[
        "@envoy//envoy/buffer:buffer_interface",
        "@envoy//envoy/network:connection_interface",
        "@envoy//envoy/network:filter_interface",
        "@envoy//source/common/common:assert_lib",
        "@envoy//source/common/common:logger_lib",
    ],
)


# 目标名为echo2_config，它是一个库目标，用于构建echo2_config.cc文件。
# 这个库依赖于echo2_lib库和Envoy的一些库，
# 如filter_interface、registry和filter_config_interface。

envoy_cc_library(
    name="echo2_config",
    srcs=["echo2_config.cc"],
    repository="@envoy",
    deps=[
        ":echo2_lib",
        "@envoy//envoy/network:filter_interface",
        "@envoy//envoy/registry:registry",
        "@envoy//envoy/server:filter_config_interface",
    ],
)

# 目标名为echo2_integration_test，
# 它是一个测试目标，用于运行echo2_integration_test.cc文件中的测试。
# 这个测试依赖于echo2_config库和integration_lib库，
# 它还使用了echo2_server.yaml文件作为测试数据。

envoy_cc_test(
    name="echo2_integration_test",
    srcs=["echo2_integration_test.cc"],
    data=["echo2_server.yaml"],
    repository="@envoy",
    deps=[
        ":echo2_config",
        "@envoy//test/integration:integration_lib"
    ],
)

# 目标名为envoy_binary_test，它是一个Shell测试目标，
# 用于运行envoy_binary_test.sh脚本。这个测试依赖于envoy二进制目标。
sh_test(
    name="envoy_binary_test",
    srcs=["envoy_binary_test.sh"],
    data=[":envoy"],
)


# 在这个BUILD文件中，envoy_cc_binary目标名为envoy的确会生成一个可执行文件。
# 这个可执行文件是Envoy的二进制文件，
# 它包含了Envoy的主程序以及所有链接到主程序的库，包括echo2_config库。

# 其他的envoy_cc_library目标（如echo2_lib和echo2_config）会生成库文件，
# 这些库文件会被链接到envoy可执行文件中。这些库文件不是独立的可执行文件，
# 它们包含的是可以被其他代码复用的函数和类。

# envoy_cc_test和sh_test目标则是用于运行测试的。
# 它们不会生成可执行文件，而是会运行测试代码，并报告测试结果。
