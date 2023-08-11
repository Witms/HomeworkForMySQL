#include "ConnectToDB.h"

namespace aiafpb1
{

ConnectToDB::ConnectToDB() {

	mysql_init(&mysql);
	if(&mysql == nullptr) {
		std::cout << "Error: can`t create MySQL-descriptor" << std::endl;
	}

	if(!mysql_real_connect(&mysql, "localhost", "cow", "cow", "chatdb", 0, NULL, 0)) {
		std::cout << "Error: can`t connect to database " << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "Success to set connect to database" << std::endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	std::cout << "Connection characterset: " << mysql_character_set_name(&mysql) << std::endl;

}

ConnectToDB::~ConnectToDB() {
	mysql_close(&mysql);
}

void ConnectToDB::addUser(std::string aft) {
	std::string bef = "insert into users(log, passwd, name) values(";
       	bef += aft;	
	bef += ")";
	mysql_query(&mysql,bef.c_str()); 
}

bool ConnectToDB::findFromUsers(std::string tag, std::string what) {

	std::string query = "select exists(select ";
	query += tag;
	query += " from users where ";
	query += tag;
	query += " = '";
	query += what;
	query += "')";
	mysql_query(&mysql, query.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				result += row[i];
			}
		}
	}		

	if(result == "0") { return 0;}
	else { return 1;}

}

bool ConnectToDB::empty() {
	mysql_query(&mysql, "select exists(select * from users)");

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				result += row[i];
			}
		}
	}		


	if(result == "0") { return 0;}
	else { return 1;}

}

std::string ConnectToDB::Names() {

	std::string str;
	
	mysql_query(&mysql, "select name,log from users");

	MYSQL_RES* res;
	MYSQL_ROW row;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				str += row[i]; 
				str += "--";
			}
			str += '\n';
		}
	}		
	
	return str;

}

}
