#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
	
	char request[200];
	char buf[200];
    char pass[5];
    char name[20];
    char dept[10];
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));

    //Entering the password inorder to authenticate
    recv(sock, &buf, sizeof(buf), 0);   //Recieving Authentication Message
    cout<<buf;
    cin>>pass;  //Inputting Password
    send(sock, pass, sizeof(pass), 0);      //Sending Password to server

    recv(sock, &buf, sizeof(buf), 0);   //Recieving Time Log
    cout<<"Time of Access = "<<buf<<endl;
    

            //Client will enter his name
            cout<<"Enter your name "<<endl;
            cin>>name;
            send(sock, name, sizeof(name), 0);

            

            // //Client will enter his department

             recv(sock, &buf, sizeof(buf), 0);
             cout<<buf;
             cin>>dept;
             send(sock, dept, sizeof(dept), 0);
            
           
        close(sock);

}
