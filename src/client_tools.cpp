
#include "client_tools.h"

/********ACTION LISTENER FUNCTIONS**********/

void action_listener::on_failure(const mqtt::token& tok){
	std::cout << name_ << " failure";
	if (tok.get_message_id() != 0)
		std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
	std::cout << std::endl;
}

void action_listener::on_success(const mqtt::token& tok){
	std::cout << name_ << " success";
	if (tok.get_message_id() != 0)
		std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
	auto top = tok.get_topics();
	if (top && !top->empty())
		std::cout << "\ttoken topic: '" << (*top)[0] << std::endl;
	std::cout << std::endl;
}


/********CALLBACK FUNCTIONS**********/

void callback::reconnect() {
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
void callback::on_failure(const mqtt::token& tok) {
	std::cout << "Connection attempt failed" << std::endl;
	if (++nretry_ > N_RETRY_ATTEMPTS)
		exit(1);
	reconnect();
}

void callback::on_success(const mqtt::token& tok) {}

void callback::connected(const std::string& cause) {
	std::cout << "\nConnection success" << std::endl;
	std::cout << "\nSubscribing to topic '" << TOPIC_INPUT_DATA << "'\n"
		<< "\tfor client " << clientId_
		<< " using QoS" << QOS << "\n"
		<< "\nPress Q<Enter> to quit\n" << std::endl;
	cli_.publish(TOPIC_PUB,clientId_);
	cli_.subscribe(TOPIC_INPUT_DATA, QOS, nullptr, subListener_);
}

void callback::connection_lost(const std::string& cause) {
	std::cout << "\nConnection lost" << std::endl;
	if (!cause.empty())
		std::cout << "\tcause: " << cause << std::endl;

	std::cout << "Reconnecting..." << std::endl;
	nretry_ = 0;
	reconnect();
}

void callback::message_handling(mqtt::const_message_ptr msg){
	std::string converter_result;
	std::string return_msg;
	converter_result = conve_->hex_converter(msg->to_string());
	if(converter_result.size() == 0){
		return;
	}
	return_msg = t->create_result_msg(msg->to_string(),converter_result);
	std::cout <<"Return msg -> "<< return_msg <<'\n'<< std::endl;
	cli_.publish(TOPIC_OUTPUT_DATA,return_msg);
}

void callback::message_arrived(mqtt::const_message_ptr msg) {
	std::cout << "Message arrived" << std::endl;
	std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
	std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

	message_handling(msg);

}


void callback::delivery_complete(mqtt::delivery_token_ptr token) {}

callback::~callback() {}


