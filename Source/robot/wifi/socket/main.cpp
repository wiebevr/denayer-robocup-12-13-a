#include <iostream>
#include <sys/socket.h>
using namespace std;

int main(int argc, char **argv)
{
	int fd;

	/* create a tcp/ip socket */
	/* request the Internet address protocol */
	/* and a reliable 2-way byte stream (TCP/IP) */

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "cannot create socket";
		return 0;
	}

	cout << "created socket: descriptor=" << fd << endl;
	return 0;
}
