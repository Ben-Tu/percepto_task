
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <chrono>
#include "mqtt/client.h"
#include "mqtt/async_client.h"
#include <thread>

#include "client_tools.h"

const std::string SERVER_ADDRESS("3.126.83.231:1883");
const std::string USERNAME("client1");

int main(int argc, char* argv[])
{

	std::cout <<"\nWhen the client runing,for quit press Q<Enter> to quit" <<'\n'<< std::endl;

	std::string password;
	std::string client_id;

	std::cout << "Please enter server password: ";
	std::cin >> password;

	std::cout << "Please enter your hostname without space: ";
	std::cin >> client_id;


	mqtt::async_client cli(SERVER_ADDRESS, client_id);

	mqtt::connect_options connOpts;
	connOpts.set_clean_session(false);
	connOpts.set_password(password);
	connOpts.set_user_name(USERNAME);

	// Install the callback before connecting.
	callback cb(cli, connOpts,client_id);
	cli.set_callback(cb);


	// Start the connection.
	// When completed, the callback will subscribe to topic.

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		cli.connect(connOpts, nullptr, cb);
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << exc << std::endl;
		return 1;
	}

	// Just block till user tells us to quit.
	while (std::tolower(std::cin.get()) != 'q')
		;

	// Disconnect
	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		cli.disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc << std::endl;
		return 1;
	}

 	return 0;
}

