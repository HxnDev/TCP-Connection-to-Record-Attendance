#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main() {

	char server_message[200];
	char buf[200];
    int password = 1234;                //Already saved password
    char name_msg[50] = "Enter you name = ";
    char dept_msg[50] = "Enter you department = ";
    char name[20];
    char dept[10];
    

    //string buff;
    char auth_message[50] = "Kindly enter your 4 digit password = ";            //Message to be displayed at client's end
	
	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);           //This will cater atmost 5 clients at a time
	
    int count = 0;
    while (1) {
        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);
        
        pid_t pid = fork();

        if (pid == 0) {
            //Recieving the password from client
            send(client_socket, auth_message, sizeof(auth_message), 0);	    //Sending Password Request
            recv(client_socket, &buf, sizeof(buf), 0);      //Recieving Password
            cout<<"The password entered is = "<<buf<<endl;

            //Authenticating the password
            int buff = atoi(buf);

            
            if (buff == password)
            {
                cout<<"Authentication Successful!"<<endl;
                
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    send(client_socket, asctime(tt), sizeof(dept_msg), 0);
                
                // Starting Communication if password is authenticated

                //Server requests for client's name
                recv(client_socket, &buf, sizeof(buf), 0);
                strcpy(name, buf);

                cout << "Name of client is = "<<name << endl;

                send(client_socket, dept_msg, sizeof(dept_msg), 0);	
                recv(client_socket, &buf, sizeof(buf), 0);
                strcpy(dept, buf);
                cout << dept << endl;

                string department(dept);

                if (department == "PF")                 //Writing into PF.txt file
                {
                    fstream write("PF.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t \t"<<asctime(tt);
                    write.close();
                }

                else if (department == "OOP")                 //Writing into OOP.txt file
                {
                    fstream write("OOP.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t \t"<<asctime(tt);
                    write.close();
                }

                else if (department == "Data Structures" or department == "DS")                 //Writing into DS.txt file
                {
                    fstream write("DS.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t \t"<<asctime(tt);
                    write.close();
                }

                else if (department == "COAL")                 //Writing into COAL.txt file
                {
                    fstream write("COAL.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t \t"<<asctime(tt);
                    write.close();
                }

                else if (department == "Algo")                 //Writing into Algo.txt file
                {
                    fstream write("Algo.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t< \t"<<asctime(tt);
                    write.close();
                }

                else if (department == "CNET")                 //Writing into CNET.txt file
                {
                    fstream write("CNET.txt",ios::app);
                    time_t t;

                    struct tm *tt;
                    time(&t);
                    tt=localtime(&t);
                    write << count <<"\t"<<dept<<"\t"<<name<<"\t \t"<<asctime(tt);
                    write.close();
                }

                else
                {
                    cout<<"Invalid Department was entered"<<endl;
                }
            
            }

            else
            {
                    cout<<"The password entered is incorrect"<<endl;
                    

            }
            
        }

        else if (pid > 0) {
            close(client_socket);
        }

        else {
            cout << "Fork failed" << endl;
        }
        count++;
        if (count == 4)
        {
            break;
        }
    }
	
}
