#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>

int main()
{
    sf::TcpSocket socket;
    std::string server_ip;
    std::cout << "Enter Server IP: ";
    std::cin >> server_ip;
    auto status = socket.connect(server_ip,5002);
    
    if(status != sf::Socket::Done)
    {
        std::cerr << "Error connecting to server\n";
        return 1;
    }
    else
    {
        std::cout << "Connection successful!\n";
    }
    
    sf::Packet packet;
    std::string s;
    std::ofstream out_midi("out.mid", std::ios::out | std::ios::binary);
    
    socket.receive(packet);

    packet >> s;
    std::cout << "Received MIDI. Saving as out.mid\n";
    out_midi << s;
    
    socket.setBlocking(false);
    std::cout << "TCP socket set to blocking. Awaiting incoming commands from server\n";
    while(true)
    {
        sf::Packet p;
        std::string command = "";
        if(socket.receive(p) == sf::Socket::Done) 
        {
            p >> command;
            std::cout << "Received a command: " << command << std::endl;
            if(command == "q") return 0;
            command = "";
        }
    }
}