#pragma once
#include <QString>

struct server_t {
	QString		name;
	QString		IP;  // go check for an IP class
	QString		subnet; 
};

class Server
{
public:
	Server();
	~Server();
private:
	server_t server;


};

