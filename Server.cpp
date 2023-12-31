#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <SFML/Network.hpp>


int main()
{
    sf::TcpListener listener;
    sf::TcpSocket client;

    std::cout << "Demo Interface Application (TCP Server)\n"
              << " Current IP is: " << sf::IpAddress::getLocalAddress().toString() << '\n'
              << "Awaiting connection..." << std::endl;

    if(listener.listen(5002) != sf::Socket::Done)
    {
        std::cerr << "Error binding listener to port 5002\n";
        return 1;
    }
    
    if(listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error accepting client connection\n";
        return 1;
    }
    else
    {
        std::cout << "Connection successful!\n";
    }
    
    std::string filename;
    std::cout << "Enter MIDI filename: ";
    std::cin >> filename;
    
    std::ifstream midi(filename, std::ios::in | std::ios::binary);
    std::stringstream midi_data;
    midi_data << midi.rdbuf();
    
    //Validate midi
    if(midi_data.str().substr(0,4) != "MThd")
    {
        std::cerr << "Header does not seem to be valid.\n";
        return 1;
    }
    
    sf::Packet midi_packet;
    midi_packet << midi_data.str();
    
    client.send(midi_packet);
    
    while(true)
    {
        std::cout << "Enter a command: " << std::flush;
        std::string input;
        sf::Packet p;
        std::cin >> input;
        p << input;
        client.send(p);
    }
    
}