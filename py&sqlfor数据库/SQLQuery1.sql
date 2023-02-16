--select *
--from employee
--where employee_id='C4'

--select *
--from project

--采购部门
--查询供应商信息
select supplier.supplier_id,price,num,supplier.city_name,city.posx ,city.posy from (supplier join supplier_parts on supplier.supplier_id=supplier_parts.supplier_id) join city on supplier.city_name=city.city_name where part_id = 'P1';

--清单
select project_id,part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on part_list_id=parts_list_id where project_id='J2';

--查询供应商信息
--select supplier.supplier_id,price,num,supplier.city_name,city.posx ,city.posy
--from (supplier join supplier_parts on supplier.supplier_id=supplier_parts.supplier_id) join city 
--on supplier.city_name=city.city_name 
--where part_id = 'P1';

--select project.project_id,city.city_name,city.posx,city.posy from project,city where project.city_name=city.city_name and project.project_id='J2';

select *
from id_pwd
--购买
--select *
--from make_deal

--select *
--from supplier_parts

--select *
--from project_parts

--select *
--from parts_list

--select *
--from make_list 

--select *
--from id_pwd

--select *
--from employee


----项目负责人

--查看员工信息
--select * from employee where sex='m'

--查看工程信息
--select * from project where phaseNo='1'

--查看工程进度
--select project_id,project_name,phaseNo from project

--查看零件
--select * from parts


--查看供应商
select * from supplier


--查看交易信息
select * from make_deal


--select project_id,part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on part_list_id=parts_list_id where project_id='J2';

--select *
--from parts_list

