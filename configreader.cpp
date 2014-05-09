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

#include <fstream>
#include <string>
#include <algorithm>
#include <map>

//In case you want to use the config externally
std::map<std::string, std::string> Config;

void readconfig(const char* path) {
	//Open a filestream for our config file
	std::fstream conf;
	conf.open(path, std::ios::in);

	//Introduce multine /**/ comments
	bool ismultiline;
	std::string line;

	if (conf.is_open()) {
		while(conf.good()) {
			std::getline(conf, line, '\n');

			//Multi-line commentary
			if (line.find("/*")) ismultiline = true;
			if (line.find("*/")) {
				if (line.find_first_of("*/") != line.npos) line.erase(line.find_first_of("*/"));
				ismultiline = false;
			}
			if (ismultiline) continue;

			//Remove single line comments and empty columns
			// if (line.find("#") != line.npos) line.erase(line.find_first_of("#"));
			if (line.find("//") != line.npos) line.erase(line.find_first_of("//"));
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
}

