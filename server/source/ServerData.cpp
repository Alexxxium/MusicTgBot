#include "ServerData.h"
#include "ServerConstants.h"
#include <filesystem>
#include <codecvt>
#include <regex>
#include <fstream>
#include <TlHelp32.h>



namespace fs = std::filesystem;

namespace srv 
{
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist) {
		constexpr auto sl = "/";

		std::string target_dir = pth::USER_DATA_DIR + std::to_string(user_id) + sl + plist + sl;
		std::vector<std::string> res;

		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry: fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (init::SUPEXT.find(ext) != init::SUPEXT.end()) {
				res.push_back(entry.path().filename().string());
			}
		}

		return res;
	}

	int countTracks(const int64_t &id, const std::string &plist) {
		constexpr auto sl = "/";

		size_t res = 0;
		std::string target_dir = pth::USER_DATA_DIR + std::to_string(id) + sl + plist + sl;


		if (!fs::exists(target_dir)) {
			throw err::NOT_EXISTED_PLAYLIST;
		}

		for (const auto &entry : fs::directory_iterator(target_dir)) {
			const auto &ext = entry.path().extension().string();
			if (init::SUPEXT.find(ext) != init::SUPEXT.end()) {
				++res;
			}
		}

		return res;
	}

	std::wstring strUTF16(const std::string &utf8str) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(utf8str);
	}

	bool isValidName(const std::string &file_or_dir) {
		return isValidName(strUTF16(file_or_dir));
	}

	bool isValidName(const std::wstring &file_or_dir) {
		constexpr auto regexstr = L"^[a-zA-Zà-ÿÀ-ÿ¸¨0-9 `~!@#¹$;%^&()_\\[\\]+='-]+$";
		std::wregex valid(regexstr);
		return std::regex_search(file_or_dir, valid);
	}

	std::vector<std::string> split(std::string &&parsestr, const std::string &sep) {
		size_t pos = 0;
		std::vector<std::string> res;

		while ((pos = parsestr.find(sep)) != std::string::npos) {
			res.push_back(parsestr.substr(0, pos));
			parsestr.erase(0, pos + sep.length());
		}
		res.push_back(parsestr);

		return res;
	}



	bool hasHash(const std::string &track) {
		constexpr size_t len = 4;
		constexpr char sep = '-', a = 'a', z = 'z';

		std::string stem = fs::path(track).stem().string();
		stem.resize(len);

		if (stem[len - 1] != sep) {
			return false;
		}
		for (int i = 0; i < len - 1; ++i) {
			if (stem[i] < a || stem[i] > z) {
				return false;
			}
		}
		return true;
	}

	std::string hash() {
		constexpr char a = 'a', z = 'z' + 1 - a, sep = '-';
		constexpr int len = 3;

		std::string res;
		time(0);

		for (int i = 0; i < len; ++i) {
			res += a + rand() % z;
		}
		return res + sep;
	}

	void update(const std::string &id, const std::string &plist, std::string &track) {
		constexpr auto standart = "default", sl = "/";
		constexpr int maxlen = 50, hashlen = 4;

		std::string ext = fs::path(track).extension().string();
		std::string stem = fs::path(track).stem().string();
		std::string path = pth::USER_DATA_DIR + id + sl + plist + sl + track;

		if (fs::exists(path)) {
			if (hasHash(track)) {
				std::string hsh = hash();
				for (int i = 0; i < hashlen; ++i) {
					track[i] = hsh[i];
				}
			}
			else {
				track = hash() + track;
			}
			update(id, plist, track);
		}
		else if (!isValidName(stem)) {
			track = standart + ext;
			update(id, plist, track);
		}
		else if (stem.size() > maxlen) {
			stem.resize(maxlen);
			track = stem + ext;
			update(id, plist, track);
		}
	}

	void unlock(const std::string &id, const std::string &loclpath) {
		constexpr auto sl = "/", lockfile = "lock.txt", unlockbit = "0";
		std::string full = pth::USER_DATA_DIR + id + sl + loclpath;

		std::string path = 
			loclpath.empty() ? pth::BUFFER_DIR + id + sl :                                                   // empty arg        -> buffer dir
			fs::is_directory(full) ? pth::USER_DATA_DIR + id + sl + fs::path(full).stem().string() + sl :    // is directory     -> use dir name
			fs::path(full).parent_path().string() + sl;                                                      // is not directory -> use parent path (is dir)

		path += lockfile;

		if (!fs::exists(path)) {
			std::ofstream file(path);
			if (!file.is_open()) {
				throw std::runtime_error("Can`t open lock.txt!");
			}
			file << unlockbit;
		}
		else {
			std::fstream file(path);
			if (!file.is_open()) {
				throw std::runtime_error("Can`t open lock.txt!");
			}
			file.seekg(0, std::ios::beg);
			file << unlockbit;
		}
	}


	void GetChildProcesses(DWORD parentPID, std::vector<DWORD>& childPIDs) {
		PROCESSENTRY32 pe32;
		ZeroMemory(&pe32, sizeof(pe32));
		pe32.dwSize = sizeof(PROCESSENTRY32);
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnapshot == INVALID_HANDLE_VALUE) {
			return;
		}

		if (Process32First(hSnapshot, &pe32)) {
			do {
				if (pe32.th32ParentProcessID == parentPID) {
					childPIDs.push_back(pe32.th32ProcessID);
					GetChildProcesses(pe32.th32ProcessID, childPIDs);
				}
			} while (Process32Next(hSnapshot, &pe32));
		}
		CloseHandle(hSnapshot);
	}

	void TerminateChildProcesses(DWORD parentPID) {
		std::vector<DWORD> childPIDs;
		GetChildProcesses(parentPID, childPIDs);

		for (DWORD childPID: childPIDs) {
			HANDLE hChildProcess = OpenProcess(PROCESS_TERMINATE, FALSE, childPID);
			if (hChildProcess != NULL) {
				TerminateProcess(hChildProcess, 0);
				CloseHandle(hChildProcess);
			}
		}
	}

	void startProcess(const std::string &syscmd, int timeout, int pause) {
		constexpr auto cd = "cd ", wr = "\"";
		if (pause > timeout || timeout <= 0 || pause <= 0) {
			throw std::runtime_error("Invalid timeout or pause!");
		}

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&pi, sizeof(pi));

		si.cb = sizeof(si);
		LPSTR lp = const_cast<LPSTR>(syscmd.c_str());

		if (!CreateProcess(NULL, lp, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			throw err::CREATE_PROCESS_FAILED;
		}

		int time = 0;
		DWORD exitCode;
		while (time < timeout) {
			DWORD waitResult = WaitForSingleObject(pi.hProcess, pause);

			if (waitResult == WAIT_OBJECT_0) {
				GetExitCodeProcess(pi.hProcess, &exitCode);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				return;
			}
			else if (waitResult == WAIT_TIMEOUT) {
				time += pause;
			}
			else {
				break;
			}
		}

		TerminateChildProcesses(pi.dwProcessId);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}