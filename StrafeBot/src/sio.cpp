#include "sio.h"
#include <iostream>
#include <thread>

SioClient::SioClient() {
    _socket_client.set_open_listener(std::bind(&SioClient::on_connected, this));
    _socket_client.set_close_listener(std::bind(&SioClient::on_close, this, std::placeholders::_1));
    _socket_client.set_fail_listener(std::bind(&SioClient::on_fail, this));

    _socket_client.socket()->on("command_completed", sio::socket::event_listener_aux(
        [&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list& ack_resp) {
            on_command_completed(data);
        }
    ));
}

void SioClient::connect(const std::string& uri) {
    _socket_client.connect(uri);
}

void SioClient::send_command() {
    std::cout << "Sending command..." << std::endl;

    sio::message::ptr msg = sio::object_message::create();
    msg->get_map()["command"] = sio::string_message::create("test command");
    _socket_client.socket()->emit("send_command_to_pc2", msg);

    //std::unique_lock<std::mutex> lock(_mtx);
    //_cv.wait(lock, [this] { return _command_confirmed; });
}

void SioClient::on_connected() {
    std::cout << "PC1 connected to server." << std::endl;

    sio::message::ptr msg = sio::object_message::create();
    msg->get_map()["pc_id"] = sio::string_message::create("pc1");
    _socket_client.socket()->emit("register", msg);
}

void SioClient::on_command_completed(const sio::message::ptr& data) {
    std::cout << "Command completed by PC2: " << data->get_string() << std::endl;

    std::lock_guard<std::mutex> lock(_mtx);
    _command_confirmed = true;
    _cv.notify_one();
}

void SioClient::on_close(sio::client::close_reason const& reason) {
    std::cout << "Connection closed." << std::endl;
}

void SioClient::on_fail() {
    std::cout << "Connection failed." << std::endl;
}