#include "test/integration/integration.h"
#include "test/integration/utility.h"

namespace Envoy {
class Echo2IntegrationTest : public BaseIntegrationTest,
                             public testing::TestWithParam<Network::Address::IpVersion> {


// 这个方法返回一个字符串，
// 这个字符串是Echo2过滤器的配置文件的内容。
// 这个配置文件定义了一个监听器，这个监听器使用Echo2过滤器来处理请求。

  std::string echoConfig() {
    return TestEnvironment::readFileToStringForTest(
        TestEnvironment::runfilesPath("echo2_server.yaml", "envoy_filter_example"));
  }

public:
  Echo2IntegrationTest() : BaseIntegrationTest(GetParam(), echoConfig()) {}
  /**
   * Initializer for an individual integration test.
   */

// 这两个方法分别在每个测试开始前和结束后被调用。
// SetUp方法调用BaseIntegrationTest::initialize来启动Envoy服务器和假的上游服务器。
// TearDown方法则关闭服务器和清理资源。


  void SetUp() override { BaseIntegrationTest::initialize(); }

  /**
   * Destructor for an individual integration test.
   */
  void TearDown() override {
    test_server_.reset();
    fake_upstreams_.clear();
  }
};



// 这个宏用于生成测试实例，每个实例都使用一个不同的IP版本（IPv4或IPv6）。

// INSTANTIATE_TEST_SUITE_P宏生成的参数在参数化测试中被使用。在你提供的echo2_integration_test.cc文件中，参数化测试是TEST_P(Echo2IntegrationTest, Echo)。

// INSTANTIATE_TEST_SUITE_P宏的第二个参数是测试套件的名称，第三个参数是测试类的名称，第四个参数是一个生成参数的表达式。在这个例子中，testing::ValuesIn(TestEnvironment::getIpVersionsForTest())生成了一个包含IPv4和IPv6两个值的参数集。

// 当测试运行时，TEST_P(Echo2IntegrationTest, Echo)会为参数集中的每个值生成一个测试实例。在这个例子中，它会生成两个测试实例：一个使用IPv4，一个使用IPv6。

// 在测试类中，你可以使用GetParam()方法来获取当前测试实例的参数值。在这个例子中，参数值被传递给了BaseIntegrationTest的构造函数，用于设置Envoy的网络环境。

// 总的来说，INSTANTIATE_TEST_SUITE_P宏生成的参数在参数化测试中被使用，用于为每个测试实例提供不同的测试环境或输入数据。


INSTANTIATE_TEST_SUITE_P(IpVersions, Echo2IntegrationTest,
                        testing::ValuesIn(TestEnvironment::getIpVersionsForTest()));


// 这是一个参数化测试，它测试了Echo2过滤器的基本行为。
// 这个测试创建一个到监听器的连接，发送一个"hello"消息，
// 然后检查返回的响应是否与发送的消息相同。


TEST_P(Echo2IntegrationTest, Echo) {
  std::string response;
  auto connection = createConnectionDriver(
      lookupPort("listener_0"), "hello",
      [&](Network::ClientConnection& conn, const Buffer::Instance& data) -> void {
        response.append(data.toString());
	conn.close(Network::ConnectionCloseType::FlushWrite);
      });

  connection->run();
  EXPECT_EQ("hello", response);
}
} // namespace Envoy
