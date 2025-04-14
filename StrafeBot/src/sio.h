#pragma once
#include <sio_client.h>
#include <mutex>
#include <condition_variable>

class SioClient {
public:
    SioClient();
    void connect(const std::string& uri);
    void send_command();

private:
    sio::client _socket_client;
    std::mutex _mtx;
    std::condition_variable _cv;
    bool _command_confirmed = false;

    void on_connected();
    void on_command_completed(const sio::message::ptr& data);
    void on_close(sio::client::close_reason const& reason);
    void on_fail();
};