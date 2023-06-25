#include "test/integration/http_integration.h"

namespace Envoy {
class HttpFilterSampleIntegrationTest : public HttpIntegrationTest,
                                        public testing::TestWithParam<Network::Address::IpVersion> {
public:
  HttpFilterSampleIntegrationTest()
      : HttpIntegrationTest(Http::CodecClient::Type::HTTP1, GetParam()) {}
  /**
   * Initializer for an individual integration test.
   */
  // SetUp：这个方法在每个测试开始之前被调用，它调用initialize方法来初始化测试环境。
  void SetUp() override { initialize(); }

// initialize：这个方法配置了HTTP过滤器，并调用父类的initialize方法来初始化HTTP集成测试。
  void initialize() override {
    config_helper_.prependFilter(
        "{ name: sample, typed_config: { \"@type\": type.googleapis.com/sample.Decoder, key: via, "
        "val: sample-filter } }");
    HttpIntegrationTest::initialize();
  }
};


// 在Google Test框架中，参数化测试的参数是通过测试套件类的构造函数或SetUp方法传入的。
// HttpFilterSampleIntegrationTest类的构造函数接受一个Network::Address::IpVersion类型的参数，
// 这个参数就是通过INSTANTIATE_TEST_SUITE_P宏生成的测试实例的参数。


// 当使用INSTANTIATE_TEST_SUITE_P宏实例化参数化测试时，Google Test会为每个参数生成一个测试实例，并调用测试套件类的构造函数或SetUp方法，将参数传入。
INSTANTIATE_TEST_SUITE_P(IpVersions, HttpFilterSampleIntegrationTest,
                         testing::ValuesIn(TestEnvironment::getIpVersionsForTest()));

// TEST_P：这是一个参数化测试，它测试了HTTP过滤器的功能。这个测试首先创建了一个HTTP请求，然后发送这个请求，并等待响应。最后，它检查响应中的"via"头部是否被过滤器正确地修改为"sample-filter"。

// 在TEST_P宏定义的测试中，你可以通过GetParam方法获取这个参数。
// HttpFilterSampleIntegrationTest类有一个名为ipVersion的成员变量，
// 这个变量在类的构造函数中被初始化为GetParam()，
// 所以在TEST_P宏定义的测试中，通过ipVersion变量获取测试实例的参数。
TEST_P(HttpFilterSampleIntegrationTest, Test1) {
  Http::TestRequestHeaderMapImpl headers{
      {":method", "GET"}, {":path", "/"}, {":authority", "host"}};
  Http::TestRequestHeaderMapImpl response_headers{
      {":status", "200"}};

  IntegrationCodecClientPtr codec_client;
  FakeHttpConnectionPtr fake_upstream_connection;
  FakeStreamPtr request_stream;

  codec_client = makeHttpConnection(lookupPort("http"));
  auto response = codec_client->makeHeaderOnlyRequest(headers);
  ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection));
  ASSERT_TRUE(fake_upstream_connection->waitForNewStream(*dispatcher_, request_stream));
  ASSERT_TRUE(request_stream->waitForEndStream(*dispatcher_));
  request_stream->encodeHeaders(response_headers, true);
  ASSERT_TRUE(response->waitForEndStream());

  EXPECT_EQ(
      "sample-filter",
      request_stream->headers().get(Http::LowerCaseString("via"))[0]->value().getStringView());

  codec_client->close();
}
} // namespace Envoy
