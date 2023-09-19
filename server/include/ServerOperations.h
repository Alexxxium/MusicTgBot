#pragma once
#include <functional>
#include <vector>
#include <string>



namespace srv
{
	class Operation {
	public:
		virtual ~Operation() = default;
		virtual void execute(const std::vector<std::string> &args) const = 0;
		virtual std::function<void()> executor(const std::vector<std::string> &args) const = 0;
	};


	class SendAudio: public Operation {
	public:
		SendAudio() = default;
		~SendAudio() = default;

		std::function<void()> executor(const std::vector<std::string> &args) const override {
			return [this, args]() { execute(args); };
		};

		void execute(const std::vector<std::string> &args) const override;
	};

	class SendAudioGroup: public Operation {
	public:
		SendAudioGroup() = default;
		~SendAudioGroup() = default;

		std::function<void()> executor(const std::vector<std::string> &args) const override {
			return [this, args]() { execute(args); };
		}

		void execute(const std::vector<std::string> &args) const override;
	};

	class DownloadAudioGroup: public Operation {
	public:
		DownloadAudioGroup() = default;
		~DownloadAudioGroup() = default;

		std::function<void()> executor(const std::vector<std::string> &args) const override {
			return [this, args]() { execute(args); };
		};

		void execute(const std::vector<std::string> &args) const override;
	};
}