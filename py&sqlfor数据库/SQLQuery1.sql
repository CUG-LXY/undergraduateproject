--select *
--from employee
--where employee_id='C4'

--select *
--from project

--�ɹ�����
--��ѯ��Ӧ����Ϣ
select supplier.supplier_id,price,num,supplier.city_name,city.posx ,city.posy from (supplier join supplier_parts on supplier.supplier_id=supplier_parts.supplier_id) join city on supplier.city_name=city.city_name where part_id = 'P1';

--�嵥
select project_id,part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on part_list_id=parts_list_id where project_id='J2';

--��ѯ��Ӧ����Ϣ
--select supplier.supplier_id,price,num,supplier.city_name,city.posx ,city.posy
--from (supplier join supplier_parts on supplier.supplier_id=supplier_parts.supplier_id) join city 
--on supplier.city_name=city.city_name 
--where part_id = 'P1';

--select project.project_id,city.city_name,city.posx,city.posy from project,city where project.city_name=city.city_name and project.project_id='J2';

select *
from id_pwd
--����
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


----��Ŀ������

--�鿴Ա����Ϣ
--select * from employee where sex='m'

--�鿴������Ϣ
--select * from project where phaseNo='1'

--�鿴���̽���
--select project_id,project_name,phaseNo from project

--�鿴���
--select * from parts


--�鿴��Ӧ��
select * from supplier


--�鿴������Ϣ
select * from make_deal


--select project_id,part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on part_list_id=parts_list_id where project_id='J2';

--select *
--from parts_list

