
create database if not exists order_system;
use  order_system;

create table if not exists dish_table(
  dish_id int not null primary key auto_increment,
	name varchar(50),
	price int);	

insert into dish_table values(null,'红烧肉',1200);
insert into dish_table values(null,'回锅肉',2200);
insert into dish_table values(null,'糖醋里脊肉',3200);
insert into dish_table values(null,'红烧鱼肉',4200);
insert into dish_table values(null,'干煸豆角',5200);



create table if not exists order_table(
  order_id int not null primary key auto_increment,
	table_id varchar(50),
	time varchar(50),
	dishes varchar(1024),	
	status int);	

insert into order_table values(null,'少林','2019/08/01 12：00','1,2,3,4,5',0);
insert into order_table values(null,'武当','2019/08/01 14：00','1,',0);
insert into order_table values(null,'峨眉','2019/08/01 18：00','1,5',0);
