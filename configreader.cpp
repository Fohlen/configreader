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
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

//In case you want to use the config externally
std::map<std::string, std::string> Config;

int main(int argc, char* argv[]) {

	const char* path; //Where can we find the config?
	if ( argc != 2 ) {
		std::cout << "usage: " << argv[0] << " filename" << std::endl;
		std::cout << "Setting config path to default (schema.conf)" << std::endl;
		path = "schema.conf";
	} else {
		//Set config path!
		path = argv[1];
	}

	//Open a filestream for our config file
	std::fstream conf;
	conf.open(path, std::ios::in);

	if (conf.is_open()) {
		while(conf.good()) {
			char buf[256];
			conf.getline(buf, 256, '\n');

			std::string line(buf);

			if (line.find('#') != line.npos) line.erase(line.find_first_of('#'));
			if (line.empty()) continue;

			if (line.find("=") != line.npos) {
				int pos = line.find("=");

				std::string key, value;
				key = line.substr(0, pos);
				value = line.substr(pos, line.size());

				key.erase(std::remove_if(key.begin(), key.end(), isspace));
				//Uggly quickfix to remove '=' character
				value.erase(0, 1);
				value.erase(remove_if(value.begin(), value.end(), isspace));

				Config[key] = value;
			}

		}
	}

	//Close config
	conf.close();

	//Print the config
	std::map<std::string, std::string>::iterator iterator;
	for (iterator = Config.begin(); iterator != Config.end(); iterator++) {
		std::cout << iterator->first << " = " << iterator->second << std::endl;
	}

	return 0;
}
