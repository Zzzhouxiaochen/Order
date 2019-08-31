#incldue<cstdio>
#include<cstdlib>
#include<mysql/mysql.h>	//第三方库

int main(){
	//创建数据库的操作句柄(遥控器)
	MYSQL* mysql=mysql_init(NULL);
	//2.建立句柄和数据库之间的联系（连接服务器）
	if(mysql_real_connect(mysql/*遥控器*/,"127.0.0.1","root"/*密码*/,""/*密码*/,
							"order_system"/*数据库名字*/,3306/*端口号*/,NULL,0/*客户端选项*/)==NULL) {
								printf("连接失败！:%s\n",mysql_error(mysql));
								return 1;
							}
	//设置编码格式（服务器和客户端匹配）
	mysql_set_character_set(mysql,"utf8");
	
	//拼装插入数据的sql
	char sql[1024]={0};
	int price=2000;
	sprintf(sql,"insert into caipinbiao values(null,'干煸豆角',%d)",price);
	//执行sql语句
	int ret=mysql_query(mysql,sql);
	if(ret !=0) {
		printf("sql 执行失败!\n");
		mysql_close(mysql);
		return 1;
	}
	//关闭连接
	mysql_close(mysql);
	return 0;
}

-L/usr/lib64/mysql  去那个目录找库  /lmysqlclient	连接库