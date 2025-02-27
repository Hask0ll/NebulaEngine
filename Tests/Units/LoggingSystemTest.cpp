//
// Created by dobar on 2/27/2025.
//

#include "Nebula.h"
#include <gtest/gtest.h>
#include <spdlog/sinks/base_sink.h>
#include <vector>
#include <mutex>

// Custom sink that captures log messages for testing
template<typename Mutex>
class TestSink : public spdlog::sinks::base_sink<Mutex> {
public:
    struct LogMessage {
        spdlog::level::level_enum level;
        std::string message;
    };

    std::vector<LogMessage> messages;

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);
        messages.push_back({
            msg.level,
            fmt::to_string(formatted)
        });
    }

    void flush_() override {}
};

using TestSinkMt = TestSink<std::mutex>;

class LogTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test sinks
        m_CoreSink = std::make_shared<TestSinkMt>();
        m_ClientSink = std::make_shared<TestSinkMt>();

        // Initialize the logger with our test sinks
        Nebula::Log::Init();

        // Replace the default sinks with our test sinks
        Nebula::Log::GetCoreLogger()->sinks().clear();
        Nebula::Log::GetCoreLogger()->sinks().push_back(m_CoreSink);

        Nebula::Log::GetClientLogger()->sinks().clear();
        Nebula::Log::GetClientLogger()->sinks().push_back(m_ClientSink);
    }

    void TearDown() override {
        Nebula::Log::Shutdown();
    }

    std::shared_ptr<TestSinkMt> m_CoreSink;
    std::shared_ptr<TestSinkMt> m_ClientSink;
};

TEST_F(LogTest, CoreLogging) {
    // Test core logging macros
    NB_CORE_TRACE("Core trace message");
    NB_CORE_INFO("Core info message");
    NB_CORE_WARN("Core warning message");
    NB_CORE_ERROR("Core error message");
    NB_CORE_CRITICAL("Core critical message");

    // Verify messages were logged at the correct levels
    ASSERT_EQ(m_CoreSink->messages.size(), 5);
    EXPECT_EQ(m_CoreSink->messages[0].level, spdlog::level::trace);
    EXPECT_EQ(m_CoreSink->messages[1].level, spdlog::level::info);
    EXPECT_EQ(m_CoreSink->messages[2].level, spdlog::level::warn);
    EXPECT_EQ(m_CoreSink->messages[3].level, spdlog::level::err);
    EXPECT_EQ(m_CoreSink->messages[4].level, spdlog::level::critical);

    // Check message content (implementation-specific)
    EXPECT_TRUE(m_CoreSink->messages[0].message.find("Core trace message") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[1].message.find("Core info message") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[2].message.find("Core warning message") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[3].message.find("Core error message") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[4].message.find("Core critical message") != std::string::npos);
}

TEST_F(LogTest, ClientLogging) {
    // Test client logging macros
    NB_CLIENT_TRACE("Client trace message");
    NB_CLIENT_INFO("Client info message");
    NB_CLIENT_WARN("Client warning message");
    NB_CLIENT_ERROR("Client error message");
    NB_CLIENT_CRITICAL("Client critical message");

    // Verify messages were logged at the correct levels
    ASSERT_EQ(m_ClientSink->messages.size(), 5);
    EXPECT_EQ(m_ClientSink->messages[0].level, spdlog::level::trace);
    EXPECT_EQ(m_ClientSink->messages[1].level, spdlog::level::info);
    EXPECT_EQ(m_ClientSink->messages[2].level, spdlog::level::warn);
    EXPECT_EQ(m_ClientSink->messages[3].level, spdlog::level::err);
    EXPECT_EQ(m_ClientSink->messages[4].level, spdlog::level::critical);

    // Check message content (implementation-specific)
    EXPECT_TRUE(m_ClientSink->messages[0].message.find("Client trace message") != std::string::npos);
    EXPECT_TRUE(m_ClientSink->messages[1].message.find("Client info message") != std::string::npos);
    EXPECT_TRUE(m_ClientSink->messages[2].message.find("Client warning message") != std::string::npos);
    EXPECT_TRUE(m_ClientSink->messages[3].message.find("Client error message") != std::string::npos);
    EXPECT_TRUE(m_ClientSink->messages[4].message.find("Client critical message") != std::string::npos);
}

TEST_F(LogTest, LogFormatting) {
    // Test format string parameters
    NB_CORE_INFO("Value: {0}", 42);
    NB_CORE_INFO("Values: {0}, {1}, {2}", 1, "test", 3.14f);
    NB_CORE_INFO("Named: {value}", fmt::arg("value", "test"));

    ASSERT_GE(m_CoreSink->messages.size(), 3);
    EXPECT_TRUE(m_CoreSink->messages[0].message.find("Value: 42") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[1].message.find("Values: 1, test, 3.14") != std::string::npos);
    EXPECT_TRUE(m_CoreSink->messages[2].message.find("Named: test") != std::string::npos);
}

TEST_F(LogTest, LoggerInstances) {
    // Verify that we have distinct loggers
    EXPECT_NE(Nebula::Log::GetCoreLogger(), Nebula::Log::GetClientLogger());

    // Verify logger names
    EXPECT_EQ(Nebula::Log::GetCoreLogger()->name(), "NEBULA");
    EXPECT_EQ(Nebula::Log::GetClientLogger()->name(), "APP");
}