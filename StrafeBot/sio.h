#pragma once
#include <sio_client.h>
#include <mutex>
#include <condition_variable>
using namespace std;

class SioClient {
public:
    SioClient();
    void connect(const string& uri);
    void send_command(const bool on_pos);

private:
    sio::client _socket_client;
    mutex _mtx;
    condition_variable _cv;
    bool _connected;

    void on_connected();
    void on_command_completed(const sio::message::ptr& data);
    void on_close(sio::client::close_reason const& reason);
    void on_fail();
};