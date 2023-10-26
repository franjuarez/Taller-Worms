#include <vector>
#include <string>


class Client {

private:
public:
	Client(...);

	~Client(...);

	std::vector<std::string> getAvailableMaps();

	void selectMap(std::string);

	
	//game funciona como monitor y para empaquetar todo lo que se tiene que graficar

	Game getGameStatus();
	

	//runCommand();

	//jumpCommand();

	//shootCommand();


};
