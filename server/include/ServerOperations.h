#pragma once
#include <functional>



namespace srv
{
	class Operation {
	protected:
		std::string name_key;

	public:
		std::string name() const noexcept;

		virtual ~Operation() = default;
		virtual void execute(const std::string &args) const;
		virtual std::function<void()> executor(const std::string &args) const;
	};


	class SendAudio: public Operation {
	public:
		SendAudio(const std::string &cmd) { 
			name_key = cmd; 
		}
		std::function<void()> executor(const std::string &args) const override {
			return [this, args]() { execute(args); };
		};

		void execute(const std::string &args) const override;
	};
}