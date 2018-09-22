/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/contrib/lite/core/api/error_reporter.h"

#include <cstdio>

#include <gtest/gtest.h>

namespace tflite {

class MockErrorReporter : public ErrorReporter {
 public:
  int Report(const char* format, va_list args) override {
    vsnprintf(buffer_, kBufferSize, format, args);
    return 0;
  }
  char* GetBuffer() { return buffer_; }

 private:
  static constexpr int kBufferSize = 256;
  char buffer_[kBufferSize];
};

TEST(ErrorReporter, TestReport) {
  MockErrorReporter mock_reporter;
  ErrorReporter* reporter = &mock_reporter;
  reporter->Report("Error: %d", 23);
  EXPECT_EQ(0, strcmp(mock_reporter.GetBuffer(), "Error: 23"));
}

}  // namespace tflite

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
