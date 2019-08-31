#include"db.hpp"
//单元测试

// void TestDishTable() {
	// MYSQL* mysql=order_system::MySQLInit();
	// order_system::DishTable dish_table(mysql);
	
	// //插入数据		//成功
	// Json::Value dish;
	// dish["name"]="干煸豆角";
	// dish["price"]=1000;
	// bool ret = dish_table.Insert(dish);
	// printf("ret = %d\n",ret);
	
	// //查找所有数据   //成功
	// Json::Value dishes;
	// int ret = dish_table.Selectall(&dishes);
	// printf("ret = %d\n",ret);
	// Json::StyledWriter writer;
	// printf("%s\n",writer.write(dishes).c_str());
	
	 // //查找指定数据   //成功
	// Json::Value dish;
	// int ret = dish_table.Selectall(9,&dish);
	// printf("ret = %d\n",ret);
	// Json::StyledWriter writer;
	// printf("%s\n",writer.write(dish).c_str());
	
	//修改指定数据   //成功
	// Json::Value dish;
	// dish["dish_id"]=9;
	// dish["name"]="肥宅快乐水";
	// dish["price"]=999;
	// int ret = dish_table.Update(dish);
	// printf("ret = %d\n",ret);

	// //删除指定数据	//成功
	// int ret = dish_table.Delete(9);
	// printf("ret = %d\n",ret);
	
	// order_system::MySQLRelease(mysql);
	
// }

void TestOrderTable() {
	MYSQL* mysql=order_system::MySQLInit();
	order_system::OrderTable order_table(mysql);
	
	//插入订单		//成功
	// Json::Value orderes;
	// dish["table_id"]="明教";
	// dish["time"]="2019/08/11 12:00";
	// dish["dishes"]="[1,2,3]";
	// dish["status"]=1;
	// bool ret = order_table.Insert(order);
	// printf("ret = %d\n",ret);
	
	 //查找所有订单   //成功
	// Json::Value orders;
	// int ret = order_table.Selectall(&orders);
	// printf("ret = %d\n",ret);
	// Json::StyledWriter writer;
	// printf("%s\n",writer.write(orders).c_str());
	
	 //修改状态   //成功
	Json::Value order;
	order["order_id"]=1;
	order["status"]=1;
	int ret = dish_table.ChangeState(order);
	printf("ret = %d\n",ret);
	
	//修改指定数据   //成功
	// Json::Value dish;
	// dish["dish_id"]=9;
	// dish["name"]="肥宅快乐水";
	// dish["price"]=999;
	// int ret = dish_table.Update(dish);
	// printf("ret = %d\n",ret);

	//删除指定数据	//成功
	// int ret = dish_table.Delete(9);
	// printf("ret = %d\n",ret);
	
	order_system::MySQLRelease(mysql);
	
}


int main() {
	//TestDishTable();
	TestOrderTable();
	return 0;
}