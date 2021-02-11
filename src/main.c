#include "cutils/socket/socket.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int i;
	if (argc < 1)
		return -1;

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0) {
			printf("ezonic client 0.0.1-DEV\nCopyright (C) 2021 Fossbay\nThis is free software; see the source for copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
			return 0;
		} else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
			printf("Usage: %s [options]\n", argv[0]);

			printf(" -v  / --version      -     Display ezonic version information.\n");
			printf(" -h  / --help         -     Display this help page.\n");
			printf(" -s  / --server       -     Set server IP for one time connect.\n");
			printf(" -pk / --privatekey   -     Set your private key.\n");
			printf(" -pd / --pubkeydir    -     Set directory with public keys.\n");
			printf(" -as / --addserver    -     Add server to server cache.\n");
			printf(" -rs / --remserver    -     Remove server from server cache.\n");
			printf(" -c  / --channel      -     Autojoin channel after connect.\n");

			return 0;
		} else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--server") == 0) {

			socket_t socket;
			socket = open_socket(SOCKET_TCP);

			int status_server_connected = connect_socket(socket, (char *)argv[i + 1], atoi(argv[i + 2]));
			if (status_server_connected == -1) {
				printf("\nInvalid server not found.\n");
				return -1;
			}
			printf("[ezonic] $ Connected to server: IP: %s PORT:%i\n", (char *)argv[i + 1], atoi(argv[i + 2]));

			printf("[ezonic] $ Starting listening port.. \n");

			socket_t recvsocket = open_socket(SOCKET_TCP);
			socket_listen(recvsocket, 8080);

			struct client_info client_information;
			recvsocket = accept_socket(recvsocket, &client_information);
			printf("(%s, %i) [ezonic] $ server connected \n", client_information.address, client_information.port);
			char server_msg[2048] = {0};
			socket_recv(recvsocket, server_msg, sizeof(server_msg) + 10);
			printf("[ezonic] $ Server Message : %s", server_msg);
		}
	}

	return 0;
}
