#include "Users.h"

namespace aiafpb1
{
	// приведение параметров к начальным "нулевым" значениям
	void User::clear()
	{
		this->log.clear();
		this->pword.clear();
		this->name.clear();
	}

	// "полное" имя пользователя в формате (имя--логин) для возможности идентификации, т.к. имена пользователей могут совпадать
	std::string User::fullName() const { return (name + "--" + log); }

	User& User::operator=(const User& u)
	{
		if (&u != this)
		{
			log = u.log;
			pword = u.pword;
			name = u.name;
		}
		return *this;
	}

	// вывод в поток данных пользователя, используется для проверки при регистрации пользователя
	std::ostream& operator<<(std::ostream& out, const User& u)
	{
		out << " логин: " << u.log << std::endl;
		out << "пароль: " << u.pword << std::endl;
		out << "   имя: " << u.name << std::endl;
		return out;
	}

	Users::Users() {}
	Users::~Users() {}

	void Users::add(const User& u)
	{
		std::string query = "'";
		query += u.log + "',";
		query += u.pword + "',";
		query += u.name + "',";
		DB->addUser(query);
		
	}


	bool Users::nameFound(User& c) { 
		std::string tag = "name";
		std::string what = c.name;
		return DB->findFromUsers(tag, what);
	}

	bool Users::logFound(User& c) { 
		std::string tag = "log";
		std::string what = c.log;
		return DB->findFromUsers(tag, what);
	}

	// проверка наличия зарегистрированных пользователей
	bool Users::empty() const { 
		return DB->empty();

	}

	// вывод списка "полных" имен пользователей
	std::stringstream Users::showNames() const
	{
		std::stringstream info;
		info << std::endl << "Имена пользователей:" << std::endl;
		info << DB->Names().c_str();
		return info;
	}
}
