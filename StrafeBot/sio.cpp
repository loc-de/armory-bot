#include "sio.h"
#include <iostream>
#include <thread>
using namespace std;

SioClient::SioClient() : 
    _connected(false)
{
    _socket_client.set_open_listener(bind(&SioClient::on_connected, this));
    _socket_client.set_close_listener(bind(&SioClient::on_close, this, placeholders::_1));
    _socket_client.set_fail_listener(bind(&SioClient::on_fail, this));

    _socket_client.socket()->on("command_completed", sio::socket::event_listener_aux(
        [&](string const& name, sio::message::ptr const& data, bool isAck, sio::message::list& ack_resp) {
            on_command_completed(data);
        }
    ));
}

void SioClient::connect(const string& uri) {
    _socket_client.connect(uri);

    unique_lock<mutex> lock(_mtx);
    _cv.wait(lock, [this] { return _connected; });
}

void SioClient::send_command() {
    cout << "Sending command..." << endl;

    sio::message::ptr msg = sio::object_message::create();
    msg->get_map()["command"] = sio::string_message::create("test command");
    _socket_client.socket()->emit("send_command_to_pc2", msg);
}

void SioClient::on_connected() {
    cout << "PC1 connected to server." << endl;

    sio::message::ptr msg = sio::object_message::create();
    msg->get_map()["pc_id"] = sio::string_message::create("pc1");
    _socket_client.socket()->emit("register", msg);

    lock_guard<mutex> lock(_mtx);
    _connected = true;
    _cv.notify_one();
}

void SioClient::on_command_completed(const sio::message::ptr& data) {
    cout << "Command completed by PC2: " << data->get_string() << endl;
}

void SioClient::on_close(sio::client::close_reason const& reason) {
    cout << "Connection closed." << endl;
}

void SioClient::on_fail() {
    cout << "Connection failed." << endl;
}