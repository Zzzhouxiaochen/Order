#include"httplib.h"
#include<signal.h>
#include<jsoncpp/json/json.h>
#include"db.hpp"

const char* CONTENT_TYPE = "application/json";
MYSQL* mysql=mysql;
int main(){
	using namespase httplib;	
	mysql=order_system::MySQLInit();
	signal(SIGINT,[](int){order_system::MySQLRelease(mysql);exit(0);});
	order_system::DishTable dish_table(mysql);
	order_system::OrderTable order_table(mysql);
	
	Server server;
	server.Post("/dish",[&dish_table](const Request& req,Response& resp)){	//新增菜品
		Json::Value req_json;
		Json::Value resp_json;
		Json::Reader reader;
		Json::FastWriter writer;
		printf("新增菜品！\n");
		
		//1.获取数据解析成Json格式
		bool ret =readr.parse(req.body,req_json);
		if(!ret) {
			printf("parse body failed!");
			resp_json["ok"]=false;
			resp_json["reason"]="parse body failed!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//2.校验JSON信息
		if(rep_json["name"].empty()||req_json["price"].empty()) {
			printf("格式错误!");
			resp_json["ok"]=false;
			resp_json["reason"]="格式错误!\n";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;			
		}
		//3.调用数据库操作插入数据
		ret = dish_table.Insert(req_json);
		if(!ret) {
			printf("数据库插入数据失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="数据库插入数据失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});
	
	server.Get("/dish",[dish_table](const Request& req,Response& resp
		(void)req;
		Json::Value req_json;
		Json::Value resp_json;
		Json::Reader reader;
		Json::FastWriter writer;
		printf("看全部菜品！\n");
		//1.直接数据库操作
		bool ret = dish_table.Selectall(resq_json);
		if(!ret) {
			printf("查看所有菜品失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="查看所有菜品失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//2.正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
		return;
	});
	
	server.Get(R"(/dish/(\d+))",[dish_table](const Request& req,Response& resp)){
		//1.获取id
		int32_t dish_id=std::stoi(req.matches[1]);	//stoi  string ->整数	//std::to_string	数字->string
		printf("获取到编号是%d的菜品\n",auto dish_id);
		
		(void)req;
		Json::Value resp_json;
		Json::FastWriter writer;
		printf("看指定菜品！\n");
		//2.直接数据库操作
		bool ret = dish_table.SelectOnce(resq_json);
		if(!ret) {
			printf("查看指定菜品失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="查看指定菜品失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//3.正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});	
	
	server.Put(R"(/dish/(\d+))",[&dish_table](const Request& req,Response& resp)){
		Json::Value req_json;
		Json::Value resp_json;
		Json::Reader reader;
		Json::FastWriter writer;
		printf("修改菜品！\n");
		
		//1.获取id
		int32_t dish_id=std::stoi(req.matches[1]);	//stoi  string ->整数	//std::to_string	数字->string
		printf("获取到编号是%d的菜品\n",auto dish_id);
		
		//2.获取数据解析成Json格式
		bool ret =readr.parse(req.body,req_json);
		if(!ret) {
			printf("parse body failed!");
			resp_json["ok"]=false;
			resp_json["reason"]="parse body failed!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//3.校验JSON信息
		if(rep_json["name"].empty()||req_json["price"].empty()) {
			printf("格式错误!");
			resp_json["ok"]=false;
			resp_json["reason"]="格式错误!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;			
		}
		//4.调用数据库操作插入数据
		resp_json["dish_id"]=dish_id;	//dish_id加入到Json中
		ret = dish_table.Update(req_json);
		if(!ret) {
			printf("数据库更新数据失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="数据库更新数据失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});	
	
	server.Delete(R"(/dish/(\d+))",[&dish_table](const Request& req,Response& resp)){
		Json::Value resp_json;
		Json::FastWriter writer;
		//1.获取id
		int32_t dish_id=std::stoi(req.matches[1]);	//stoi  string ->整数	//std::to_string	数字->string
		printf("删除编号是%d的菜品\n",auto dish_id);
		//2.直接数据库操作
		bool ret = dish_table.Delete(req_json);
		if(!ret) {
			printf("删除指定菜品失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="删除指定菜品失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//3.正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});	



	server.Post("/order",[&order_table](const Request& req,Response& resp))	{
		Json::Value req_json;
		Json::Value resp_json;
		Json::Reader reader;
		Json::FastWriter writer;
		printf("新增订单！\n");
		
		//1.获取数据解析成Json格式
		bool ret =readr.parse(req.body,req_json);
		if(!ret) {
			printf("新增订单失败！");
			resp_json["ok"]=false;
			resp_json["reason"]="新增订单失败！";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//2.校验JSON信息
		if(rep_json["table_id"].empty()||req_json["time"].empty()||req_json["dish_ids"].empty()) {
			printf("格式错误!");
			resp_json["ok"]=false;
			resp_json["reason"]="格式错误!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;			
		}
		//3.构造其他需要的字段
		req_json["status"]=1;	//1进行中	0关闭
		//把dish_ids转换成dishes
		const Json::Value& dish_ids=req_json["dish_ids"];
		req_json["dishes"]=writer.write(dish_ids);
		//4.调用数据库操作插入数据
		ret = order_table.Insert(req_json);
		if(!ret) {
			printf("数据库插入数据失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="数据库插入数据失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});
	
	server.Get("/order",[order_table](const Request& req,Response& resp))	{
		(void)req;
		Json::Value resp_json;
		Json::FastWriter writer;
		printf("看全部订单！\n");
		//1.直接数据库操作
		bool ret = order_table.Selectall(resq_json);
		if(!ret) {
			printf("查看所有菜品失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="查看所有菜品失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//2.正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});
	
	server.Put(R"(/order/(\d+))",[](const Request& req,Response& resp))	{
		Json::Value req_json;
		Json::Value resp_json;
		Json::Reader reader;
		Json::FastWriter writer;
		printf("修改菜品！\n");
		
		//1.获取id
		int32_t dish_id=std::stoi(req.matches[1]);	//stoi  string ->整数	//std::to_string	数字->string
		printf("获取到订单编号是%d的订单章台\n",auto dish_id);
		
		//2.获取数据解析成Json格式
		bool ret =readr.parse(req.body,req_json);
		if(!ret) {
			printf("parse body failed!");
			resp_json["ok"]=false;
			resp_json["reason"]="parse body failed!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//3.校验JSON信息
		if(rep_json["status"].empty()) {
			printf("格式错误!");
			resp_json["ok"]=false;
			resp_json["reason"]="格式错误!";
			resp.status=400;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;			
		}
		//4.调用数据库操作插入数据
		resp_json["dish_id"]=dish_id;	//dish_id加入到Json中
		ret = order_table.ChangeState(req_json);
		if(!ret) {
			printf("数据库更新数据失败!");
			resp_json["ok"]=false;
			resp_json["reason"]="数据库更新数据失败";
			resp.status=500;
			resp.set_content(writer.write(resp_json),CONTENT_TYPE);
			return;
		}
		//正确的响应
		resp_json["ok"]=true;
		resp.status=200;
		resp.set_content(writer.write(resp_json),CONTENT_TYPE);
	});
	
	server.set_base_dir("./wwwroot");
	server.listen("0.0.0.0",9094);
}
