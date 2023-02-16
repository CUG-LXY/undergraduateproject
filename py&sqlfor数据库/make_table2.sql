create table city
(
	city_name varchar(50) not null,
	posx int not null,
	posy int not null,
	primary key(city_name)
);

create table project
(
	project_id varchar(50),
	phase int,
	project_name varchar(50) not null,
	size varchar(50) not null,
	responsible_man varchar(50) not null,
	city_name varchar(50) not null,
	start_time date,
	end_time date,
	primary key (project_id),
	foreign key (city_name) references city
);

create table parts
(
	part_id varchar(50),
	part_name varchar(50) not null,
	color varchar(50) not null,
	type varchar(50) not null,
	primary key (part_id)
);

create table supplier
(
	supplier_id varchar(50),
	supplier_name varchar(50) not null,
	city_name varchar(50) not null,
	primary key (supplier_id),
	foreign key (city_name) references city
);

create table project_parts
(
	project_id varchar(50),
	part_id varchar (50),
	num int not null,
	primary key (project_id,part_id),
	foreign key (project_id) references project,
	foreign key (part_id) references parts
);

create table supplier_parts
(
	supplier_id varchar(50),
	part_id varchar(50),
	num int not null,
	price numeric(10,2) not null,
	primary key (supplier_id,part_id),
	foreign key (supplier_id) references supplier,
	foreign key (part_id) references parts
);

create table make_deal
(
	deal_id varchar(50),
	project_id varchar(50),
	supplier_id varchar(50),
	part_id varchar(50),
	num int not null,
	phase int not null,
	primary key (deal_id),
	foreign key (project_id) references project,
	foreign key (supplier_id) references supplier,
	foreign key (part_id) references parts
);

create table manager
(
	manager_id varchar(50),
	manager_name varchar(50),
	sex char(1) not null,
	birth_day date not null,
	phone_number char(11) not null,
	family_address varchar(50),
	position varchar(50) not null,
	primary key (manager_id)
);

create table department
(
	dept_name varchar(50),
	primary key (dept_name)
);

create table manager_project
(
	project_id varchar(50),
	manager_id varchar(50),
	primary key (project_id, manager_id),
	foreign key (project_id) references project,
	foreign key (manager_id) references manager
);

create table belong 
(
	manager_id varchar(50),
	dept_name varchar(50),
	primary key (manager_id,dept_name),
	foreign key (manager_id) references manager,
	foreign key (dept_name) references department
);


create table parts_list
(
	list_id int IDENTITY(0,1),
	part_id varchar(50),
	require_num int not null,
	had_bought_num int not null,
	effective int check (effective in (0,1,2,3)),
	primary key (list_id,part_id),
	foreign key (part_id) references parts
);

create table buy
(
	manager_id varchar(50),
	list_id int,
	part_id varchar(50),
	primary key (manager_id,list_id,part_id),
	foreign key (manager_id) references manager,
	foreign key (list_id,part_id) references parts_list,
);

create table ini_plan
(
	ini_plan_id varchar(50),
	phase_sum int,
	pre_start_time date,
	pre_end_time date,
	primary key (ini_plan_id),
);

create table make_plan
(
	project_id varchar(50),
	ini_plan_id varchar(50),
	primary key (project_id,ini_plan_id),
	foreign key (project_id) references project,
	foreign key (ini_plan_id) references ini_plan
);

create table make_list
(
	project_id varchar(50),
	list_id int,
	part_id varchar(50),
	primary key(project_id,list_id,part_id),
	foreign key (project_id) references project,
	foreign key (list_id,part_id) references parts_list
);

create table his_project
(
	project_id varchar(50),
	phase int,
	project_name varchar(50) not null,
	size varchar(50) not null,
	responsible_man varchar(50) not null,
	manager_num int not null,
	city_name varchar(50) not null,
	end_time date,
	primary key (project_id),
	foreign key (city_name) references city
);

