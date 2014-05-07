/*
  Very basic and simple c++ config reader

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>
#include "configreader.cpp"

extern std::map<std::string, std::string> Config;

int main(int argc, char* argv[]) {

	const char* path; //Where can we find the config?
	if ( argc != 2 ) {
		std::cout << "usage: " << argv[0] << " filename" << std::endl;
		std::exit(1);
	} else {
		//Set config path!
		path = argv[1];
	}

	//Let our configreader parse!
	readconfig(path);

	//formatted output
	for(std::map<std::string, std::string>::iterator iterator = Config.begin(); iterator != Config.end(); iterator++) {
		std::cout << iterator->first << " = " << iterator->second << std::endl;
	}

	return 0;
}


