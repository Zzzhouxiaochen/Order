#include<cstdio>
#include<cstdlib>
#include<mysql/mysql.h>	//第三方库

int main(){
	//1.创建数据库的操作句柄(遥控器)
	MYSQL* mysql=mysql_init(NULL);
	//2.建立句柄和数据库之间的联系（连接服务器） 
	if(mysql_real_connect(mysql/*遥控器*/,"127.0.0.1"/*主机名*/,"root"/*用户名*/,""/*密码*/,
							"order_system"/*数据库名字*/,3306/*端口号*/,NULL,0/*客户端选项*/)==NULL) {
								printf("连接失败！:%s\n",mysql_error(mysql));
								return 1;
							}
	//设置编码格式（服务器和客户端匹配）
	mysql_set_character_set(mysql,"utf8");
	
	//3.拼装数据的sql
	char sql[1024]={0};
	sprintf(sql,"select* from dish_table");
	//4.执行sql语句
	int ret=mysql_query(mysql,sql);
	if(ret !=0) {
		printf("sql 执行失败!\n");
		mysql_close(mysql);
		return 1;
	}
	//5.获取结果进行遍历
	//获取集合
	MYSQL_RES* result=mysql_store_result(mysql);
	int rows=mysql_num_rows(result);	//行
	int cols=mysql_num_fields(result);	//列
	//行列遍历得到结果
	for(int row=0;row<rows;++row) {
		MYSQL_ROW mysql_row=mysql_fetch_row(result);	//得到一行数据
		//使用方括号取下标操作获得每列数据
		for(int col=0;col<cols;col++) {
			printf("%s\t",mysql_row[col]);
		}
		printf("\n");
	}
	//6.结果集合需要手动释放
	mysql_free_result(result);
	//关闭连接
	mysql_close(mysql);
	return 0;
}
