
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/client.h"
#include "mqtt/async_client.h"
#include "converter.h"


const std::string SERVER_ADDRESS("3.126.83.231:1883");
const std::string CLIENT_ID("Ben");
const std::string USERNAME("client1");
const std::string TOPIC("input_data");

const std::string TOPIC_PUB("hostname");
const std::string PASSWORD("0G*XXzzZu_ICwqBf~BQWkwsl");

const int	QOS = 1;
const int	N_RETRY_ATTEMPTS = 5;

//class tools;


//class vali{
//
//	tools* t;
//public:
//
//
//	bool is_hex_notation(std::string const& s)
//	{
//	  return s.compare(0, 2, "0x") == 0
//	      && s.size() > 2
//		  && s.size() == 10
//	      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
//	}
//
//	bool is_four_byte_number(std::string const& s){
//		int number = t->convert_hex_string_to_int(s);
//		if (sizeof(number) == 4)
//			std::cout << " for token:"<< number << std::endl;
//			return 1;
//		return 0;
//	}
//
//	bool run_all_validation_functions(std::string const& s){
//		if (is_hex_notation(s) && is_four_byte_number(s))
//			return 1;
//	}
//
//};


class action_listener : public virtual mqtt::iaction_listener
{
	std::string name_;

	void on_failure(const mqtt::token& tok) override {
		std::cout << name_ << " failure";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		std::cout << std::endl;
	}

	void on_success(const mqtt::token& tok) override {
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
	}

public:
	action_listener(const std::string& name) : name_(name) {}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener

{
	// Counter for the number of connection retries
	int nretry_;
	// The MQTT client
	mqtt::async_client& cli_;
	// Options to use if we need to reconnect
	mqtt::connect_options& connOpts_;
	// An action listener to display the result of actions.
	action_listener subListener_;
	//tools t;
	// This deomonstrates manually reconnecting to the broker by calling
	// connect() again. This is a possibility for an application that keeps
	// a copy of it's original connect_options, or if the app wants to
	// reconnect with different options.
	// Another way this can be done manually, if using the same options, is
	// to just call the async_client::reconnect() method.
	void reconnect() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		try {
			cli_.connect(connOpts_, nullptr, *this);
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			exit(1);
		}
	}

	// Re-connection failure
	void on_failure(const mqtt::token& tok) override {
		std::cout << "Connection attempt failed" << std::endl;
		if (++nretry_ > N_RETRY_ATTEMPTS)
			exit(1);
		reconnect();
	}

	// (Re)connection success
	// Either this or connected() can be used for callbacks.
	void on_success(const mqtt::token& tok) override {}

	// (Re)connection success
	void connected(const std::string& cause) override {
		std::cout << "\nConnection success" << std::endl;
		std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
			<< "\tfor client " << CLIENT_ID
			<< " using QoS" << QOS << "\n"
			<< "\nPress Q<Enter> to quit\n" << std::endl;

		cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "Reconnecting..." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override {
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

		//t.converter(msg->to_string());

	}

	//validate msg

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
				: nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
};


/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// A subscriber often wants the server to remember its messages when its
	// disconnected. In that case, it needs a unique ClientID and a
	// non-clean session.



	std::string s = "0xa4172bd2";
	converter c;
	std::cout << c.hex_converter(s) << std::endl;

	return 1;
//	c.delete()
//	std::cout << SERVER_ADDRESS << std::endl;
//	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);
//
//	mqtt::connect_options connOpts;
//	connOpts.set_clean_session(false);
//	connOpts.set_password(PASSWORD);
//	connOpts.set_user_name(USERNAME);
//	// Install the callback(s) before connecting.
//	callback cb(cli, connOpts);
//	cli.set_callback(cb);
//
//	// Start the connection.
//	// When completed, the callback will subscribe to topic.
//
//	try {
//		std::cout << "Connecting to the MQTT server..." << std::flush;
//		cli.connect(connOpts, nullptr, cb);
//	}
//	catch (const mqtt::exception& exc) {
//		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
//			<< SERVER_ADDRESS << "'" << exc << std::endl;
//		return 1;
//	}
//
//	// Just block till user tells us to quit.
//
//	while (std::tolower(std::cin.get()) != 'q')
//		;
//
//	// Disconnect
//
//	try {
//		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
//		cli.disconnect()->wait();
//		std::cout << "OK" << std::endl;
//	}
//	catch (const mqtt::exception& exc) {
//		std::cerr << exc << std::endl;
//		return 1;
//	}
//
// 	return 0;
}

