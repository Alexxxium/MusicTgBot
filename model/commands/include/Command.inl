
namespace mb::cmd
{
	template<typename T>
	bool Execute<T>::execute(const std::string &cmdname, TgBot::Message::Ptr message, TgBot::Bot &bot, const std::string &callback) {
		std::unique_ptr<Command> wrap(new T(cmdname));

		switch (wrap->type())
		{
		case CMD_TYPE_MACRO: case CMD_TYPE_ANY: {
			wrap->setMessage(message);
			break;
		}
		case CMD_TYPE_INLINE: {
			TgBot::CallbackQuery::Ptr query(new TgBot::CallbackQuery);
			query->message = message;
			query->data = callback;
			wrap->setCallbackQuery(query);
			break;
		}
		default:
			throw err::UNKNOWN_CMD;
			break;
		}

		return wrap->execute(bot);
	}
}
