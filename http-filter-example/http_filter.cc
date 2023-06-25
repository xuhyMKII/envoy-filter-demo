#include <string>

#include "http_filter.h"

#include "envoy/server/filter_config.h"

// 定义了两个类：HttpSampleDecoderFilterConfig和HttpSampleDecoderFilter，它们分别代表过滤器的配置和过滤器本身。


namespace Envoy {
namespace Http {

// 构造函数：接收一个protobuf配置对象，从中提取出关键的配置信息（key_和val_）。
HttpSampleDecoderFilterConfig::HttpSampleDecoderFilterConfig(const sample::Decoder& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

// 接收一个HttpSampleDecoderFilterConfig对象的共享指针，用于后续的过滤器操作。
HttpSampleDecoderFilter::HttpSampleDecoderFilter(HttpSampleDecoderFilterConfigSharedPtr config)
    : config_(config) {}

HttpSampleDecoderFilter::~HttpSampleDecoderFilter() {}

void HttpSampleDecoderFilter::onDestroy() {}

const LowerCaseString HttpSampleDecoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string HttpSampleDecoderFilter::headerValue() const {
  return config_->val();
}

// 这是过滤器处理HTTP请求头的方法。在这个方法中，过滤器向请求头中添加了一个新的头部字段，字段的键和值由配置对象提供。
FilterHeadersStatus HttpSampleDecoderFilter::decodeHeaders(RequestHeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}


// 这是过滤器处理HTTP请求体的方法。在这个例子中，这个方法并没有做任何处理，
// 只是简单地返回了FilterDataStatus::Continue，表示过滤器链应该继续处理请求体。
FilterDataStatus HttpSampleDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

// 这个方法设置了过滤器的回调对象，这个对象提供了一些用于操作HTTP请求的方法。
void HttpSampleDecoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy
