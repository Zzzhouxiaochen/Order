#pragma once
                                     
#include<unistd.h>                                     
#include<stdio.h>                                      
#include<stdlib.h>                                     
#include<mysql/mysql.h>                                
#include<jsoncpp/json/json.h>

namespace order_system {
static MYSQL* MySQLInit() {             
	//1.创建数据库的操作句柄(遥控器)
	MYSQL* mysql=mysql_init(NULL);
	//2.建立句柄和数据库之间的联系（连接服务器）
	if(mysql_real_connect(mysql/*遥控器*/,"127.0.0.1","root"/*密码*/,""/*密码*/,
							"order_system"/*数据库名字*/,3306/*端口号*/,NULL,0/*客户端选项*/)==NULL) {
								printf("连接失败！:%s\n",mysql_error(mysql));
								return NULL;
							}
	//设置编码格式（服务器和客户端匹配）
	mysql_set_character_set(mysql,"utf8");
	return mysql;
}  

static void MySQLRelease(MYSQL* mysql) {             
	mysql_close(mysql);
}                                                    
  
class DishTable{                                     
public:                                            
	DishTable(MYSQL* mysql):mysql_(mysql){ 
		
	} 
	
	//用JSON作为函数参数
	//一个核心类，两个重要方法 
	//Json::Value	表示一个Json对象用法和map一样
	//Writer::write：把一个JSON对象转成字符串（std::string）
	//Reader::parse：把字符串反序列化成Json对象
	bool Insert(const Json::Value& dish){	//插入一道菜
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(
			sql,"insert into dish_table values(null,'%s',%d)",
			dish["name"].asCString(),
			dish["price"].asInt()
			);
		//2.执行
		int ret=mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("DishTable Insert Failed! %s\n", mysql_error(mysql_));
			return false;
		}
		printf("DishTable Insert OK!\n");
		return true;
	}
	
	
	bool Selectall(Json::Value* dishes){
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(sql,"select dish_id,name,price from dish_table");
		//2.执行sql语句
		int ret=mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("DishTable Selectall Failed! &s\n", mysql_error(mysql_));
			return 1;
		}
		//3.获取结果进行遍历
		//1.获取集合
		MYSQL_RES* result=mysql_store_result(mysql_);
		int rows = mysql_num_rows(result);	//行
		//2.行遍历得到结果
		for(int i = 0; i < rows; ++i) {
			MYSQL_ROW row=mysql_fetch_row(result);	//得到一行数据
			Json::Value dish;
			dish["dish_id"]=atoi(row[0]);	//id
			dish["name"]=row[1];	//name
			dish["price"]=atoi(row[2]);	//price
			dishes->append(dish);
		}
		//4.结果集合需要手动释放
		mysql_free_result(result);
		return true;
	}
	
	//用JSON作为输出型参数
	bool SelectOnce(int32_t dish_id, Json::Value* dish) {
		//1.拼装SQL
    char sql[1024*8]={0};
		sprintf(sql,"select dish_id,name,price from dish_table where dish_id = %d",dish_id);
		//2.执行sql语句
		int ret=mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("DishTable SelectOnce Failed! %s\n", mysql_error(mysql_));
			return false;
		}
		//3.获取结果进行遍历
		//获取集合
		MYSQL_RES* result=mysql_store_result(mysql_);
		int rows=mysql_num_rows(result);	//行
		if(rows != 1) {
			printf("DishTable SelectOnce Failed! \n");
			mysql_free_result(result);
			return false;
		}
		MYSQL_ROW row=mysql_fetch_row(result);	//得到一行数据
		(*dish)["dish_id"]=dish_id;
		(*dish)["name"]=row[1];
		(*dish)["price"]=atoi(row[2]);
		//4.结果集合需要手动释放
		mysql_free_result(result);
		return true;
	}
	

	bool Update(const Json::Value& dish){
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(sql,"update dish_table set name = '%s',price = '%d' where dish_id = %d",
			dish["name"].asCString(),dish["price"].asInt(),dish["dish_id"].asInt());
		//2.执行sql语句
		int ret=mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("DishTable Update Failed! %s\n",mysql_error(mysql_));
			return false;
		}
		printf("DishTable Update OK!\n");		
		return true;
	}
	
	
	bool Delete(int32_t dish_id){
		//1.拼装SQL
    char sql[1024*8]={0};
		sprintf(sql,"delete from dish_table where dish_id = %d",dish_id);
		//2.执行sql语句
		int ret=mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("DishTable Delete Failed! %s\n",mysql_error(mysql_));
			return false;
		}
		printf("DishTable Delete OK!\n");		
		return true;
	}
	
 private:
	MYSQL* mysql_;
}; 


class OrderTable{
public:                                            
	OrderTable(MYSQL* mysql):mysql_(mysql){ 
		
	}
		
	bool Insert(const Json::Value& order){
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(
			sql,"insert into order_table values(null,'%s','%s','%s',%d)",
			order["table_id"].asCString(),
			order["time"].asCString(),
			order["dishes"].asCString(),
			order["status"].asInt()
			);
		//2.执行sql语句
		int ret = mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("OrderTable Insert Failed! %s\n",mysql_error(mysql_));
			return false;
		}
		printf("OrderTable Insert OK!\n");		
		return true;
	}
	
	bool Selectall(Json::Value* orderes){
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(
			sql,"Select order_id,table_id,time,dishes,status from order_table");
		//2.执行sql语句
		int ret = mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("OrderTable Selectall Failed! %s\n",mysql_error(mysql_));
			return false;
		}
		printf("OrderTable Selectall OK!\n");
		//3.获取结果进行遍历
		//1.获取集合
		MYSQL_RES* result=mysql_store_result(mysql_);
		int rows = mysql_num_rows(result);	//行
		//2.行遍历得到结果
		for(int i=0;i<rows;++i) {
			MYSQL_ROW row=mysql_fetch_row(result);	//得到一行数据
			Json::Value order;
			order["order_id"]=atoi(row[0]);	 // 注意, order_id 是数字, table_id 是字符串 
			order["table_id"]=row[1];	
			order["time"]=row[2];	
			order["dishes"]=row[3];	
			order["status"]=atoi(row[4]);	//price
			orderes->append(order);
		}
		//4.结果集合需要手动释放
		mysql_free_result(result);		
		return true;
	}
		
	bool ChangeState(const Json::Value& order){
		//1.拼装SQL
		char sql[1024*8]={0};
		sprintf(
			sql,"update order_table set status = %d where order_id =%d",
			order["status"].asInt(),
			order["order_id"].asInt()
			);
		//2.执行sql语句
		int ret = mysql_query(mysql_,sql);
		if(ret !=0) {
			printf("OrderTable ChangState Failed! %s\n",mysql_error(mysql_));
			return false;
		}
		printf("OrderTable ChangState OK!\n");		
		return true;
	}

 private:
	MYSQL* mysql_;

};

}
