#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <Windows.h>
#include <windef.h>

#include "Client.h";
#include "Utils.h";

using namespace std;



int main(int argc, char* argv[])
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(1, 1), &wsa_data);
	std::vector<std::string> parameter_list(argv + 1, argv + argc);

	std::string username = parameter_list.at(0);
	std::string password = parameter_list.at(1);
	std::string server_ip = parameter_list.at(2);
	std::string server_port_string = parameter_list.at(3);
	size_t server_port = Utils::string_to_size_t(server_port_string);

	std::cout << "attempting to connect to " << server_ip << ":" << server_port << " as " << username << std::endl;

	std::unique_ptr<Client> client(new Client(server_port, server_ip));
	client->connect_and_auth(username, password);
	client->start_reciver();
	client->sender();
	WSACleanup();
}