
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <chrono>
#include "mqtt/client.h"
#include "mqtt/async_client.h"
#include "converter.h"


const std::string TOPIC_INPUT_DATA("input_data");
const std::string TOPIC_OUTPUT_DATA("output_data");
const std::string TOPIC_PUB("hostname");

const int	QOS = 1;
const int	N_RETRY_ATTEMPTS = 5;


/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */


class action_listener: public virtual mqtt::iaction_listener{

public:
	std::string name_;
	action_listener(const std::string& name) : name_(name) {}

	void on_failure(const mqtt::token& tok) override;

	void on_success(const mqtt::token& tok) override;

};


class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener{


public:
	//onverter class
	converter* conve_;
	tools* t;
	//name of the client
	std::string clientId_;

	mqtt::const_message_ptr* msg;
	// Counter for the number of connection retries
	int nretry_;
	// The MQTT client
	mqtt::async_client& cli_;
	// Options to use if we need to reconnect
	mqtt::connect_options& connOpts_;
	// An action listener to display the result of actions.
	action_listener subListener_;

	callback(mqtt::async_client& cli, mqtt::connect_options& connOpts ,std::string const& clientId)
				: nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"), clientId_(clientId) {}

	// This deomonstrates manually reconnecting to the broker by calling
	// connect() again. This is a possibility for an application that keeps
	// a copy of it's original connect_options, or if the app wants to
	// reconnect with different options.
	// Another way this can be done manually, if using the same options, is
	// to just call the async_client::reconnect() method.
	void reconnect();

	// Re-connection failure
	void on_failure(const mqtt::token& tok) override;

	// (Re)connection success
	// Either this or connected() can be used for callbacks.
	void on_success(const mqtt::token& tok) override;

	// (Re)connection success
	void connected(const std::string& cause) override;

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override;

	void message_handling(mqtt::const_message_ptr msg);

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override;

	void delivery_complete(mqtt::delivery_token_ptr token) override;


	~callback();
};
