#pragma once
#include <vector>
#include <string>
#include <WinSock2.h>



namespace srv 
{
	std::vector<std::string> getPlayList(const int64_t &user_id, const std::string &plist);

	int countTracks(const int64_t &id, const std::string &plist);

	std::wstring strUTF16(const std::string &utf8str);
	bool isValidName(const std::string  &file_or_dir);
	bool isValidName(const std::wstring &file_or_dir);

	std::vector<std::string> split(std::string &&parsestr, const std::string &sep);



	void GetChildProcesses(DWORD parentPID, std::vector<DWORD> &childPIDs);

	void TerminateChildProcesses(DWORD parentPID);


	// Ñreate a win32 process and waits for it to complite or will come timeout
	void startProcess(const std::string &syscmd, int timeout, int pause);

	// Check track name: Uncorrect name - set default. Big name - resize, Existed name - add hash
	void update(const std::string &id, const std::string &plist, std::string &track);

	// Unlock playlist for client-bot
	void unlock(const std::string &id, const std::string &loclpath);
}